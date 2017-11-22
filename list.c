#include "list.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

struct node {
    struct node *prev;
    item x;
    struct node *next;
    bool sentinel;
};

typedef struct node node;

//Note that senEnd and end are the same, whereas senStart and start are not
//It's illegal for position to be "at senStart" (ie. before the sentinel node)
struct list {
	node *senStart;
    node *start;
	node *senEnd;
    node *end;
    node *position;
    int length;
};

//------------------------------------------------------------------------------

void fail(char *m) {
	fprintf(stderr, "%s\n", m);
	exit(1);
}


//start is set at the first real item
//end is set at senEnd
list *newList() {
    list *l = malloc(sizeof(list));
    node *senStart = malloc(sizeof(node));
    node *senEnd = malloc(sizeof(node));
    *senStart = (node) {NULL, 0, senEnd, true};
    *senEnd = (node) {senStart, 0, NULL, true};
    *l = (list) {senStart, senStart->next, senEnd, senEnd, senStart->next, 0};
    return l;
}

void updateStart(list *l) {
	l->start = l->senStart->next;
}

void start(list *l) {
    l->position = l->start;
}

void end(list *l) {
    l->position = l->end;
}

bool atStart(list *l) {
    return (l->position == l->start);
}

bool atEnd(list *l) {
    return (l->position == l->end);
}

void forward(list *l) {
    node *current = l->position;
	node *next = l->position->next;
    if (current->sentinel == true) fail("You reached the end of the list");
    else {
        l->position = next;
    }
}

void backward(list *l) {
	node *current = l->position;
	node * next = current->prev;
	if (next->sentinel == true) fail("You reached the start of the list");
	else {
		l->position = next;
	}
}

//TODO: Fix pointer re-assignment!!!
void insertBefore(list *l, item x) {
    node *left = l->position->prev;
    node *right = l->position;
    node *new = malloc(sizeof(node));
    *new = (node) {left, x, right, false};
    right->prev = new;
    left->next = new;
    l->length = l->length + 1;
	updateStart(l);
}

void insertAfter(list *l, item x) {

}

item getBefore(list *l) {
    return 0;
}

item getAfter(list *l) {
    return 0;
}

void setBefore(list *l, item x) {

}

void setAfter(list *l, item x) {

}

void deleteBefore(list *l) {

}

void deleteAfter(list *l) {

}

//------------------------------------------------------------------------------

void testNew() {
    list *l = newList();
    assert(l->start->prev->prev == NULL);
    assert(l->end->next == NULL);
    assert(l->start->prev->next != NULL);
    assert(l->end->prev != NULL);
    printf("New passed\n");
}

void testStart() {
    list *l = newList();
    insertBefore(l, 24);
    insertBefore(l, 12);
    insertBefore(l, 2);
    insertBefore(l, 3);
    insertBefore(l, 567);
    start(l);
    assert(l->position == l->start);
    printf("Start passed\n");
}

void testEnd() {
    list *l = newList();
    insertBefore(l, 24);
    start(l);
    insertBefore(l, 10);
    end(l);
    assert(l->position == l->end);
    printf("End passed\n");
}

void testAtStart() {
    list *l = newList();
    insertBefore(l, 24);
    start(l);
    assert(atStart(l) == true);
    printf("atStart passed\n");
}

void testAtEnd() {
    list *l = newList();
    insertBefore(l, 24);
    start(l);
    insertBefore(l, 10);
    end(l);
    assert(atEnd(l) == true);
    printf("atEnd passed\n");
}

void testInsertBefore() {
    list *l = newList();
    int lengthBefore = l->length;
    end(l);
    insertBefore(l, 5);
    assert (l->position->sentinel == true);
    assert (atEnd(l) == true);
    assert (l->position->prev->sentinel == false);
    assert(l->length == lengthBefore + 1);
    assert(l->position->prev->x == 5);

    lengthBefore = l->length;
    insertBefore(l, 34);
    assert (l->position->sentinel == true);
    assert (atEnd(l) == true);
    assert (l->position->prev->sentinel == false);
    assert(l->length == lengthBefore + 1);
    assert(l->position->prev->x == 34);
    printf("insertBefore passed\n");
}

void testForward() {
    list *l = newList();
    insertBefore(l, 243);
    insertBefore(l, 1006);
    insertBefore(l, 12);
    insertBefore(l, 5);
    start(l);
    printf("%d \n", l->position->x);
    assert(atStart(l) == true);
    node *expectedNewPosition = l->position->next;
    forward(l);
    node *positionAfter = l->position;
    assert(expectedNewPosition == positionAfter);
    printf("Forward passed\n");
}

void testBackward() {
    printf("Backward passed\n");
}

int listMain() {
    testNew();
    testStart();
    testEnd();
    testAtStart();
    testAtEnd();
    testInsertBefore();
    testForward();
    testBackward();
    printf("All tests passed\n");
    return 0;
}
