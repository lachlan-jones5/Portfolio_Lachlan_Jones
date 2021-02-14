#include <iostream>
#include <string>

int main(){

	int fizz = 3;						//Set numbers that we want to be divisible by (fizz and buzz numbers)
	int buzz = 5;
	std::string outString; 					//Our string begins here

	for (int i = 1; i <= 100; i++){

		outString = "";					//Set string to empty

		if (i % fizz == 0)
			outString += "Fizz";			//Add fizz to string if i is divisible by fizz number
		
		if (i % buzz == 0)				//Add buzz to string if i is divisible by buzz number
			outString += "Buzz";

		if (outString.compare("") == 0)			//Check to see if string is empty, add number to string if so
			outString += std::to_string(i);

		std::cout << outString << std::endl;		//Print the string with a new line

	}

	return 0;					

}


			
