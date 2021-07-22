#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() 
{

    int n;
    scanf("%d", &n);

    // Initialise variables
    int limit = n + (n-1), switch_counter = 0, out_index = 0, neg_counter = 0, rev_index = 0;
    int mid = n - 1;
    int out[n];
    char reverse[(limit * 2 + 1) * ((n - 1) * 2)];

    // Perform printing calculations
    for (int i = 0; i < n; i++){
            
        for (int j = 0; j < n; j++){
                
            if (j <= switch_counter && j != 0) ++neg_counter;
            out[out_index++] = n - neg_counter;
            printf("%d ", out[out_index - 1]);
            reverse[rev_index++] = n + '0';
            reverse[rev_index++] = ' ';
                
        }
        
        for (int x = out_index - 1; x > 0; x--){
                
            printf("%d ", out[x]);
            reverse[rev_index++] = n + '0';
            reverse[rev_index++] = ' ';
                
        }
        
        reverse[rev_index++] = '\n';
        ++switch_counter;
        out_index = 0;
        printf("\n");
    
    }

    for (int x = 0; x < rev_index - limit + 2; x++)
        printf("%c", reverse[x]);
    
    return 0;

}
