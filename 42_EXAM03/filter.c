// filter:
// Allowed functions: read, strlen, malloc, calloc, realloc, free, printf, perror
// ------------------------------------------------------------------------------

// Write a programm taht will take one and only one argument s.

// Your programm will then read from stdin and write all the content read in stdout
// except that every occurence of s must be replaced by '*'.

// For example :

// ./filter bonjour
// will behave the same way as:
// sed 's/bonjour/*******/g'

// in case of error during read or a malloc you must write "Error: " followed by
// the error message in stderr and return 1.

// $> echo 'abcdefgaaaabcdefabc' | ./filter abc | cat -e
// ***defgaaa***def***

// If the program is called whitout argument or with an empty argument or with
// multiples arguments it must return 1.

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


int ft_strncmp(char *str, char *cmp, int len){
    int i = 0;
    while (str[i] && str[i] == cmp[i] && i < len){
        i++;    
    }
    if (i == len) return 0; //match found 
    return 1;
}


int main (int ac, char **av){
    if (ac != 2 || !av[1][0]) return 1;
    char *word = av[1];
    int len = strlen(av[1]);
    char *input = malloc(1);
    if(!input) return 1;
    int size = 4096;
    char buffer[size];
    char *tmp = NULL;
    int b_read = 0;
    int t_read= 0;

    while (1){
        tmp = realloc(input, size + t_read);
        if (!tmp) {
            perror("Error1");
            free(input);
            return 1;
        }
        input = tmp;
        
        b_read = read(0, buffer + t_read, size);
        if (b_read < 0){
            perror("Error2");
            free(input);
            return 1;
        }
        if (b_read == 0) break;
        for (int i = 0; i < b_read; i++){
            input[i+ t_read] = buffer[i];
        }
        t_read +=b_read;
    }

    input[t_read] = '\0';

    for (int i = 0; i < t_read;){
        if ( i+ len <=t_read &&ft_strncmp(input + i, word, len) == 0){
            for (int j = 0; j <len; j++){
                printf("*");
            }
            i += len;
        } else {
            printf("%c", input[i]);
            i++;
        }
    }
    free(input);
    return 0;
}