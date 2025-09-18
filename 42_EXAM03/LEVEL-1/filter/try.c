#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include  <stdlib.h>


// $> echo 'abcdefgaaaabcdefabc' | ./a abc | cat -e
// ***defgaaa***def***

#ifndef BUFFER_SIZE
    #define BUFFER_SIZE 42
#endif



int ft_strncmp(const char *compare, char *to, int len){
   
    int i = 0;
    while (i < len){
        if(compare[i] != to[i]){
            return (0);
        }
        i++;
    }
    return (1);
}


int main (int argc, char **argv)
{
    if (argc != 2) return (1);

    char *word = argv[1];
    char *input = malloc(1);
    if (!input) return (perror("Error occured"), 1);
    char *buffer = malloc(BUFFER_SIZE);
    if (!buffer) return  (perror("Error occured"), free(input), 1);

    int read_s;
    int total_read = 0;
    while ((read_s = read(0, buffer, BUFFER_SIZE)) > 0){
        char *collect = realloc(input, total_read+ read_s + 1);
        if (!collect) return (perror("Error occured"), free(input), free(buffer),  1);
       
        input = collect;
        int i = 0;
        while (i < read_s)
        {
            input[total_read + i] = buffer[i];
            i++;
        }
        total_read += read_s;
        input[total_read] = '\0';
       
    };
    free(buffer);

    char *ptr = input;
    int len = strlen(word);
    while (*ptr){
        if(ft_strncmp(ptr, word, len) == 1){
            int i = 0;
            while (i < len){
                printf("*");
                i++;
                ptr++;
            }
        } else printf("%c", *ptr);
        
        ptr++;
    }
    free(input);
    return (0);
}