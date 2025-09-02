
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


// first we have to confirm if all values are num

int check_int(char **av, int ac)
{
    int i = 1;
    while (i < ac){
        char j = 0;
        if (av[i][j] == '-' || av[i][j]=='+'){
            j++;
        }
        while(av[i][j]){
            if (av[i][j] < '0' || av[i][j] > '9'){
                return (0);
            }
            j++;
        }
        i++;
    }
    return 1;
}

void solve (int *numbers, int target, int index){

}


int main (int argc, char **argv)
{
    if (argc <= 2) return (1);
    int thenum;
    int *numbers;
    if (argc > 3 && check_int(argv, argc)){
        thenum = atoi(argv[1]);
        numbers = malloc(sizeof(int) * (ac - 2));
        if (!number) return (1);
        solve(numbers, target, 0);
        free(numbers);
    }
    else {
        printf("something wrong");
        return (1);
    }

    return (0);
}

