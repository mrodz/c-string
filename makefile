CC=gcc

all: build
	run

run: build
	./my_string.exe

build: my_string.c main.c my_string.h
	$(CC) -o my_string main.c my_string.c -I.