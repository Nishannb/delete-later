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
    if (!line) return NULL;

    int index = 0;
    char *copy = (char *) malloc(sizeof(char) * (strlen(line) + 1));
    if (!copy) return NULL;

    while (line[index])
    {
        copy[index] = line[index];
        index++;
    }
    copy[index] = '\0';
    return copy;
}

char *get_next_line(int fd)
{
    if (fd < 0 || BUFFER_SIZE <= 0) return NULL;

    static char buffer[BUFFER_SIZE];
    static int read_position = 0;
    static int position = 0;

    char *line = malloc(BUFFER_SIZE + 1);
    if (!line) return NULL;

    int index = 0;

    while (1)
    {
        if (read_position <= position)
        {
            read_position = read(fd, buffer, BUFFER_SIZE);
            position = 0;
            if (read_position <= 0) break;
        }

        line[index++] = buffer[position++];
        if (buffer[position - 1] == '\n') break;

        // Expand line buffer if needed
        if (index >= BUFFER_SIZE)
        {
            char *tmp = realloc(line, index + BUFFER_SIZE + 1);
            if (!tmp)
            {
                free(line);
                return NULL;
            }
            line = tmp;
        }
    }

    if (index == 0)
    {
        free(line);
        return NULL;
    }

    line[index] = '\0';

    char *result = ft_strdup(line); // duplicate to mimic original behavior
    free(line); // free original to prevent leak

    return result;
}

int main(int argc, char **argv)
{
    if (argc != 2) return 1;

    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) return 1;

    char *line;
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line); // free after use
    }

    close(fd);
    return 0;
}
