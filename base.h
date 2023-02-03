#ifndef BASE_H
#define BASE_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Declaration of the structures needed to run the sorting program
typedef struct Chain {
    char name[6];
	float val;
    float x;
    float y;
	struct Chain* next;
} Chain;

typedef struct Node {
    char name[6];
    float var;
    float x;
    float y;
    int bal;
    struct Node *l, *r;
} Node;

#endif