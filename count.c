// This program takes a *.txt file and counts how many times each word occurs.
// The results are stored in a TST.

#include "tst.h"
#include "listC.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

struct count {
    list *l;
    tst *t;
	bool debug;
};

typedef struct count count;

count *newEmptyCount(bool debug) {
    count *c = malloc(sizeof(count));
    list *l = newList();
    c->l = l;
    tst *t = newTst();
    c->t = t;
	c->debug = debug;
    return c;
}

void readAllChars(count *c) {
    FILE *in = fopen("input.txt", "r");
    char ch = fgetc(in);
    while (! feof(in)) {
        insertBefore(c->l, ch);
        if (c->debug) printf("%c\n", ch);
        ch = fgetc(in);
    }
    fclose(in);
}

void convert(count *c) {
    int length = getLength(c->l);
    int i = 0;
    start(c->l);
    while (!atEnd(c->l)) {
		if (c->debug) printf("length %d i %d\n", length, i);
        char ch = getAfter(c->l);
		if (c->debug) printf("before %c \n", ch);
		bool deleted = false;
        if ((ch >= 'A') && (ch <= 'Z')) setAfter(c->l, (ch - 'A' + 'a'));
        else if (!isspace(ch) && ((ch < 'a') || (ch > 'z'))) {
			deleteAfter(c->l);
			deleted = true;
		}
		ch = getAfter(c->l);
		if (c->debug) printf("after %c\n", ch);
		if (!atEnd(c->l) && !deleted) forward(c->l);
    }
}

void insertAll(count *c) {
	int length = getLength(c->l);
    start(c->l);
	char buffer[50];
	int position = 0;
	while (!atEnd(c->l)) {
		int i = 0;
		while (! isspace(getAfter(c->l))) {
			if (c->debug) printf("i = %d\n", i);
			buffer[i] = getAfter(c->l);
			if (c->debug) printf("buffer [i] = %c\n", buffer[i]);
			i++;
			position++;
			forward(c->l);
		}
		buffer[i] = '\0';
		if (strlen(buffer) != 0) {
			if (c->debug) printf("I'm okay 2!\n");
			int foundX = search(c->t, buffer);
			if (c->debug) printf("I'm okay!\n");
			if (foundX == - 1) insertString(c->t, 1, buffer);
			else {
				node *n = findNode(c->t, buffer);
				int x = foundX + 1;
				amend(n, x);
			}
		}
		else if (position < length) forward(c->l);
	}
}

void get(int max, char line[max]) {
    printf("KEY: ");
    fgets(line, max, stdin);
	int length = strlen(line);
	if (line[length - 1] == '\n') line[length - 1] = '\0';
}

//------------------------------------------------------------------------------

void testRead() {
    count *c = newEmptyCount(true);
    readAllChars(c);
    assert(getLength(c->l) == 139);
    start(c->l);
    assert(getAfter(c->l) == 'T');
    end(c->l);
    assert(getBefore(c->l) == '\n');
    printf("testRead passed\n");
}

void testConvert() {
    count *c = newEmptyCount(true);
    readAllChars(c);
	convert(c);
    start(c->l);
    assert(getAfter(c->l) == 't');
	printf("testConvert passed\n");
}

void testInsert() {
	count *c = newEmptyCount(true);
    readAllChars(c);
	convert(c);
	printf("convert passed\n");
	insertAll(c);
	assert(search(c->t, "test") == 1);
	assert(search(c->t, "testing") == 3);
	assert(search(c->t, "tests") == -1);
	printf("testInsert passed\n");
}

void tests() {
    testRead();
	testConvert();
	testInsert();
    printf("All tests PASSED\n");
}

//------------------------------------------------------------------------------
int main(int n, char *args[n]) {
    if (n > 1) tests();
    else {
        count *c = newEmptyCount(false);
        readAllChars(c);
		convert(c);
		insertAll(c);
		int max = 50;
		char key[max];
		while (true) {
			get(max, key);
			int x = search(c->t, key);
			if (x == - 1) printf("NOT FOUND\n");
			else printf("VALUE: %d\n", x);
		}
    }
    return 0;
}
