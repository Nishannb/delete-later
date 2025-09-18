#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#ifndef BUFFER_SIZE
    #define BUFFER_SIZE 42
#endif



int main (int ac, char **av){
    if (ac != 2) return 1;
    char *word= av[1];
    char *input = malloc(1);
    char *buffer = malloc(BUFFER_SIZE);
    int read_s = 0;
    int total_read = 0;
    char *temp

    while ((read_s = read(0, buffer, BUFFER_SIZE)) > 0){

    }



}