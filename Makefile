all:
	g++ main.c -o main -Wall -Werror -pthread -O0 -lpapi
	./main a b c 2

generate_data: generate_data.c
	g++ generate_data.c -o generate_data
	./generate_data 1000

clean_data:
	rm -f generate_data
	rm -f a
	rm -f b
	rm -f c
	rm -f ikj
	rm -f jik
	rm -f jki
	rm -f kij
	rm -f kji

test:
	chmod +x test.sh
	./test.sh

clean:
	rm -f main
