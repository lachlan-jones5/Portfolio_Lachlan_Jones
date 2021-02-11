/*

	Exercise 8 - Stacks Revisited
	Lachlan Jones
	lj428

*/

#include <iostream>
#include <fstream>
using namespace std;

void file_opener(fstream& infile) {

	//Takes in file name
	string file;

	cerr << "Enter the file name : ";
	cin >> file;

	cout << flush;
	//File opened
	infile.open(file);

	//If file was not found then this message is displayed
	if (!infile) {

		cerr << "File was not found.  Please run the program and try again.\n";
		exit(1);

	}

}

//This creates a stack twice the size of the original stack, and then returns a pointer to the new stack after the original is deleted
int* double_stack(int* stack, int &n, int INDEX_stack) {

	n *= 2;

	int* new_stack = new int[n];

	for (int i = 0; i <= INDEX_stack; i++)
		new_stack[i] = stack[i];

	delete[] stack;

	cerr << "Stack doubled from " << n / 2 << " to " << n << ".\n";

	return new_stack;

}

//Creates a stack, and then returns a pointer to it
int* stack_creation(int n) {

	int* stack = new int[n];

	return stack;

}

int main() {

	fstream infile;
	file_opener(infile);

	int n;

	infile >> n;

	int* stack = stack_creation(n);
	int INDEX_stack = -1;

	int value;
	string command;

	//While there are input values
	while (infile >> command) {

		//If it is a pop commmand
		if (command.compare("pop") == 0) {

			if (INDEX_stack > -1)
				--INDEX_stack;

		}
		//If it is a push command
		else if (command.compare("push") == 0) {

			infile >> value;

			//If the array is full, double it
			if (INDEX_stack == (n - 1))
				stack = double_stack(stack, n, INDEX_stack);

			stack[++INDEX_stack] = value;

		}

	}

	cerr << "Stack contains " << (INDEX_stack + 1) << " entries\n";

	infile.close();

	//Deleting the final stack
	delete[] stack;

	return 0;

}
