#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int        ft_strncmp(const char *s1, const char *s2, size_t n)
{
        size_t        i;

        i = 0;
        while (s1[i] == s2[i] && i < n)
        {
                i++;
        }
        if (i == n)
                return (0);
        return (s1[i] - s2[i]);
}


int        main(int argc, char **argv)
{
        ssize_t        bytes_read;
        char        read_buf;
        char        *buf;
        char        *tmp;
        ssize_t        size;
        ssize_t        i;
        size_t        j;

        i = 0;
        size = 1;
        if (argc != 2)
        {
                return (printf("Argv Error\n"), 1);
        }
        buf = malloc(sizeof(char) * size);
        if (!buf)
        {
                perror("Error");
                return (1);
        }
        bytes_read = 1;
        while ((bytes_read = read(STDIN_FILENO, &read_buf, 1)) > 0)
        {
                if (read_buf == '\n')
                        continue ;
                if (i >= size)
                {
                        size *= 2;
                        tmp = realloc(buf, size);
                        if (!tmp)
                        {
                                free(buf);
                                perror("Error");
                                return (1);
                        }
                        buf = tmp;
                }
                buf[i++] = read_buf;
        }
        if (bytes_read < 0)
        {
                free(buf);
                perror("Error:");
                return (1);
        }
        buf[i] = '\0';
        i = 0;
        while (buf[i] != '\0')
        {
                if (ft_strncmp(argv[1], &(buf[i]), strlen(argv[1])) == 0)
                {
                        j = 0;
                        while (j < strlen(argv[1]))
                        {
                                buf[j + i] = '*';
                                j++;
                        }
                }
                i++;
        }
        printf("%s\n", buf);
        free(buf);
        return (0);
}