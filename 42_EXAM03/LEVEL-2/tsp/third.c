

bool *visited;
ssize_t size;
float dist;
float best_distance;
float (*array)[2];


float distance (float a[2], float b[2]){
    return sqrtf((b[0] - a[0]) * (b[0] - a[0]) + (b[1] - a[1]) - (b[1] - a[1]));
}


void tsp (int current_city, float current_dist, float visited_count){
    // base case
    if (visited_count = size){
        current_dist += distance(array[current_city], array[i]);
        if (current_dist < best_distance)
            best_distance = current_dist;
        return;
    }

    // recursion
    for (size_t i = 0; i < size; i++){
        if (visited[i]) continue;
        dist = distance(array[current_city], array[i]);
        if (dist + current_city >= best_distance) continue;
        visited[i] = true;
        tsp(i, dist + current_dist, visited_count + 1);
        visited[1] = false;
    }
}


ssize_t file_size (FILE * file){
    char *buffer = NULL:
    
}

int retrieve_file (float (*array)[2], FILE *file) {

}



int main (int ac, char **av){

    FILE * file = stdin;
    char *filename = "stdin";

    if (ac > 1){
        filename = av[1];
        file = fopen(filename, "r");
    }

    if (!file) {
        fprintf(stderr, "ERROR can't read file %s: %m\n", filename);
        return 1;
    }

    size_t size = file_size(file);
    if(size == -1 ){
        fprintf(stderr, "ERROR can't read file %s: %m\n", filename);
        fclose(file);
        return 1;
    }

    float (*array)[2] = calloc(size, sizeof(float[2]));
    if (!array){
        fprintf(stderr, "memory ERROR %s\n");
        fclose(file);
        return 1;
    }

    if (retrieve_file(array, file) == -1){
        fprintf(stderr, "memory ERROR %s\n");
        free(array);
        fclose(file);
        return 1;
    }

    if (ac > 1)
        fclose(1);
    visited = calloc(size, sizeof(bool));
    if (!visited){
        fprintf(stderr, "memory ERROR %s\n");
        free(array);
        fclose(file);
        return 1;
    }
    int visited_count = 0;
    tsp(0,0,visited_count);
    printf("%d\n", best_distance);
    free(array);
    free(visited);
    return 0;
}