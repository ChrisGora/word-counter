list: list.h list.c
	gcc -DlistMain=main -std=c99 -pedantic -Wall -O3 list.c -o list
	./list
