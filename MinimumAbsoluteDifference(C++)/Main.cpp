#include <iostream>
#include <climits>
#include <vector>
#include <algorithm>

int minimumAbsoluteDifference(std::vector<int> arr){

	std::sort(arr.begin(), arr.end());		//Sorts the array (O(log(n)) time

	int maxDiff = INT_MAX;				//Set the largest difference to 'infinity'

	for (int i = 0; i < arr.size(); i++)		//Loop through the array (O(n) and check the difference between it and its neighbour
		if (abs(arr[i + 1] - arr[i]) < maxDiff)
			maxDiff = abs(arr[i + 1] - arr[i]);		//If the absolute difference is smaller than the one currently recorded, then we update it

	return maxDiff;					//Once we have made it through the entire array, return the minimum absolute difference

}

int main(){

	int N, temp;				//Temp variables to log the number of arguments and the current variable being read in

	std::cin >> N;

	std::vector<int> arr;

	for (int i = 0; i < N; i++){		//Read in the variables and push them onto the vector we created earlier

		std::cin >> temp;

		arr.push_back(temp);	

	}

	std::cout << minimumAbsoluteDifference(arr) << std::endl; //Print out the minimum absolute difference
		

	return 0;

}
