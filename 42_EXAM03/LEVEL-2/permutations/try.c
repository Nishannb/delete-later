#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


void sorted(char *str){
	char tmp;
	for(int i = 0; str[i]; i++){
		for(int j = i+1; str[j]; j++){
			if(str[i] > str[j]){
				tmp = str[i];
				str[i] = str[j];
				str[j] = tmp;
			}
		}
	}
}


void swap(char *word, int i, int j){
    char tmp;
    if (word){
        tmp = word[i];
        word[i] = word[j];
        word[j] = tmp;
    }
}

void perm (char * word, int index) {
    int len = strlen(word);

    if (index >= len) {
        int in = 0;
        while (word[in]){
            write(1, &word[in], sizeof(word[in]));
            in++;
        }
        write(1, "\n", 1);
        return;
    };

    for (int j = index; j<len; j++){
        swap(word, index, j );
        perm(word, index + 1);
        swap(word, index, j );
    }
    
}

int main (int argc, char **argv)
{
    if (argc !=2) return (1);
    char *word;

    if (argc == 2){
        word = argv[1];
        sorted(word);
        perm(word, 0);
    }
    return (0);
}