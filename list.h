#ifndef LIST_H
#define LIST_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "base.h"

//Declaration of the functions needed to do the chained list sort
void writeList(Chain* chain, FILE *f);
void writeList_coords(Chain* chain, FILE *f);
void swap(Chain *a, Chain *b);
void swap_coords(Chain *a, Chain *b);
void sort(Chain* begin);
void sortByName(Chain* begin);
void sortByName_coords(Chain* begin);
void r_sort(Chain* begin);
void r_sortByName(Chain* begin);
void r_sortByName_coords(Chain* begin);
int searchNameList(Chain* c, char* name);
Chain* createChain(char* name, float value);
Chain* createChain_coords(char* name, float value, float value2);
Chain* insertEnd(Chain* begin, char* name, float value);
Chain* insertEnd_strict(Chain* begin, char* name, float value);
Chain* insertEnd_coords(Chain* begin, char* name, float value, float value2);
Chain* insertEnd_coords_strict(Chain* begin, char* name, float value, float value2);

#endif