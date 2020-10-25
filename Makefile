CC = cc
CFLAGS = -Wall

all: main

out:
	[ -d out ] || mkdir out

out/randutils.o: out src/randutils.h src/randutils.c
	$(CC) $(CFLAGS) -c src/randutils.c
	mv randutils.o out/

out/aloha.o: out/randutils.o src/aloha.h src/aloha.c
	$(CC) $(CFLAGS) -c src/aloha.c
	mv aloha.o out/

main: out/aloha.o src/main.c
	$(CC) $(CFLAGS) -o out/main out/randutils.o out/aloha.o src/main.c

run: main
	out/main

clean:
	rm -rf out/
