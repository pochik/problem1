#!/bin/bash

g++ generate_data.c -o generate_data -Wall -Werror -pthread -O0 -fsanitize=address
./generate_data 2

g++ main.c -o main -Wall -Werror -pthread -O0 -fsanitize=address

./main a b c 0

./main a b ikj 1
diff ikj c

./main a b kij 2
diff kij c

./main a b jik 3
diff jik c

./main a b jki 4
diff jki c

./main a b kji 5
diff kji c
