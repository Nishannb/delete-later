#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>



int ft_strncmp(char *str, char *cmp, int len){
    int i = 0;
    while (str[i] && str[i] == cmp[i] && i <len){
        i++;
    }
    if (i == len) return 0;
    return 1;
}


int main (int ac, char **av){
    if(ac != 2 || !av[1][0]){
        return 1;
    }
    char *word = av[1];
    int len = strlen(av[1]);
    if (!len){
        return 1;
    }
    int size = 4096;
    char buffer[size];
    char *tmp = NULL;
    char *input = malloc(1);
    if (!input){
        perror("Error: malloc error");
        return 1;
    }
    int b_read =0;
    int t_read= 0;

    while (1){
        tmp = realloc(input, size + t_read);
        if (!tmp){
            perror("Error: something realloc");
            free(input);
            return 1;
        }
        input = tmp;

        b_read = read(0, buffer + t_read, size);
        if (b_read < 0){
            perror("Error: error in reading");
            free(input);
            return 1;
        }
        if (b_read == 0) break;

        for (int i = 0; i < b_read; i++){
            input[i+t_read] = buffer[i];
        }

        t_read+= b_read;
    }

    input[t_read] = '\0';

    for (int i = 0; i < t_read; ){
        if (i + len <= t_read && ft_strncmp(input+i, word, len) == 0){
            for (int j = 0; j < len; j++){
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