.PHONY: list tst listC count

list: list.h list.c
	gcc -DlistMain=main -std=c99 -pedantic -Wall -O3 list.c -o list
	./list

tst: tst.h tst.c listC.h
	gcc -DtstMain=main -std=c99 -pedantic -Wall -O3 tst.c list.c -o tst
	./tst

count: count.c tst.h listC.h
	gcc -std=c99 -pedantic -Wall -O3 count.c tst.c list.c -o count
	./count t
