using System;
using System.Collections.Generic;
using System.Threading.Tasks;

namespace ConsoleApp1
{
    class LongestIncreasingSubsequence
    {
		//This function is a binary search for the smallest value greater than or equal to the value given
        static int BSearch(List<int> array, int[] T, int left, int right, int val)
        {

            while (right - left > 1)
            {

                int middle = left + (right - left) / 2;

                if (array[T[middle]] >= val)
                    right = middle;
                else
                    left = middle;

            }

            return right;

        }
		//This function finds and prints the longest increasing subsequence given from user input
        static void LIS(List<int> arr)
        {

            int N = arr.Capacity;				//Set N = the amount of numbers given

            int[] tailIndicies = new int[N];	//Tail indicies array holds all possible end values

            for (int i = 0; i < N; i++)			//Initalise to 0
                tailIndicies[i] = 0;

            int[] prevIndicies = new int[N];	//Prev indicies holds all parent values

            for (int i = 0; i < N; i++)
                prevIndicies[i] = -1;			//Initialise to -1

            int len = 1;						//The longest subsqeuence - currently is 1 as each element is a subsequence of 1

			//Iterate through the given elements
            for (int i = 1; i < N; i++)
            {
				
				if (arr[i] <= arr[tailIndicies[0]])
                    tailIndicies[0] = i;
                else if (arr[i] > arr[tailIndicies[len - 1]]) //If it is bigger than the previous element, then we can add it in
                {

                    prevIndicies[i] = tailIndicies[len - 1];
                    tailIndicies[len++] = i;

                }
                else //If it is not big enough to add, we find a place for it to be added to
                {

                    int x = BSearch(arr, tailIndicies, -1, len - 1, arr[i]);
                    prevIndicies[i] = tailIndicies[x - 1];
                    tailIndicies[x] = i;

                }

            }

			//Create a new array to hold the LIS
            int[] myArr = new int[N];
            int myArrIndex = 0;

            for (int i = tailIndicies[len - 1]; i >= 0; i = prevIndicies[i])
                myArr[myArrIndex++] = arr[i];

			//Print the LIS
            for (int i = myArrIndex - 1; i >= 0; i--)
                Console.Write(myArr[i] + " ");


        }
        static void Main(string[] args)
        {

            Console.WriteLine("Input your values separated by a space");
            string input = Console.ReadLine();

            List<int> arr = new List<int>(Array.ConvertAll(input.Split(" "), int.Parse));
            LIS(arr); 
        }

    }

}

