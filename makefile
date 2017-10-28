all: 07.c
	gcc -g -o rand 07.c

run: all
	./rand
