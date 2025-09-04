// Assignment name: rip
// Expected files: *.c *.h
// Allowed functions: puts, write
// --------------------------------------------------------------------------------
// Write a program that will take as argument a string containing only parenthesis.
// If parenthesis are unbalanced (for example "())") your program shall remove the
// minimum number of parenthesis for the expression to be balanced.
// By removing we mean replacing by spaces.
// You will print all the solutions (can be more than one).
// The order of the solutions is not important.

// For example this should work:
// (For readability reasons the '_' means space and the spaces are for readability only.)
// $> ./rip '( ( )' | cat -e
// _ ( ) $
// ( _ ) $

// $> ./rip '( ( ( ) ( ) ( ) ) ( ) )' | cat -e
// ( ( ( ) ( ) ( ) ) ( ) ) $

// $> ./rip '( ) ( ) ) ( )' | cat -e
// ( ) ( ) _ ( ) $
// ( ) ( _ ) ( ) $
// ( _ ( ) ) ( ) $

// $> ./rip '( ( ) ( ( ) (' | cat -e
// ( ( ) _ _ ) _ $
// ( _ ) ( _ ) _ $
// ( _ ) _ ( ) _ $
// _ ( ) ( _ ) _ $
// _ ( ) _ ( ) _ $

#include <stdio.h>

int is_val(char *str){
    int open =0;
    int end = 0;
    int i = 0;

    while (str[i]){
        if (str[i] == '(')
            open++;
        else if (str[i] == ')'){
            if (open > 0)
                open--;
            else 
                end++;
        }
        i++;
    }
    return open + end;
}

void rip (char *position, int m_fix, int n_fix, int pos)
{
    //base case
    if (m_fix == n_fix && !is_val(position)){
        puts(position);
        return;
    }

    // recursion
    for (int i = pos; position[i]; i++){
        if (position[i] == '(' || position[i] ==')'){
            char tmp = position[i];
            position[i] = ' ';
            rip(position, m_fix, n_fix + 1, i);
            position[i] = tmp;
        }
    }
}


int main(int ac, char **av){
    if (ac !=2) return 1;
    int m_fix = is_val(av[1]);
    rip(av[1], m_fix, 0, 0);
    return 0;
}