#include <stdio.h>
#include <stdlib.h>


int isSafe (int *position, int column, int row){
    for (int prev_col=0; prev_col < column; prev_col++){
        int prev_row = position[prev_col];
        if (prev_row == row || // R==C
            prev_row - prev_col == row - column || // R-C 
            prev_row + prev_col == column + row // R + C
        ){
            return (0);
        }
    }
    return (1);
}


void solve (int *position, int column, int n)
{
    if (column == n){
        for (int i = 0; i< n; i++){
            if (i > 0)
                printf(" ");
            printf("%d", position[i]);
        }
        printf("\n");
        return;
    }

    for (int row = 0; row <n; row++){
        if((isSafe(position, column, row))){
            position[column] = row;
            solve(position, column + 1, n);
        }
    }
}


int main (int argc, char ** argv)
{
    if (argc != 2) return (1);

    int n = atoi(argv[1]);
    int *position =  malloc(sizeof(int) * n);
    if (!position) return (1);
    solve(position, 0, n);
    free(position);
    return (0);
}