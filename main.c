#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void generate_data(int *a, int *b, int size){
    srand(time(NULL));
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            int tmp = 0;
            while (tmp < 10){
                tmp = rand() % 100;
            }
            a[i * size + j] = tmp;
            tmp = 0;
            while (tmp < 10){
                tmp = rand() % 100;
            }
            b[i * size + j] = tmp;
        }
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

void multiply(int *a, int *b, int *c, int size){
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            c[i * size + j] = 0;
            for (int k = 0; k < size; k++){
                c[i * size + j] += a[i * size + k] * b[k * size + j];
            }
        }
    }
}

int main(int argc, char **argv){

    int size = 2;

    int *a = (int *)calloc(size*size, sizeof(int));
    int *b = (int *)calloc(size*size, sizeof(int));
    int *c = (int *)calloc(size*size, sizeof(int));

    generate_data(a, b, size);
    print(a, size);
    print(b, size);

    multiply(a, b, c, size);
    print(c, size);

    return 0;
}
