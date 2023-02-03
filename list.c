#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "base.h"

//Write the entire list in the file
void writeList(Chain* chain, FILE *f) {
    if (chain != NULL) {
        fprintf(f, "%s;%f\n", chain->name, chain->val);
        writeList(chain->next, f);
    }
}

//This function does the same thing as the one before, but it writes 3 values instead of 2
void writeList_coords(Chain* chain, FILE *f) {
    if (chain != NULL) {
        fprintf(f, "%s;%f;%f\n", chain->name, chain->x, chain->y);
        writeList_coords(chain->next, f);
    }
}

//This function switch the value of two chains from the list
void swap(Chain *a, Chain *b) { 
    int temp = a->val;
    char name[6];
    strcpy(name, a->name);
    a->val = b->val; 
    strcpy(a->name, b->name);
    b->val = temp;
    strcpy(b->name, name);
} 

//This one does the same as the one before, but instaed of changing the value, it changes the x and y value of the structure
void swap_coords(Chain *a, Chain *b) { 
    int x = a->x;
    int y = a->y;
    char name[6];
    strcpy(name, a->name);
    a->x = b->x; 
    a->y = b->y;
    strcpy(a->name, b->name);
    b->x = x;
    b->y = y;
    strcpy(b->name, name);
} 

//This is a bubble sort for a chained list. It sorts the list by the value of every chain
void sort(Chain* begin) {
	int swapped, i; 
    Chain *p; 
    Chain *tmp = NULL; 
    if (begin == NULL) return; 
    do { 
        swapped = 0; 
        p = begin; 
        while (p->next != tmp) { 
            if (p->val > p->next->val) { 
                swap(p, p->next); 
                swapped = 1; 
            } 
            p = p->next; 
        } 
        tmp = p; 
    } 
    while (swapped);
}

//This is a name version of the bubble sort, it sorts the list by the name of the stations
void sortByName(Chain* begin) {
	int swapped, i; 
    Chain *p; 
    Chain *tmp = NULL; 
    if (begin == NULL) return; 
    do { 
        swapped = 0; 
        p = begin; 
        while (p->next != tmp) { 
            if (atoi(p->name) > atoi(p->next->name)) { 
                swap(p, p->next); 
                swapped = 1; 
            } 
            p = p->next; 
        } 
        tmp = p; 
    } 
    while (swapped);
}

//This is another version of bubble sort with the coords values (x and y)
void sortByName_coords(Chain* begin) {
	int swapped, i; 
    Chain *p; 
    Chain *tmp = NULL; 
    if (begin == NULL) return; 
    do { 
        swapped = 0; 
        p = begin; 
        while (p->next != tmp) { 
            if (atoi(p->name) > atoi(p->next->name)) { 
                swap_coords(p, p->next); 
                swapped = 1; 
            } 
            p = p->next; 
        } 
        tmp = p; 
    } 
    while (swapped);
}

/*|*///These 3 functions does the inverted sort of a list, with the same specification of the original ones
/*|*/void r_sort(Chain* begin) {
	int swapped, i; 
    Chain *p; 
    Chain *tmp = NULL; 
    if (begin == NULL) return; 
    do { 
        swapped = 0; 
        p = begin; 
        while (p->next != tmp) { 
            if (p->val < p->next->val) { 
                swap(p, p->next); 
                swapped = 1; 
            } 
            p = p->next; 
        } 
        tmp = p; 
    } 
    while (swapped);
}
/*|*/
/*|*/void r_sortByName(Chain* begin) {
	int swapped, i; 
    Chain *p; 
    Chain *tmp = NULL; 
    if (begin == NULL) return; 
    do { 
        swapped = 0; 
        p = begin; 
        while (p->next != tmp) { 
            if (atoi(p->name) < atoi(p->next->name)) { 
                swap(p, p->next); 
                swapped = 1; 
            } 
            p = p->next; 
        } 
        tmp = p; 
    } 
    while (swapped);
}
/*|*/
/*|*/void r_sortByName_coords(Chain* begin) {
	int swapped, i; 
    Chain *p; 
    Chain *tmp = NULL; 
    if (begin == NULL) return; 
    do { 
        swapped = 0; 
        p = begin; 
        while (p->next != tmp) { 
            if (atoi(p->name) < atoi(p->next->name)) { 
                swap_coords(p, p->next); 
                swapped = 1; 
            } 
            p = p->next; 
        } 
        tmp = p; 
    } 
    while (swapped);
}

//This function return 1 if a station is already in the list and return -1 if not
int searchNameList(Chain* c, char* name) {
    if (c == NULL) return -1;
    if (strcmp(c->name, name) != 0) {
        return searchNameList(c->next, name);
    }
    return 1;
}

/*-----------------------------------------------------------
Those 2 functions create a chain for the list, with one and two values respectively*/
Chain* createChain(char* name, float value) {
	Chain* c = malloc(sizeof(Chain));
	if (c == NULL) {
		exit(1);
	}
	c->next=NULL;
    strcpy(c->name, name);
	c->val = value;
	return c;
}

Chain* createChain_coords(char* name, float value, float value2) {
	Chain* c = malloc(sizeof(Chain));
	if (c == NULL) {
		exit(1);
	}
	c->next=NULL;
    strcpy(c->name, name);
	c->x = value;
    c->y = value2;
	return c;
}
/*(The two variables are x and y)
-------------------------------------------------------------*/

/*|  Those functions insert the values at the end of the list, the ones with "strict" in their name add the values
/*|   only if the station is not already in the list.*/
/*|*/Chain* insertEnd(Chain* begin, char* name, float value) {
	Chain *new, *p1;
	new = createChain(name, value);
	p1 = begin;
	while(p1->next != NULL){
		p1 = p1->next;
	}
	p1->next = new;
	return begin;
}
/*|*/
/*|*/Chain* insertEnd_strict(Chain* begin, char* name, float value) {
	Chain *new, *p1;
	new = createChain(name, value);
	p1 = begin;
    if (searchNameList(begin, name) != 1) {
        while(p1->next != NULL){
		    p1 = p1->next;
	    }
	    p1->next = new;
    }
	return begin;
}
/*|*/
/*|*/Chain* insertEnd_coords(Chain* begin, char* name, float value, float value2) {
	Chain *new, *p1;
	new = createChain_coords(name, value, value2);
	p1 = begin;
	while(p1->next != NULL){
		p1 = p1->next;
	}
	p1->next = new;
	return begin;
}
/*|*/
/*|*/Chain* insertEnd_coords_strict(Chain* begin, char* name, float value, float value2) {
	Chain *new, *p1;
	new = createChain_coords(name, value, value2);
	p1 = begin;
    if (searchNameList(p1, name) != 1) {
        while(p1->next != NULL){
		    p1 = p1->next;
	    }
	    p1->next = new;
    }
	return begin;
}
