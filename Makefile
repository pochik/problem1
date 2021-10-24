all:
	g++ main.c -o main
	./main

generate_data: generate_data.c
	g++ generate_data.c -o generate_data
	./generate_data

clean:
	rm main
	rm generate_data
	rm a
	rm b
