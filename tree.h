#ifndef TREE_H
#define TREE_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "base.h"

//Declaration of the functions needed to do the tree sort
void writeNode(Node *t, FILE *f);
void writeNode_coords(Node *t, FILE *f);
void parcInfWrite(Node *t, FILE *out);
void parcInfWrite_coords(Node *t, FILE *out);
int Lexist(Node *t);
int Rexist(Node *t);
int max(int a, int b);
int min(int a, int b);
int searchNameTree(Node *t, char* name);
Node* createTree(char name[], float value);
Node* createTree_coords(char name[], float value, float value2);
Node *rotg(Node *t);
Node *rotd(Node *t);
Node *drotg(Node *t);
Node *drotd(Node *t);
Node *treeBalance(Node *t);
Node *insertAVL(Node *t, char* name, float value, int *h);
Node *insertAVL_strict(Node *t, char* name, float value, int *h);
Node *r_insertAVL(Node *t, char* name, float value, int *h);
Node *r_insertAVL_strict(Node *t, char* name, float value, int *h);
Node *insertABR(Node *t, char* name, float value);
Node *insertABR_strict(Node *t, char* name, float value);
Node *r_insertABR(Node *t, char* name, float value);
Node *r_insertABR_strict(Node *t, char* name, float value);
Node *insertNameABR_coords(Node *t, char* name, float value, float value2);
Node *insertNameABR_coords_strict(Node *t, char* name, float value, float value2);
Node *r_insertNameABR_coords(Node *t, char* name, float value, float value2);
Node *r_insertNameABR_coords_strict(Node *t, char* name, float value, float value2);
Node *insertNameAVL_coords(Node *t, char* name, float value, float value2, int *h);
Node *insertNameAVL_coords_strict(Node *t, char* name, float value, float value2, int *h);
Node *r_insertNameAVL_coords(Node *t, char* name, float value, float value2, int *h);
Node *r_insertNameAVL_coords_strict(Node *t, char* name, float value, float value2, int *h);

#endif