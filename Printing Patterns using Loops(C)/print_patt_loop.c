#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() 
{

    int n;
    scanf("%d", &n);

    int length = n + (n - 1), removal_pos = 0, neg_counter = 0, add_pos = length - 1;

    for (int i = 0; i < length/2 + 1; i++){

        for (int j = 0; j < length; j++){

            printf("%d ", n - neg_counter);
            if (j < removal_pos) ++neg_counter;
            if (j >= add_pos) --neg_counter;

        }

        ++removal_pos;
        --add_pos;

        neg_counter = 0;

        printf("\n");

    }

    for (int x = 0; x < length/2; x++){

        for (int j = 0; j < length; j++){

            printf("%d ", n - neg_counter);
            if (j >= removal_pos) --neg_counter;
            if (j < add_pos) ++neg_counter;

        }

        ++removal_pos;
        --add_pos;

        neg_counter = 0;

        printf("\n");

    }

    return 0;

}
