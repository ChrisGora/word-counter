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

static void fail(char *m) {
	fprintf(stderr, "%s\n", m);
	exit(1);
}

list *newList() {
    list *l = malloc(sizeof(list));
    node *senStart = malloc(sizeof(node));
    node *senEnd = malloc(sizeof(node));
    *senStart = (node) {NULL, 0, senEnd, true};
    *senEnd = (node) {senStart, 0, NULL, true};
    *l = (list) {senStart, senStart->next, senEnd, senEnd, senStart->next, 0};
    return l;
}

static void updateStart(list *l) {
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
	node *next = current->next;
    if (current->sentinel) fail("You are at the end of the list");
    else {
        l->position = next;
    }
}

void backward(list *l) {
	node *current = l->position;
	node *next = current->prev;
	if (next->sentinel) fail("You are at the start of the list");
	else {
		l->position = next;
	}
}

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
	insertBefore(l, x);
	backward(l);
}

//TODO: Add errors!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
item getBefore(list *l) {
  backward(l);
  return getAfter(l);
}

item getAfter(list *l) {
  node *current = l->position;
  if (current->sentinel) fail("You are at the end of the list");
	return current->x;
}

void setBefore(list *l, item x) {
	node *current = l->position;
	node *left = current->prev;
	if (left->sentinel) fail("You are at the start of the list");
	else left->x = x;
}

void setAfter(list *l, item x) {
	node *current = l->position;
	if (current->sentinel) fail("You are at the end of the list");
	else current->x = x;
}

void deleteBefore(list *l) {
  node *right = l->position;
  node *delete = right->prev;
	node *left = delete->prev;
	if (!(delete->sentinel)) {
		free(delete);
    right->prev = left;
    left->next = right;
    l->length = l->length - 1;
		updateStart(l);
	}
	else fail("You are at the start of the list");
}

//Note that there will still be an error if you try to delete at the end of the
// list. It will just come from the forward function.
void deleteAfter(list *l) {
	forward(l);
	deleteBefore(l);
}

//------------------------------------------------------------------------------

static void assertPosition(list *l, char* c) {
	node *current = l->position;
	node *prev = current->prev;
	int posArray = strstr(c, "|") - c;
	printf("%c \n", c[posArray]);
	printf("posArray %d\n", posArray);
	if (!(current->sentinel)) assert(c[posArray + 1] - '0' == current->x);
	if (!(prev->sentinel)) assert(c[posArray - 1] - '0' == current->prev->x);
}

static void assertElementsForward(list *l, char* c) {
	int i = 0;
	int length = strlen(c);
	node *current = l->start;
	while (i < length) {
		if (c[i] != '|') {
			int fromArray = c[i] - '0';
			int fromList = current->x;
			printf("fromArray %d \n", fromArray);
			printf("fromList %d \n", fromList);
			assert(fromArray == fromList);
			current = current->next;
		}
		i++;
	}
}

static void assertElementsBackward(list *l, char* c) {
	int length = strlen(c) - 1;
	node *current = l->end->prev;
	while (length >= 0) {
		if (c[length] != '|') {
			int fromArray = c[length] - '0';
			int fromList = current->x;
			printf("fromArray %d \n", fromArray);
			printf("fromList %d \n", fromList);
			assert(fromArray == fromList);
			current = current->prev;
		}
		length--;
	}
}

static void compare(list *l, char* c) {
	assertPosition(l, c);
	assertElementsForward(l, c);
	assertElementsBackward(l, c);
	printf("Compare of %s passed\n", c);
}

static void testNew() {
    list *l = newList();
    assert(l->start->prev->prev == NULL);
    assert(l->end->next == NULL);
    assert(l->start->prev->next != NULL);
    assert(l->end->prev != NULL);
	compare(l, "|");
    printf("New passed\n");
}

static void testStart() {
    list *l = newList();
    insertBefore(l, 2);
    insertBefore(l, 1);
    insertBefore(l, 2);
    insertBefore(l, 3);
    insertBefore(l, 5);
    start(l);
    assert(l->position == l->start);
	compare(l, "|21235");
    printf("Start passed\n");
}

static void testEnd() {
    list *l = newList();
    insertBefore(l, 2);
    start(l);
    insertBefore(l, 1);
	compare(l, "1|2");
    end(l);
    assert(l->position == l->end);
	compare(l, "12|");
    printf("End passed\n");
}

static void testAtStart() {
    list *l = newList();
    insertBefore(l, 2);
    start(l);
    assert(atStart(l) == true);
	compare(l, "|2");
    printf("atStart passed\n");
}

static void testAtEnd() {
    list *l = newList();
    insertBefore(l, 4);
    start(l);
    insertBefore(l, 7);
	compare(l, "7|4");
    end(l);
    assert(atEnd(l) == true);
	compare(l, "74|");
	printf("atEnd passed\n");
}

static void testInsertBefore() {
    list *l = newList();
    int lengthBefore = l->length;
    end(l);
    insertBefore(l, 5);
	compare(l, "5|");
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

static void testForward() {
    list *l = newList();
    insertBefore(l, 2);
    insertBefore(l, 1);
    insertBefore(l, 1);
    insertBefore(l, 5);
	compare(l, "2115|");
    start(l);
	compare(l, "|2115");
    printf("%d \n", l->position->x);
    assert(atStart(l) == true);
    node *expectedNewPosition = l->position->next;
    forward(l);
    node *positionAfter = l->position;
    assert(expectedNewPosition == positionAfter);
	compare(l, "2|115");
    printf("Forward passed\n");
}

static void testBackward() {
    list *l = newList();
    insertBefore(l, 2);
    insertBefore(l, 1);
    insertBefore(l, 1);
    insertBefore(l, 5);
	compare(l, "2115|");
	backward(l);
	compare(l, "211|5");
	backward(l);
	compare(l, "21|15");
    printf("Backward passed\n");
}

static void testInsertAfter() {
    list *l = newList();
    int lengthBefore = l->length;
    end(l);
    insertAfter(l, 5);
	compare(l, "|5");
    assert (l->position->sentinel == false);
    assert (atStart(l) == true);
	assert(l->position->x == 5);
    assert (l->position->prev->sentinel == true);
    assert(l->length == lengthBefore + 1);

    lengthBefore = l->length;
    insertAfter(l, 3);
	compare(l, "|35");
    assert (l->position->sentinel == false);
    assert (atStart(l) == true);
    assert (l->position->prev->sentinel == true);
    assert(l->length == lengthBefore + 1);
    printf("insertAfter passed\n");
}

static void testSetBefore() {
    list *l = newList();
    insertBefore(l, 2);
    insertBefore(l, 1);
    insertBefore(l, 1);
    insertBefore(l, 5);
	compare(l, "2115|");
	backward(l);
	compare(l, "211|5");
	setBefore(l, 2);
	compare(l, "212|5");
}

static void testSetAfter() {
    list *l = newList();
    insertBefore(l, 2);
    insertBefore(l, 1);
    insertBefore(l, 1);
    insertBefore(l, 5);
	compare(l, "2115|");
	backward(l);
	compare(l, "211|5");
	setAfter(l, 2);
	compare(l, "211|2");
}

static void testDelete() {
	list *l = newList();
    insertBefore(l, 3);
    insertBefore(l, 6);
    insertBefore(l, 9);
    insertBefore(l, 2);
	compare(l, "3692|");
	backward(l);
	backward(l);
	compare(l, "36|92");
	deleteBefore(l);
	compare(l, "3|92");
	deleteBefore(l);
	compare(l, "|92");
	deleteAfter(l);
	compare(l, "|2");
	deleteAfter(l);
	compare(l, "|");
}
/*
static void manualErrorTest1() {
	list *l = newList();
	insertBefore(l, 3);
    insertBefore(l, 6);
	deleteAfter(l);
}

static void manualErrorTest2() {
	list *l = newList();
	insertAfter(l, 3);
    insertAfter(l, 6);
	deleteBefore(l);
}

static void manualErrorTest3() {
	list *l = newList();
	insertBefore(l, 3);
    insertBefore(l, 6);
	forward(l);
}

static void manualErrorTest4() {
	list *l = newList();
	insertAfter(l, 3);
    insertAfter(l, 6);
	backward(l);
}
*/
int listMain() {
    testNew();
    testStart();
    testEnd();
    testAtStart();
    testAtEnd();
    testInsertBefore();
    testForward();
    testBackward();
	testInsertAfter();
	testSetBefore();
	testSetAfter();
	testDelete();
	//manualErrorTest1();
	//manualErrorTest2();
	//manualErrorTest3();
	//manualErrorTest4();
    printf("All tests passed\n");
    return 0;
}
