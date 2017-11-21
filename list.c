#include "list.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

struct list {
    item a;
    item b;
};

list *newList() {
    return 0;
}

void start(list *l) {

}

void end(list *l) {

}

bool atStart(list *l) {
    return false;
}

bool atEnd(list *l) {
    return false;
}

void forward(list *l) {

}

void backward(list *l) {

}

void insertBefore(list *l, item x) {

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

//-----------------------------------------------------------------------------

void testNew() {

}

void testStart() {

}

void testEnd() {

}

void listMain() {
    testNew;
    testStart;
    testEnd;
    return 0;
}
