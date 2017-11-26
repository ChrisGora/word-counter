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

struct count {
    list* l;
    tst *t;
};

typedef struct count count;

count *newEmptyCount() {
    count *c = malloc(sizeof(count));
    list *l = newList();
    c->l = l;
    tst *t = newTst();
    c->t = t;
    return c;
}

void readAllChars(count *c) {
    FILE *in = fopen("input.txt", "r");
    char ch = fgetc(in);
    while (! feof(in)) {
        insertBefore(c->l, ch);
        printf("%c\n", ch);
        ch = fgetc(in);
    }
    fclose(in);
}

void convert(count *c) {
    int length = getLength(c->l);
    int i = 0;
    start(c->l);
    while (i < length) {
        char ch = getAfter(c->l);
        if ((ch >= 'A') && (ch <= 'Z')) setAfter(c->l, ch - 'A' + 'a');
        if ()
    }
}

//------------------------------------------------------------------------------
void testRead() {
    count *c = newEmptyCount();
    readAllChars(c);
    assert(getLength(c->l) == 139);
    start(c->l);
    assert(getAfter(c->l) == 'T');
    end(c->l);
    assert(getBefore(c->l) == '\n');
    printf("testRead passed\n");
}

void tests() {
    testRead();
    printf("All tests PASSED\n");
}

//------------------------------------------------------------------------------
int main(int n, char *args[n]) {
    if (n > 1) tests();
    else {
        count *c = newEmptyCount();
        readAllChars(c);
    }
    return 0;
}
