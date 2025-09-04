#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#ifndef BUFFER_SIZE
    #define BUFFER_SIZE 42
#endif


char    *ft_strdup(const char *str)
{
    char    *copy;
    int        i;

    copy = (char *)malloc(sizeof(char) * strlen(str) + 1);
    if (copy == NULL)
        return (NULL);
    i = 0;
    while (str[i] != '\0')
    {
        copy[i] = str[i];
        i++;
    }
    copy[i] = '\0';
    return (copy);
}

char *get_next_line(int fd)
{
    static int b_read = 0; 
    static int pos = 0;
    char *line =  malloc(BUFFER_SIZE + 1);
    static char buffer[BUFFER_SIZE];
    char *temp_buffer = NULL;
    int index = 0;

    while (1337)
    {
        if (b_read <= pos){
            b_read = read(fd, buffer, BUFFER_SIZE);
            if (b_read > 0){
                temp_buffer = realloc(line, index + b_read);
                if(!temp_buffer) { free(line); return NULL; }
                line = temp_buffer;
            }
            pos = 0;
            if (b_read <= 0) break;
        }
        line[index++] = buffer[pos++];
        if (buffer[pos - 1] == '\n') break;
    }
    line[index] = '\0';
    if (index == 0) return NULL;
    // return (ft_strdup(line)); // might not need it
    return line;
}

int main (int ac, char **av)
{
    if(ac !=2) return 1;
    int fd = open(av[1], O_RDONLY);
    char *s = get_next_line(fd);
    if (s){
        printf("%s\n", s);
        free(s);
    }

}