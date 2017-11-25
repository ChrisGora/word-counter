#include "tst.h"
#include "listC.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

struct node {
	int x;
	char c;
	struct node *left;
	struct node *middle;
	struct node *right;
	struct node *prev;
	bool sentinel;
	bool checked;
};

typedef struct node node;

struct tst {
	node *senStart;
	node *first;
	list *allNodes;
};

//------------------------------------------------------------------------------

tst *newTst() {
	tst *t = malloc(sizeof(tst));
	node *senStart = malloc(sizeof(node));
	node *senLeft = malloc(sizeof(node));
	node *senMiddle = malloc(sizeof(node));
	node *senRight = malloc(sizeof(node));
	*senStart = (node) {-1, '0', senLeft, senMiddle, senRight, NULL, true, false};
	*senLeft = (node) {-1, '0', NULL, NULL, NULL, senStart, true, false};
	*senMiddle = (node) {-1, '0', NULL, NULL, NULL, senStart, true, false};
	*senRight = (node) {-1, '0', NULL, NULL, NULL, senStart, true, false};
	list *l = newList();
	t->allNodes = l;
	t->senStart = senStart;
	t->first = NULL;
	insertBefore(l, senStart);
	insertBefore(l, senLeft);
	insertBefore(l, senMiddle);
	insertBefore(l, senRight);
	return t;
}

//Turn a sentinel into a normal node and add missing sentinels
static void createNode(node *n, int x, char c) {
	n->sentinel = false;
	node *senLeft = malloc(sizeof(node));
	node *senMiddle = malloc(sizeof(node));
	node *senRight = malloc(sizeof(node));
	*senLeft = (node) {-1, '0', NULL, NULL, NULL, n, true, false};
	*senMiddle = (node) {-1, '0', NULL, NULL, NULL, n, true, false};
	*senRight = (node) {-1, '0', NULL, NULL, NULL, n, true, false};
	n->left = senLeft;
	n->middle = senMiddle;
	n->right = senRight;
	n->x = x;
	n->c = c;
}

void insertString(tst *t, int x, char *c) {
	
}

static node *findNode(tst *t, char *c) {
	return NULL;
}

int search(tst *t, char *c) {
	return 0;
}

void removeString(tst *t, char *c) {
	
}

//------------------------------------------------------------------------------

static void setUnchecked(tst *t) {

}

static bool compare(tst *t, char *s) {
	return 0;
}

static void testNew() {
	tst *t = newTst();
	list *l = t->allNodes;
	node *s = t->senStart;
	start(l);
	assert(atStart(l));
	assert(s == getAfter(l));
	forward(l);
	assert((s->left) == getAfter(l));
	forward(l);
	assert(s->middle == getAfter(l));
	forward(l);
	assert(s->right == getAfter(l));
	forward(l);
	printf("testNew passed\n");
}

static void testInsert() {
	tst *t = newTst();
	insertString(t, 1, "abc");
	insertString(t, 2, "abd");
	compare(t, "abc*,abd*");
	printf("testInsert passed\n");
}

int tstMain() {
	testNew();
	testInsert();
	printf("ALL TESTS PASSED\n");
	return 0;
}
