#include <stdio.h>
#include <stdlib.h>

int main() {

    int m[3][3] = {{1,2,3}, {4,5,6}, {7,8,9}};
    for (int i = 0; i < 3; j++) {
        for (int j = 0; j < 3; j++) {
            printf("%d\t", m[i][j]);
        }
        printf("\n");
    }

    int **t = malloc(3 * sizeof(int *));
    for (int i = 0; i < 3; i++)
        t[i] = malloc(3 * sizeof(int));

}

    
