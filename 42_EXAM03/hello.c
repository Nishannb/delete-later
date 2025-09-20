
char *get_next_line(int fd){
    static char b[BUFFER_SIZE + 1] = "";
    char *res;
    char *tmp;

    ssize_t bytes_read;

    if (fd < 0) return NULL;

    res = NULL;
    tmp = ft_strchr(b, '\n');
    while (!tmp){
        if (!str_append_str(&res, b))
        {
            free(res);
            return NULL;
        }

        bytes_read = read(fd, b, BUFFER_SIZE);
        if (bytes_read < 0) {
            free(res);
            return NULL;
        }

        if (bytes_read == 0) break;
        b[bytes_read] = '\0';
        tmp = ft_strchr(b, '\n');
    }
    if (tmp){
        if (!str_append_mem(&res, b, (tmp -b) + 1)){
            free(res);
            return NULL;
        }
        ft_memcpy(b, tmp + 1, ft_strlen(tmp + 1) + 1);
    } else if (res && ft_strlen(res) > 0){
        b[0] = '\0';
        return res;
    }
    else {
        free(res);
        return NULL;
    }
    return res;
}