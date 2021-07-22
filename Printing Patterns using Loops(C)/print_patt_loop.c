#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() 
{

    int n;
    scanf("%d", &n);
    int length = n + (n - 1) - 1, cl_index = 0, rev_index = 0, removal_pos = 0;
    int curr_line[n];
    int rev[n * length];

    for (int i = 0; i < length/2 + 1; i++){

        for (int j = 0; j < n; j++){

            curr_line[cl_index++] = n;
            rev[rev_index++] = n;
            printf("%d ", n);

        }

        for (int k = n - 1; k > 0; k--){

            rev[rev_index++] = n;
            printf("%d ", curr_line[k]); 

        } 

        printf("\n");
        cl_index = 0;

        removal_pos++;

    }

    for (int j = 0; j < (length + 1) - (length/2 + 1); j++){

        for (int k = 0; k < length + 1; k++) printf("%d ", n);
        printf("\n");

    }

    return 0;

}

/*

 5 5 5 5 5 5 5 5 5
 5 4 4 4 4 4 4 4 5
 5 4 3 3 3 3 3 4 5
 5 4 3 2 2 2 3 4 5
 5 4 3 2 1 2 3 4 5
 5 4 3 2 2 2 3 4 5
 5 4 3 3 3 3 3 4 5
 5 4 4 4 4 4 4 4 5
 5 5 5 5 5 5 5 5 5

*/
