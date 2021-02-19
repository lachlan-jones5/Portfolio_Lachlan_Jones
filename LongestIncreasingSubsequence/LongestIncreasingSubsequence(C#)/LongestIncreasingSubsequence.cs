using System;
using System.Collections.Generic;
using System.Threading.Tasks;

namespace ConsoleApp1
{
    class LongestIncreasingSubsequence
    {
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
        static void LIS(List<int> arr)
        {

            int N = arr.Capacity;

            int[] tailIndicies = new int[N];

            for (int i = 0; i < N; i++)
                tailIndicies[i] = 0;

            int[] prevIndicies = new int[N];

            for (int i = 0; i < N; i++)
                prevIndicies[i] = -1;

            int len = 1;

            for (int i = 1; i < N; i++)
            {

                if (arr[i] <= arr[tailIndicies[0]])
                    tailIndicies[0] = i;
                else if (arr[i] > arr[tailIndicies[len - 1]])
                {

                    prevIndicies[i] = tailIndicies[len - 1];
                    tailIndicies[len++] = i;

                }
                else
                {

                    int x = BSearch(arr, tailIndicies, -1, len - 1, arr[i]);
                    prevIndicies[i] = tailIndicies[x - 1];
                    tailIndicies[x] = i;

                }

            }


            //Do the print part now
            int[] myArr = new int[N];
            int myArrIndex = 0;

            for (int i = tailIndicies[len - 1]; i >= 0; i = prevIndicies[i])
                myArr[myArrIndex++] = arr[i];


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

