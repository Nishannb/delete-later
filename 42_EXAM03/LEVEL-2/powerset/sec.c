// display all subsets of a set whose sum of its elements is equal to the first argument.
// The numbers of the set are from the second argument to the last.
// A subset must not be displayed a second time.

// ex1
// ./a.out 5 2 3 | cat -e
// 2 3$

// ex2
// ./a.out 12 5 7 4 3 2 | cat -e
// 5 7$
// 5 4 3$
// 7 3 2$
// */

// ils ne testent pas des séquences invalides telles que :

// ./a.out 5 12 18 | cat -e

// l'ordre des lignes n'est pas important, par contre l'ordre de l'input l'est.

// ceci est valide

// ./a.out 5 3 2 1 4 | cat -e 
// 3 2$
// 1 4$

// ceci est valide

// ./a.out 5 3 2 1 4 | cat -e 
// 1 4$
// 3 2$

// ceci n'est pas valide

// ./a.out 5 3 2 1 4 | cat -e 
// 4 1$
// 2 3$

// faire attention au cas ou le nombre à atteindre est 0 car 'rien' est condidérê comme une possibilité donc il faudra afficher une nouvelle ligne

// ./a.out 0 1 -1 2 -2 | cat -e
// $
// -1 1 2 -2$
// -1 1$
// 2 -2$

#include <stdio.h>
#include <stdlib.h>

int check_int (char **nums, int ac)
{
    int i = 1;
    
    while (i < ac){
        int j = 0;
        if (nums[i][j] == '-' || nums[i][j] == '+'){
            j++;
        }
        while (nums[i][j]){
            if(nums[i][j] < '0' || nums[i][j] >'9'){
                return 0;
            }
            j++;
        }
        i++;
    }
    return 1;
}


void solve(int *nums, int target, int len, int *subset, int index, int sub_size, int sum)
{

    //base case
    if (len == index){
        if(target == sum){
            for (int i = 0; i < sub_size; i++){
                printf("%d", subset[i]);
                if (i != sub_size - 1)
                    printf(" ");
            }
            printf("\n");
        }
        return;
    }

    // recursion

    solve(nums, target, len, subset, index + 1, sub_size, sum);
    subset[sub_size] = nums[index];
    solve(nums, target, len, subset, index + 1, sub_size + 1, sum + nums[index]);
}



int main (int ac, char **av){
    if (ac > 3 && check_int(av, ac)){
        int target = atoi(av[1]);
        int subset[(ac -2)];
        int sub_size;
        int * numbers = malloc (sizeof(int) * (ac - 2));
        if (!numbers){
            return 1;
        }
       for (int i = 0; i < (ac -2); i++){
            numbers[i] = atoi(av[i + 2]);
       }

        solve(numbers, target, (ac - 2), subset, 0, 0, 0); // index, sub_size, sum
        free(numbers);
        return 0;
    }
    return 1;
}