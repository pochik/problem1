all:
	g++ main.c -o main -Wall -Werror -pthread -O0 -fsanitize=address
	./main a b c 0

generate_data: generate_data.c
	g++ generate_data.c -o generate_data
	./generate_data

clean:
	rm main
