#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// ./a.out '( ( ) ( ( ) ('


int is_val(char *input){
    int fourty = 0;
    int fourtyone = 0;

    while (*input){
        if (*input == '('){
            fourty += 1;
        } else if (*input == ')')
            if (fourty > 0)
                fourty--;
            else 
                fourtyone += 1;
        input++;
    }
    return (fourty + fourtyone);
}


void solve( char *arg, int tofix, int nfixed, int pos )
{
    if (is_val(arg)== 0 && tofix == nfixed ){
        puts(arg);
        return;
    }

    for (int i = pos; arg[i]; i++){
        if (arg[i] == '(' || arg[i] == ')'){
            int num = arg[i];
            arg[i] = '_';
            solve(arg, tofix, nfixed + 1, i); // i is the new position of cursor (new pos) RECURSION
            arg[i] = num; // BACKTRACKING
        }
    }
    return;
}


int main (int ac, char **av)
{
    if (ac != 2) return (1);
    int tofix = 0;

    char *input = av[1];
    
    tofix= is_val(input);
    solve(input, tofix, 0, 0); // last two 0's are total fixed yet and position of cursor
    return (0);
}