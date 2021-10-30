all:
	g++ main.c -o main -Wall -Werror -pthread -O0
	./main a b c 0

generate_data: generate_data.c
	g++ generate_data.c -o generate_data
	./generate_data 1000

clean_data:
	rm generate_data
	rm a
	rm b
	rm c
	rm ikj
	rm jik
	rm jki
	rm kij
	rm kji

test:
	chmod +x test.sh
	./test.sh

clean:
	rm main
