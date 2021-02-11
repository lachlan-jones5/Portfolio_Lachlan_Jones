/*

	Assignment 2- Discrete Simulation


	Name:				Lachlan Jones
	Student ID:			lj428
	Student Number:		6087383

*/

#include <iostream>
#include <fstream>
using namespace std;

struct event {

	double time;	//This is the time the event will begin to occur
	int event_type;	//Event types are (0) Tourist arrival, (1) Business arrival, (2) to (Nb + 1) are Business server completions, and (Nb + 2) to (Nb + Nt + 1) are Tourist server completions
	double length;	//This is the amount of time the event will take.  If an event is an arrival, the amount of time it will take to server the customer is here.  If it is a server completion event, it will be 0, because once the server completes then this event is over
					//i.e. It happens instantly

};

//Declaring global variables
string filename; //Stores the name of the input file, as it needs to be opened again for the second pass
double simulation_time; //Current time of simulation
int Nb, Nt; //Nb = number of business servers, Nt = number of tourist servers
event Nb_queue[500]; //Business customers queue
event Nt_queue[500]; //Tourist customers queue

//Declaration of ALL indexes!
int INDEX_Nb_stack, INDEX_Nt_stack; //Index of the top of the server stacks
int INDEX_heap; //Index of the top of the event heap
int INDEX_Nb_queue_front, INDEX_Nb_queue_back, SIZE_Nb_queue; //Front, back and size indexes of the business queue
int INDEX_Nt_queue_front, INDEX_Nt_queue_back, SIZE_Nt_queue;	//Front, back and size indexes of the tourist queue

//Declaring statistics counters and variables
int total_passengers, B_passengers, T_passengers, MAX_Nb, MAX_Nt, MAX_all; //Statistics for amount of passengers and max queue sizes
//Counters for service times, such as total service time (used for averages later)
double total_service_time, B_service_time, T_service_time, total_queue_time, B_queue_time, T_queue_time, total_queue_length, last_queue_change, B_queue_length, B_last_change, T_last_change, T_queue_length;

//This method opens the file coming in.
void file_opener(fstream& infile) {

	//Input of filename
	cerr << "File name: ";
	cin >> filename;

	//Opening of file using fstream
	infile.open(filename);

	//If file does not open
	if (!infile) {

		cerr << "Error in finding file " << filename << ". Try again\n";
		exit(1);

	}

}

//Pushes the server back onto the top of the stack
void push(event this_event, event* stack, int& index) {

	stack[++index] = this_event;

}

//Retrieves the server from the top of the stack
event pop(event* stack, int& index) {

	return stack[index--];

}

//This is used to remove a customer from the front of a queue
event dequeue(event* queue, int& queue_size, int& queue_index_back, int& queue_index_front) {

	--queue_size;

	//This is used to get the average length of both queues
	total_queue_length += (queue_size + 1) * (simulation_time - last_queue_change);
	last_queue_change = simulation_time;

	//Allows for wrap around like enqueue
	if (queue_index_front == (500 - 1)) {
		queue_index_front = 0;
		return queue[500 - 1];
	}
	else
		return queue[queue_index_front++];

}

//Enqueue is used to add someone to the end of the queue
void enqueue(event cust, int& queue_size, event* queue, int& queue_index_back, int& queue_index_front) {

	//If the queue is empty, this is what occurs
	if (queue_size < 0) {

		queue[0] = cust;
		queue_index_back = 0;
		queue_index_front = 0;
		queue_size = 1;

	}//This if statement deals with a 'wrap around' of the queue i.e. if the queue reaches the end of the array, it can wrap around to the beginning
	else if (queue_index_back == (500 - 1)) {

		queue[0] = cust;
		queue_index_back = 0;
		++queue_size;

	}//This statement adds someone to the end of the queue, if everything else prior is valid
	else {

		queue[++queue_index_back] = cust;
		++queue_size;

	}
	
	//This is used for the average length of both queues
	total_queue_length += (queue_size - 1) * (simulation_time - last_queue_change);
	last_queue_change = simulation_time;

	//This is used to find the maximum of both queues
	if ((SIZE_Nb_queue + SIZE_Nt_queue) > MAX_all)
		MAX_all = SIZE_Nb_queue + SIZE_Nt_queue;

}

//This is the siftup function.  It is used to keep everything in order
void siftup(event* heap, int i) {

	if (i != 0) {

		int p = (i / 2) - 1;

		if (p < 0)
			p = 0;



		//To keep everything in order, if the right child of a node is bigger than the left child, they switch.
		if (heap[i].time > heap[i - 1].time) {

			event temp = heap[i];
			heap[i] = heap[i - 1];
			heap[i - 1] = temp;
			siftup(heap, i - 1);

		}

		//If a child is bigger than it's parent node, it switches
		if (heap[p].time < heap[i].time) {

			event temp = heap[i];
			heap[i] = heap[p];
			heap[p] = temp;
			siftup(heap, p);

		}

		//These next two if statements ensure that service completion events are stored higher in the event heap than customer arrivals.
		if (heap[i].time == heap[i - 1].time) {

			if (heap[i].event_type >= 2 && (heap[i - 1].event_type == 0 || heap[i - 1].event_type == 1)) {

				event temp = heap[i];
				heap[i] = heap[i - 1];
				heap[i - 1] = temp;
				siftup(heap, i - 1);

			}

		}

		if (heap[p].time == heap[i].time) {

			if (heap[i].event_type >= 2 && (heap[p].event_type == 0 || heap[p].event_type == 1)) {

				event temp = heap[i];
				heap[i] = heap[p];
				heap[p] = temp;
				siftup(heap, p);

			}

		}

	}

}

//This method adds an event to the event heap
void add_event(event this_event, event* heap) {

	heap[++INDEX_heap] = this_event;
	//Maintains the order of the heap
	siftup(heap, INDEX_heap);

}

//This method gets the event at the top of the event heap
event get_event(event* heap) {

	return heap[INDEX_heap--];

}

//This method processes the arrival of a customer, and if there is a server to serve them, then this metho is called
event process_arrival(event this_event, event* stack, int& index, event* heap) {

	event new_event = pop(stack, index);
	new_event.time = simulation_time + this_event.length;
	add_event(new_event, heap);

	return new_event;

}

//This method is when a server finishes serving and there is another customer that the server can serve
//This customer is then added to the server and a server completion event is created
event continue_serving(event this_event, event customer, event* heap, event prev_event) {

	this_event.time = customer.length + simulation_time;
	add_event(this_event, heap);

	//This is to guard against some strange bug where service completion events are sometimes processed twice
	if (!(prev_event.time == this_event.time && prev_event.event_type == this_event.event_type && prev_event.length == this_event.length)) {

		//Here we get the total amount of time the customer was in the queue for and add it to the total queue time.
		total_queue_time += simulation_time - customer.time;

		//These are adding the customer queue time to the correct counters.
		//If the customer that is about to begin getting served is a business customer, then we add their total queue time to the total business queue time
		//The same goes for a tourist customer
		if (this_event.event_type >= 2 && this_event.event_type <= (Nb + 1))
			B_queue_time += simulation_time - customer.time;
		else
			T_queue_time += simulation_time - customer.time;

	}

	return customer;
}

//This method increments various counters.
//Not every counter is here, because it was easier to store them elsewhere.
//However, counters such as the total amount of passengers, total business passengers, and total tourist passengers are managed here.
void counters(event this_event, event prev_event) {

	switch (this_event.event_type) {

	case 0:
		total_passengers++;
		T_passengers++;
		total_service_time -= simulation_time;
		T_service_time -= simulation_time;
		break;

	case 1:
		total_passengers++;
		B_passengers++;
		total_service_time -= simulation_time;
		B_service_time -= simulation_time;
		break;

	default:
		//The total service time of a customer is also managed here
		//Used for the average total service time later on when printing
		if (!(prev_event.time == this_event.time && prev_event.event_type == this_event.event_type && prev_event.length == this_event.length)) {

			total_service_time += simulation_time;

			if (this_event.event_type >= 2 && this_event.event_type <= (Nb + 1))
				B_service_time += simulation_time;
			else
				T_service_time += simulation_time;

		}
		break;

	}

}

//The simulation loop
void main_loop(int pass, fstream& infile, event* heap, event* Nb_stack, event* Nt_stack, double* Nb_busy, double* Nt_busy) {

	event first_event;

	//Read in the first event
	infile >> first_event.time;
	infile >> first_event.event_type;
	infile >> first_event.length;

	//Put first event onto the heap
	add_event(first_event, heap);

	//The previous event is a solution to a bug in which completion events are repeated.  I have implemented this as to get the correct averages
	event prev_event;

	event this_event;
	this_event.time = -1.1;
	this_event.event_type = -1;
	this_event.length = -1.1;

	//i.e. while the event heap is not empty
	while (INDEX_heap > -1) {

		prev_event.time = this_event.time;
		prev_event.event_type = this_event.event_type;
		prev_event.length = this_event.length;

		this_event = get_event(heap); //Retrieve the next item in the heap (we are using a max heap so it will be the top most item)
		simulation_time = this_event.time; //Make the current simulation time equal to this event's time

		//Calling the counters method, described above.
		counters(this_event, prev_event);

		//This event is used to add an event to the heap later on
		event add_an_event;

		switch (this_event.event_type) {

		case 0: //Case 0 is if the current event occuring is a tourist passenger arrival

			switch (pass) { //pass refers to if it is the first run or the second run
							//Each run has different rules, so we refer to different sets of if statements

			case 1: //The first run
				//If there is an idle tourist server, then they go into this statement
				if (INDEX_Nt_stack > -1) { 

					event server = process_arrival(this_event, Nt_stack, INDEX_Nt_stack, heap);

					//This is used to calculate the idle time per server later on
					Nt_busy[(server.event_type - Nb) - 2] += this_event.length;

				}
				else { //If there is no idle tourist server, then the customer is added to the back of the customer queue

					enqueue(this_event, SIZE_Nt_queue, Nt_queue, INDEX_Nt_queue_back, INDEX_Nt_queue_front);

					//Below are some counters, used to calculate the average tourist queue length later on
					T_queue_length += (SIZE_Nt_queue - 1) * (simulation_time - T_last_change);
					T_last_change = simulation_time;

					//This is updating the max of the tourist queue
					if (SIZE_Nt_queue > MAX_Nt)
						MAX_Nt = SIZE_Nt_queue;

				}
				break;

			case 2:
				//This is the second run
				if (INDEX_Nt_stack > -1) {//If there is a tourist server available, they wll serve the tourist server.
											//This if statement works the same as in case 1
					event server = process_arrival(this_event, Nt_stack, INDEX_Nt_stack, heap);

					Nt_busy[(server.event_type - Nb) - 2] += this_event.length;
				}//However, this time, if there are no tourist servers available, but the queue for the business passengers is empty and there is a business server available
					//The business server will serve the tourist passenger
				else if (INDEX_Nt_stack == -1 && SIZE_Nb_queue == -1 && INDEX_Nb_stack > -1) {
					event server = process_arrival(this_event, Nb_stack, INDEX_Nb_stack, heap);

					Nb_busy[server.event_type - 2] += this_event.length;

				}
				else { //If there are no servers available at all, then the tourist passenger gets put at the back of the tourist queue

					enqueue(this_event, SIZE_Nt_queue, Nt_queue, INDEX_Nt_queue_back, INDEX_Nt_queue_front);
					T_queue_length += (SIZE_Nt_queue - 1) * (simulation_time - T_last_change);
					T_last_change = simulation_time;

					if (SIZE_Nt_queue > MAX_Nt)
						MAX_Nt = SIZE_Nt_queue;
				}
				break;


			}


			//We read in the next event from the file, and if it isn't the dummy record, it is added to the heap
			infile >> add_an_event.time;
			infile >> add_an_event.event_type;
			infile >> add_an_event.length;

			if (add_an_event.time > 0 && add_an_event.length > 0)
				add_event(add_an_event, heap);

			break;

		case 1: //A business passenger arrives in the terminal!

			if (INDEX_Nb_stack > -1) { //If there is a business server available to serve them, then they will be served

				event server = process_arrival(this_event, Nb_stack, INDEX_Nb_stack, heap);

				Nb_busy[server.event_type - 2] += this_event.length;

			}
			else { //If not, they're added to the queue

				enqueue(this_event, SIZE_Nb_queue, Nb_queue, INDEX_Nb_queue_back, INDEX_Nb_queue_front);

				B_queue_length += (SIZE_Nb_queue - 1) * (simulation_time - B_last_change);
				B_last_change = simulation_time;

				if (SIZE_Nb_queue > MAX_Nb)
					MAX_Nb = SIZE_Nb_queue;

			}

			//Once again, we read in the next event and add it to the index only if it is not the dummy record
			infile >> add_an_event.time;
			infile >> add_an_event.event_type;
			infile >> add_an_event.length;

			if (add_an_event.time > 0 && add_an_event.length > 0)
				add_event(add_an_event, heap);

			break;

		default: //Default means it is a service completion

			if (this_event.event_type >= 2 && this_event.event_type <= (Nb + 1)) { //Business server completion

				if (SIZE_Nb_queue > -1) { //If the business queue is not empty, then the server will start serving the next business customer

					event customer = continue_serving(this_event, dequeue(Nb_queue, SIZE_Nb_queue, INDEX_Nb_queue_back, INDEX_Nb_queue_front), heap, prev_event);

					Nb_busy[this_event.event_type - 2] += customer.length;

					B_queue_length += (SIZE_Nb_queue + 1) * (simulation_time - B_last_change);
					B_last_change = simulation_time;

				}
				else {

					switch (pass) {//Once again, the second and first runs differ

					case 1: //In the first run, if there is no one in the business queue to serve, the server becomes idle

						push(this_event, Nb_stack, INDEX_Nb_stack); //may need to set event time to 0

						break;

					case 2://Here in the second run, if the business queue is empty, there are no idle tourist servers, and the tourist queue isn't empty...
							//Then the business server will serve the tourist server.
						if (SIZE_Nt_queue > -1 && INDEX_Nt_stack == -1) {

							event customer = continue_serving(this_event, dequeue(Nt_queue, SIZE_Nt_queue, INDEX_Nt_queue_back, INDEX_Nt_queue_front), heap, prev_event);
							Nb_busy[this_event.event_type - 2] += customer.length;
							T_queue_length += (SIZE_Nt_queue + 1) * (simulation_time - T_last_change);
							T_last_change = simulation_time;



						}
						else {

							push(this_event, Nb_stack, INDEX_Nb_stack);

						}
						break;

					}

				}

			}
			else {//Tourist server completion, works the same as case 1: for the pass switch statement above.

				if (SIZE_Nt_queue > -1) {
					event customer = continue_serving(this_event, dequeue(Nt_queue, SIZE_Nt_queue, INDEX_Nt_queue_back, INDEX_Nt_queue_front), heap, prev_event);
					Nt_busy[(this_event.event_type - Nb) - 2] += customer.length;
					T_queue_length += (SIZE_Nt_queue + 1) * (simulation_time - T_last_change);
					T_last_change = simulation_time;


				}
				else {

					push(this_event, Nt_stack, INDEX_Nt_stack);

				}

			}

			break;

		}

	}

}

//Initialises all global variables
void initialisation(fstream& infile) {

	infile >> Nb;
	infile >> Nt;

	INDEX_Nb_stack = INDEX_Nt_stack = INDEX_heap = MAX_all = -1;
	INDEX_Nb_queue_front = INDEX_Nb_queue_back = SIZE_Nt_queue = -1;
	INDEX_Nt_queue_front = INDEX_Nt_queue_back = SIZE_Nb_queue = MAX_Nb = MAX_Nt = -1;

	total_passengers = B_passengers = T_passengers = total_queue_length = 0;
	last_queue_change = B_last_change = T_last_change = 0.0;
	B_queue_length = T_queue_length = 0.0;
	simulation_time = total_service_time = B_service_time = T_service_time = total_queue_length = total_queue_time = 0.0;

}

//Constructs the appropriate amount of servers
void server_creation(event* Nb_stack, event* Nt_stack, double* Nb_busy, double* Nt_busy) {

	for (int i = 0; i < Nb; i++) {

		event server;
		server.time = 0;
		server.event_type = i + 2;
		server.length = 0;
		Nb_stack[i] = server;

		Nb_busy[i] = 0;

	}

	for (int i = 0; i < Nt; i++) {

		event server;
		server.time = 0;
		server.event_type = Nb + i + 2;
		server.length = 0;
		Nt_stack[i] = server;

		Nt_busy[i] = 0;

	}

	INDEX_Nb_stack = (Nb - 1);
	INDEX_Nt_stack = (Nt - 1);

}

//This function prints the stats of each run
void print_stats(double* Nb_actual_busy, double* Nt_actual_busy) {


	fprintf(stderr, "\tNumber of people served:\t\t\t\t%04d\n", total_passengers);
	fprintf(stderr, "\tTime last service is completed:\t\t\t\t%04.02f\n", simulation_time);
	cerr << "\n\tBusiness class customers:\n";
	fprintf(stderr, "\tAverage total service time:\t\t\t\t%04.02f\n", (B_service_time / (float)B_passengers));
	fprintf(stderr, "\tAverage total time in queue:\t\t\t\t%04.02f\n", (B_queue_time / (float)B_passengers));
	fprintf(stderr, "\tAverage length of queue:\t\t\t\t%04.02f\n", (B_queue_length / simulation_time));
	fprintf(stderr, "\tMaximum number queued:\t\t\t\t\t%04d\n", MAX_Nb);
	cerr << "\n\tTourist class customers:\n";
	fprintf(stderr, "\tAverage total service time:\t\t\t\t%04.02f\n", (T_service_time / (float)T_passengers));
	fprintf(stderr, "\tAverage total time in queue:\t\t\t\t%04.02f\n", (T_queue_time / (float)T_passengers));
	fprintf(stderr, "\tAverage length of queue:\t\t\t\t%04.02f\n", (T_queue_length / simulation_time));
	fprintf(stderr, "\tMaximum number queued:\t\t\t\t\t%04d\n", MAX_Nt);
	cerr << "\n\tAll customers:\n";
	fprintf(stderr, "\tAverage total service time:\t\t\t\t%04.02f\n", (total_service_time / (float)total_passengers));
	fprintf(stderr, "\tAverage total time in queue:\t\t\t\t%04.02f\n", (total_queue_time / (float)total_passengers));
	fprintf(stderr, "\tAverage length of queue:\t\t\t\t%04.02f\n", (total_queue_length / (float)total_passengers));
	fprintf(stderr, "\tMaximum number queued:\t\t\t\t\t%04d\n", MAX_all);

	cerr << "\n\tBusiness class servers:\n";
	for (int i = 0; i < Nb; i++)
		fprintf(stderr, "\tTotal idle time for business class server %d:\t\t%04.02f\n", (i + 1), (simulation_time - Nb_actual_busy[i]));

	cerr << "\n\tTourist class servers:\n";

	for (int i = 0; i < Nt; i++)
		fprintf(stderr, "\tTotal idle time for tourist class server %d:\t\t%04.02f\n", (i + 1), (simulation_time - Nt_actual_busy[i]));

	cerr << "\n";

}

int main() {

	fstream infile;
	file_opener(infile);

	//Initialisation methods
	initialisation(infile);
	event heap[Nb + Nt + 1]; //The event heap
	event Nb_stack[Nb];		//The stack of all business servers
	event Nt_stack[Nt];		//The stack of all tourist servers
	double Nb_busy[Nb];		//An array of the total time business servers are busy for
	double Nt_busy[Nt];		//An array of the total time tourist servers are busy for
	server_creation(Nb_stack, Nt_stack, Nb_busy, Nt_busy);

	//First pass
	int pass = 1;
	main_loop(pass++, infile, heap, Nb_stack, Nt_stack, Nb_busy, Nt_busy);
	cerr << "\nPass 1: Business servers exclusively serve business class:\n\n";
	print_stats(Nb_busy, Nt_busy);
	cerr << "\n\n";

	infile.close();

	//Reopen the file! Yea! :D
	infile.open(filename);

	//Initialisation methods
	initialisation(infile);
	server_creation(Nb_stack, Nt_stack, Nb_busy, Nt_busy);

	//Second pass
	main_loop(pass, infile, heap, Nb_stack, Nt_stack, Nb_busy, Nt_busy);
	cerr << "Pass 2: Idle business servers may serve tourist class:\n\n";
	print_stats(Nb_busy, Nt_busy);
	cerr << "\n\n";

	infile.close();

	return 0;

}
