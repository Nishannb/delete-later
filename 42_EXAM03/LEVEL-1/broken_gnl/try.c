#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

#ifndef BUFFER_SIZE
    #define BUFFER_SIZE 42
#endif


char *ft_strdup(char *line)
{
    if (!line) return (NULL);
    int index = 0;

    char *copy = (char *) malloc(sizeof(char) * strlen(line) + 1);
    // copy = (char *) malloc(sizeof(char) * strlen(str) + 1);
    if(!copy) return (NULL);

    while (line[index]){
        copy[index] = line[index];
        index++;
    }
    copy[index] = '\0';
    return (copy);
}


char *get_next_line(int fd)
{
    if (fd < 0 || BUFFER_SIZE <= 0) return (NULL);
    static char buffer[BUFFER_SIZE];
    static int read_postion = 0;
    static int position = 0;
    char *line = malloc(BUFFER_SIZE + 1);
    int index = 0;

    while (1337)
    {
        if (read_postion <= position)
        {
            read_postion = read(fd, buffer, BUFFER_SIZE);
            if (read_postion <= 0) break;
        }
        line[index++] = buffer[position++];
        if (buffer[position - 1] == '\n') break;
    }
    line[index] = '\0';
    if (index == 0) return (NULL);
    return (ft_strdup(line));
}

int main( int argc, char **argv){
    if (argc != 2)
        return (1);
    int fd = open(argv[1], O_RDWR);
    printf("%s\n", get_next_line(fd));
    printf("%s\n", get_next_line(fd));
    // get_next_line(fd);
    // get_next_line(fd);
    // get_next_line(fd);
}
