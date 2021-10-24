#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void generate_data(int size){
    FILE *a;
    FILE *b;
    a = fopen("a", "w");
    b = fopen("b", "w");
    srand(time(NULL));
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            int tmp = 0;
            while (tmp < 10){
                tmp = rand() % 100;
            }
            fprintf(a, "%d ", tmp);
            //a[i * size + j] = tmp;
            tmp = 0;
            while (tmp < 10){
                tmp = rand() % 100;
            }
            fprintf(b, "%d ", tmp);
            //b[i * size + j] = tmp;
        }
    }
    fclose(a);
    fclose(b);
}

int main(){
    generate_data(10);
    return 0;
}
