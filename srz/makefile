all: main

./output/utils.o: ./src/utils.h ./src/utils.c
	gcc -c -o ./output/utils.o -Wall ./src/utils.c

./output/aloha.o: ./src/aloha.h ./src/aloha.c
	gcc -c -o ./output/aloha.o -Wall ./src/aloha.c

main: ./output/utils.o ./output/aloha.o ./src/main.c
	gcc -Wall -o main ./output/aloha.o ./output/utils.o ./src/main.c
