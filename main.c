#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <time.h>
#include <papi.h>

void get_data(int *a, int *b, int size, FILE* file_a, FILE* file_b){

    for (int i = 0; i < size * size; i++){
        fscanf(file_a, "%d", &a[i]);
        fscanf(file_b, "%d", &b[i]);
        if (feof(file_a)) break;
        if (feof(file_b)) break;
    }
}


void print(int *a, int size){
    printf("\n");
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            printf("%d ", a[i * size + j]);
        }
        printf("\n");
    }
    printf("\n");
}

void zero(int *a, int size){
    for (int i = 0; i < size * size; i++)
        a[i] = 0;
}

void multiply_ijk(int *a, int *b, int *c, int size){
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            for (int k = 0; k < size; k++){
                c[i * size + j] += a[i * size + k] * b[k * size + j];
            }
        }
    }
}

void multiply_ikj(int *a, int *b, int *c, int size){
    for (int i = 0; i < size; i++){
        for (int k = 0; k < size; k++){
            for (int j = 0; j < size; j++){
                c[i * size + j] += a[i * size + k] * b[k * size + j];
            }
        }
    }
}

void multiply_jik(int *a, int *b, int *c, int size){
    for (int j = 0; j < size; j++){
        for (int i = 0; i < size; i++){
            for (int k = 0; k < size; k++){
                c[i * size + j] += a[i * size + k] * b[k * size + j];
            }
        }
    }
}


void multiply_jki(int *a, int *b, int *c, int size){
    for (int j = 0; j < size; j++){
        for (int k = 0; k < size; k++){
            for (int i = 0; i < size; i++){
                c[i * size + j] += a[i * size + k] * b[k * size + j];
            }
        }
    }
}


void multiply_kij(int *a, int *b, int *c, int size){
    for (int k = 0; k < size; k++){
        for (int i = 0; i < size; i++){
            for (int j = 0; j < size; j++){
                c[i * size + j] += a[i * size + k] * b[k * size + j];
            }
        }
    }
}

void multiply_kji(int *a, int *b, int *c, int size){
    for (int k = 0; k < size; k++){
        for (int j = 0; j < size; j++){
            for (int i = 0; i < size; i++){
                c[i * size + j] += a[i * size + k] * b[k * size + j];
            }
        }
    }
}

int main(int argc, char **argv){

    FILE* file_a = fopen(argv[1], "r");
    FILE* file_b = fopen(argv[2], "r");

    char type_a = fgetc(file_a);
    char type_b = fgetc(file_b);

    if (type_a != type_b) { printf("Error, different matrix types\n"); return -1; }

    int size_a, size_b;
    fscanf(file_a, "%d", &size_a);
    fscanf(file_b, "%d", &size_b);

    if (size_a != size_b) { printf("Error, different matrix sizes"); return -1; }

    int size = size_a;

    int *a = (int *)calloc(size*size, sizeof(int));
    int *b = (int *)calloc(size*size, sizeof(int));
    int *c = (int *)calloc(size*size, sizeof(int));

    get_data(a, b, size, file_a, file_b);

    //print(a, size);
    //print(b, size);

    zero(c, size);

    clock_t start, stop;
    start = clock();

    long long L1_LOAD, L1_STORE, L1_CACHE, L2_LOAD, L2_STORE, L2_CACHE;
    int retval = 0;
    int event_set_L1_LOAD = PAPI_NULL;
    int event_set_L1_STORE = PAPI_NULL;
    int event_set_L1_CACHE = PAPI_NULL;

    int event_set_L2_LOAD = PAPI_NULL;
    int event_set_L2_STORE = PAPI_NULL;
    int event_set_L2_CACHE = PAPI_NULL;

    //Initialization

    retval = PAPI_library_init(PAPI_VER_CURRENT);
    if (retval != PAPI_VER_CURRENT) {
        fputs("failed to initialize PAPI\n", stderr);
        printf("%d %d\n", retval, PAPI_VER_CURRENT);
        return 1;
    }

    //Create eventset
    if (PAPI_create_eventset(&event_set_L1_LOAD) != PAPI_OK) {
        fputs("unable to create event set\n", stderr);
        return 2;
    }
    if (PAPI_create_eventset(&event_set_L1_STORE) != PAPI_OK) {
        fputs("unable to create event set\n", stderr);
        return 2;
    }
    if (PAPI_create_eventset(&event_set_L1_CACHE) != PAPI_OK) {
        fputs("unable to create event set\n", stderr);
        return 2;
    }
    if (PAPI_create_eventset(&event_set_L2_LOAD) != PAPI_OK) {
        fputs("unable to create event set\n", stderr);
        return 2;
    }
    if (PAPI_create_eventset(&event_set_L1_STORE) != PAPI_OK) {
        fputs("unable to create event set\n", stderr);
        return 2;
    }
    if (PAPI_create_eventset(&event_set_L1_CACHE) != PAPI_OK) {
        fputs("unable to create event set\n", stderr);
        return 2;
    }

    //Add eventset

    if (PAPI_add_event(event_set_L1_LOAD, PAPI_L1_LDM) != PAPI_OK) {
        fputs("can't add event\n", stderr);
        return 3;
    }
    if (PAPI_add_event(event_set_L1_STORE, PAPI_L1_STM) != PAPI_OK) {
        fputs("can't add event\n", stderr);
        return 3;
    }
    if (PAPI_add_event(event_set_L1_CACHE, PAPI_L1_TCM) != PAPI_OK) {
        fputs("can't add event\n", stderr);
        return 3;
    }
    if (PAPI_add_event(event_set_L2_LOAD, PAPI_L2_LDM) != PAPI_OK) {
        fputs("can't add event\n", stderr);
        return 3;
    }
    if (PAPI_add_event(event_set_L2_STORE, PAPI_L2_STM) != PAPI_OK) {
        fputs("can't add event\n", stderr);
        return 3;
    }
    if (PAPI_add_event(event_set_L2_CACHE, PAPI_L2_TCM) != PAPI_OK) {
        fputs("can't add event\n", stderr);
        return 3;
    }

    //Start
    if (PAPI_start(event_set_L1_LOAD) != PAPI_OK) {
        fputs("failed to start counters\n", stderr);
        return 4;
    }
    if (PAPI_start(event_set_L1_STORE) != PAPI_OK) {
        fputs("failed to start counters\n", stderr);
        return 4;
    }
    if (PAPI_start(event_set_L1_CACHE) != PAPI_OK) {
        fputs("failed to start counters\n", stderr);
        return 4;
    }
    if (PAPI_start(event_set_L2_LOAD) != PAPI_OK) {
        fputs("failed to start counters\n", stderr);
        return 4;
    }
    if (PAPI_start(event_set_L2_STORE) != PAPI_OK) {
        fputs("failed to start counters\n", stderr);
        return 4;
    }
    if (PAPI_start(event_set_L2_CACHE) != PAPI_OK) {
        fputs("failed to start counters\n", stderr);
        return 4;
    }

    //Code
    if (atoi(argv[4]) == 0)
            multiply_ijk(a, b, c, size);

    else if (atoi(argv[4]) == 1)
            multiply_ikj(a, b, c, size);

    else if (atoi(argv[4]) == 2)
            multiply_kij(a, b, c, size);

    else if (atoi(argv[4]) == 3)
            multiply_jik(a, b, c, size);

    else if (atoi(argv[4]) == 4)
            multiply_jki(a, b, c, size);

    else if (atoi(argv[4]) == 5)
            multiply_kji(a, b, c, size);


    //Stop
    if (PAPI_stop(event_set_L1_LOAD, &L1_LOAD) != PAPI_OK) {
        fputs("error in stop counters 1\n", stderr);
        return 5;
    }
    if (PAPI_stop(event_set_L1_STORE, &L1_STORE) != PAPI_OK) {
        fputs("error in stop counters 1\n", stderr);
        return 5;
    }
    if (PAPI_stop(event_set_L1_CACHE, &L1_CACHE) != PAPI_OK) {
        fputs("error in stop counters 1\n", stderr);
        return 5;
    }
    if (PAPI_stop(event_set_L2_LOAD, &L2_LOAD) != PAPI_OK) {
        fputs("error in stop counters 1\n", stderr);
        return 5;
    }
    if (PAPI_stop(event_set_L2_STORE, &L2_STORE) != PAPI_OK) {
        fputs("error in stop counters 1\n", stderr);
        return 5;
    }
    if (PAPI_stop(event_set_L2_CACHE, &L2_CACHE) != PAPI_OK) {
        fputs("error in stop counters 1\n", stderr);
        return 5;
    }

    //Print
    printf("L1 LOAD = %lld \n"
            "L1 STORE = %lld \n"
            "L1 CACHE = %lld \n"
            "L2 LOAD = %lld \n"
            "L2 STORE = %lld \n"
            "L2 CACHE = %lld \n",
            L1_LOAD, L1_STORE, L1_CACHE,
            L2_LOAD, L2_STORE, L2_CACHE);

    stop = clock();
    double seconds = (double)(stop - start) / CLOCKS_PER_SEC;
    printf("%f\n", seconds);

    //print(c, size);

    FILE* file_c = fopen(argv[3], "w");
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            fprintf(file_c, "%d ", c[i * size + j]);
        }
    }

    free(a);
    free(b);
    free(c);

    return 0;
}
