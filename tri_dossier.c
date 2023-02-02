#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Chain{
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

void writeNode(Node *t, FILE *f) {
    fprintf(f, "%s;%f\n", t->name, t->var);
}

void writeNode_coords(Node *t, FILE *f) {
    fprintf(f, "%s;%f;%f\n", t->name, t->x, t->y);
}

void parcInfWrite(Node *t, FILE *out) {
    if (t != NULL) {
        parcInfWrite(t->l, out);
        writeNode(t, out);
        parcInfWrite(t->r, out);
    }
}

void parcInfWrite_coords(Node *t, FILE *out) {
    if (t != NULL) {
        parcInfWrite_coords(t->l, out);
        writeNode_coords(t, out);
        parcInfWrite_coords(t->r, out);
    }
}

void writeList(Chain* chain, FILE *f) {
    if (chain != NULL) {
        fprintf(f, "%s;%f\n", chain->name, chain->val);
        writeList(chain->next, f);
    }
}

void writeList_coords(Chain* chain, FILE *f) {
    if (chain != NULL) {
        fprintf(f, "%s;%f;%f\n", chain->name, chain->x, chain->y);
        writeList_coords(chain->next, f);
    }
}

void swap(Chain *a, Chain *b) { 
    int temp = a->val;
    char name[6];
    strcpy(name, a->name);
    a->val = b->val; 
    strcpy(a->name, b->name);
    b->val = temp;
    strcpy(b->name, name);
} 

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

void r_sort(Chain* begin) {
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

void r_sortByName(Chain* begin) {
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

void r_sortByName_coords(Chain* begin) {
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

int Lexist(Node *t) {
    return t->l == NULL ? 1 : 0;
}

int Rexist(Node *t) {
    return t->r == NULL ? 1 : 0;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a < b ? a : b;
}

int searchNameTree(Node *t, char* name) {
    int res1 = 0, res2 = 0;
    if (t == NULL) return -1;
    if (strcmp(t->name, name) != 0) {
        res1 = searchNameTree(t->l, name);
        res2 = searchNameTree(t->r, name);
    } else {
        res1 = 1;
        res2 = 1;
    }
    return max(res1, res2);
}

int searchNameList(Chain* c, char* name) {
    if (c == NULL) return -1;
    if (strcmp(c->name, name) != 0) {
        return searchNameList(c->next, name);
    }
    return 1;
}

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

Chain* insertEnd(Chain* begin, char* name, float value) {
	Chain *new, *p1;
	new = createChain(name, value);
	p1 = begin;
	while(p1->next != NULL){
		p1 = p1->next;
	}
	p1->next = new;
	return begin;
}

Chain* insertEnd_strict(Chain* begin, char* name, float value) {
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

Chain* insertEnd_coords(Chain* begin, char* name, float value, float value2) {
	Chain *new, *p1;
	new = createChain_coords(name, value, value2);
	p1 = begin;
	while(p1->next != NULL){
		p1 = p1->next;
	}
	p1->next = new;
	return begin;
}

Chain* insertEnd_coords_strict(Chain* begin, char* name, float value, float value2) {
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

Node* createTree(char name[], float value) {
    Node* t = malloc(sizeof(Node));
    if (t == NULL) {
        printf("Something wrong happened with the allocation\n");
        exit(1);
    }
    t->l = NULL;
    t->r = NULL;
    t->bal = 0;
    strcpy(t->name, name);
    t->var = value;
    return t;
}

Node* createTree_coords(char name[], float value, float value2) {
    Node* t = malloc(sizeof(Node));
    if (t == NULL) {
        printf("Something wrong happened with the allocation\n");
        exit(1);
    }
    t->l = NULL;
    t->r = NULL;
    t->bal = 0;
    strcpy(t->name, name);
    t->x = value;
    t->y = value2;
    return t;
}

Node *rotg(Node *t) {
    Node* piv;
    int ea, ep;
    piv = t->r;
    t->r = piv->l;
    piv->l = t;
    ea = t->bal;
    ep = piv->bal;
    t->bal = ea - max(ep, 0) - 1;
    piv->bal = min(min(ea - 2, ea + ep - 2), ep - 1);
    t = piv;
    return t;
}

Node *rotd(Node *t) {
    Node* piv;
    int ea, ep;
    piv = t->l;
    t->l = piv->r;
    piv->r = t;
    ea = t->bal;
    ep = piv->bal;
    t->bal = ea - min(ep, 0) + 1;
    piv->bal = max(max(ea + 2, ea + ep + 2), ep + 1);
    t = piv;
    return t;
}

Node *drotg(Node *t) {
    t->r = rotd(t->r);
    return rotg(t);
}

Node *drotd(Node *t) {
    t->l = rotg(t->l);
    return rotd(t);
}

Node *treeBalance(Node *t) {
    if (t->bal >= 2) {
        if (t->r->bal >= 0) {
            return rotg(t);
        } else {
            return drotg(t);
        }
    } else if (t->bal <= -2) {
        if (t->l->bal <= 0) {
            return rotd(t);
        } else {
            return drotd(t);
        }
    }
    return t;
}

Node *insertAVL(Node *t, char* name, float value, int *h) {
    if (t == NULL) {
        *h = 1;
        return createTree(name, value);
    } else if (value < t->var) {
        t->l = insertAVL(t->l, name, value, h);
        *h = -*h;
    } else if (value >= t->var) {
        t->r = insertAVL(t->r, name, value, h);
    } else {
        *h = 0;
        return t;
    }
    if (*h != 0) {
        t->bal = t->bal + *h;
        t = treeBalance(t);
        if (t->bal == 0) {
            *h = 0;
        } else {
            *h = 1;
        }
    }
    return t;
}

Node *insertAVL_strict(Node *t, char* name, float value, int *h) {
    if (t == NULL) {
        *h = 1;
        return createTree(name, value);
    } else if (searchNameTree(t, name) == 1) {
        return t;
    } else if (value < t->var) {
        t->l = insertAVL_strict(t->l, name, value, h);
        *h = -*h;
    } else if (value >= t->var) {
        t->r = insertAVL_strict(t->r, name, value, h);
    } else {
        *h = 0;
        return t;
    }
    if (*h != 0) {
        t->bal = t->bal + *h;
        t = treeBalance(t);
        if (t->bal == 0) {
            *h = 0;
        } else {
            *h = 1;
        }
    }
    return t;
}

Node *r_insertAVL(Node *t, char* name, float value, int *h) {
    if (t == NULL) {
        *h = 1;
        return createTree(name, value);
    } else if (value > t->var) {
        t->l = r_insertAVL(t->l, name, value, h);
        *h = -*h;
    } else if (value <= t->var) {
        t->r = r_insertAVL(t->r, name, value, h);
    } else {
        *h = 0;
        return t;
    }
    if (*h != 0) {
        t->bal = t->bal + *h;
        t = treeBalance(t);
        if (t->bal == 0) {
            *h = 0;
        } else {
            *h = 1;
        }
    }
    return t;
}

Node *r_insertAVL_strict(Node *t, char* name, float value, int *h) {
    if (t == NULL) {
        *h = 1;
        return createTree(name, value);
    } else if (searchNameTree(t, name) == 1) {
        return t;
    } else if (value > t->var) {
        t->l = r_insertAVL_strict(t->l, name, value, h);
        *h = -*h;
    } else if (value <= t->var) {
        t->r = r_insertAVL_strict(t->r, name, value, h);
    } else {
        *h = 0;
        return t;
    }
    if (*h != 0) {
        t->bal = t->bal + *h;
        t = treeBalance(t);
        if (t->bal == 0) {
            *h = 0;
        } else {
            *h = 1;
        }
    }
    return t;
}

Node *insertABR(Node *t, char* name, float value) {
    if (t == NULL) return createTree(name, value);
    if (value < t->var) {
        t->l = insertABR(t->l, name, value);
    } else if (value >= t->var) {
        t->r = insertABR(t->r, name, value);
    }
    return t;
}

Node *insertABR_strict(Node *t, char* name, float value) {
    if (t == NULL) return createTree(name, value);
    if (searchNameTree(t, name) == 1) {
        return t;
    } else if (value < t->var) {
        t->l = insertABR_strict(t->l, name, value);
    } else if (value >= t->var) {
        t->r = insertABR_strict(t->r, name, value);
    }
    return t;
}

Node *r_insertABR(Node *t, char* name, float value) {
    if (t == NULL) return createTree(name, value);
    if (value > t->var) {
        t->l = r_insertABR(t->l, name, value);
    } else if (value <= t->var) {
        t->r = r_insertABR(t->r, name, value);
    }
    return t;
}

Node *r_insertABR_strict(Node *t, char* name, float value) {
    if (t == NULL) return createTree(name, value);
    if (searchNameTree(t, name) == 1) {
        return t;
    } else if (value > t->var) {
        t->l = r_insertABR_strict(t->l, name, value);
    } else if (value <= t->var) {
        t->r = r_insertABR_strict(t->r, name, value);
    }
    return t;
}

Node *insertNameABR_coords(Node *t, char* name, float value, float value2) {
    if (t == NULL) return createTree_coords(name, value, value2);
    if (atoi(name) < atoi(t->name)) {
        t->l = insertNameABR_coords(t->l, name, value, value2);
    } else if (atoi(name) >= atoi(t->name)) {
        t->r = insertNameABR_coords(t->r, name, value, value2);
    }
    return t;
}

Node *insertNameABR_coords_strict(Node *t, char* name, float value, float value2) {
    if (t == NULL) return createTree_coords(name, value, value2);
    if (searchNameTree(t, name) == 1) {
        return t;
    } else if (atoi(name) < atoi(t->name)) {
        t->l = insertNameABR_coords_strict(t->l, name, value, value2);
    } else if (atoi(name) >= atoi(t->name)) {
        t->r = insertNameABR_coords_strict(t->r, name, value, value2);
    }
    return t;
}

Node *r_insertNameABR_coords(Node *t, char* name, float value, float value2) {
    if (t == NULL) return createTree_coords(name, value, value2);
    if (atoi(name) < atoi(t->name)) {
        t->l = r_insertNameABR_coords(t->l, name, value, value2);
    } else if (atoi(name) >= atoi(t->name)) {
        t->r = r_insertNameABR_coords(t->r, name, value, value2);
    }
    return t;
}

Node *r_insertNameABR_coords_strict(Node *t, char* name, float value, float value2) {
    if (t == NULL) return createTree_coords(name, value, value2);
    if (searchNameTree(t, name) == 1) {
        return t;
    } else if (atoi(name) < atoi(t->name)) {
        t->l = r_insertNameABR_coords_strict(t->l, name, value, value2);
    } else if (atoi(name) >= atoi(t->name)) {
        t->r = r_insertNameABR_coords_strict(t->r, name, value, value2);
    }
    return t;
}

Node *insertNameAVL_coords(Node *t, char* name, float value, float value2, int *h) {
    if (t == NULL) {
        *h = 1;
        return createTree_coords(name, value, value2);
    } else if (atoi(name) < atoi(t->name)) {
        t->l = insertNameAVL_coords(t->l, name, value, value2, h);
        *h = -*h;
    } else if (atoi(name) >= atoi(t->name)) {
        t->r = insertNameAVL_coords(t->r, name, value, value2, h);
    } else {
        *h = 0;
        return t;
    }
    if (*h != 0) {
        t->bal = t->bal + *h;
        t = treeBalance(t);
        if (t->bal == 0) {
            *h = 0;
        } else {
            *h = 1;
        }
    }
    return t;
}

Node *insertNameAVL_coords_strict(Node *t, char* name, float value, float value2, int *h) {
    if (t == NULL) {
        *h = 1;
        return createTree_coords(name, value, value2);
    } else if (searchNameTree(t, name) == 1) {
        return t;
    } else if (atoi(name) < atoi(t->name)) {
        t->l = insertNameAVL_coords_strict(t->l, name, value, value2, h);
        *h = -*h;
    } else if (atoi(name) >= atoi(t->name)) {
        t->r = insertNameAVL_coords_strict(t->r, name, value, value2, h);
    } else {
        *h = 0;
        return t;
    }
    if (*h != 0) {
        t->bal = t->bal + *h;
        t = treeBalance(t);
        if (t->bal == 0) {
            *h = 0;
        } else {
            *h = 1;
        }
    }
    return t;
}

Node *r_insertNameAVL_coords(Node *t, char* name, float value, float value2, int *h) {
    if (t == NULL) {
        *h = 1;
        return createTree_coords(name, value, value2);
    } else if (atoi(name) > atoi(t->name)) {
        t->l = r_insertNameAVL_coords(t->l, name, value, value2, h);
        *h = -*h;
    } else if (atoi(name) <= atoi(t->name)) {
        t->r = r_insertNameAVL_coords(t->r, name, value, value2, h);
    } else {
        *h = 0;
        return t;
    }
    if (*h != 0) {
        t->bal = t->bal + *h;
        t = treeBalance(t);
        if (t->bal == 0) {
            *h = 0;
        } else {
            *h = 1;
        }
    }
    return t;
}

Node *r_insertNameAVL_coords_strict(Node *t, char* name, float value, float value2, int *h) {
    if (t == NULL) {
        *h = 1;
        return createTree_coords(name, value, value2);
    } else if (searchNameTree(t, name) == 1) {
        return t;
    } else if (atoi(name) > atoi(t->name)) {
        t->l = r_insertNameAVL_coords_strict(t->l, name, value, value2, h);
        *h = -*h;
    } else if (atoi(name) <= atoi(t->name)) {
        t->r = r_insertNameAVL_coords_strict(t->r, name, value, value2, h);
    } else {
        *h = 0;
        return t;
    }
    if (*h != 0) {
        t->bal = t->bal + *h;
        t = treeBalance(t);
        if (t->bal == 0) {
            *h = 0;
        } else {
            *h = 1;
        }
    }
    return t;
}


int main(int argc, char *argv[]) {
    FILE *in = NULL, *out = NULL, *tmp_out = NULL;
    Node *tree = NULL, *tmp = NULL;
    Chain *list = NULL, *tmp2 = NULL;
    float value, value2, sum2 = 0;
    int reverse = 0, max = 0, moy = 0, wind = 0, moist = 0, height = 0, mode = 0, tempPress = 0, h = 0, i = 0, skip = 0, sum = 0, num;
    char *type = "--avl", input[50] = "undefined", output[50] = "undefined", inputFile[100], outputFile[100], line[1024], stop, letter, name[6], name2[6], *verif;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-f") == 0) {
            strcpy(input, argv[i+1]);
        } 
        if (strcmp(argv[i], "-o") == 0) {
            strcpy(output, argv[i+1]);
        } 
        if (strcmp(argv[i], "--abr") == 0) {
            type = argv[i];
        } 
        if (strcmp(argv[i],"--tab") == 0) {
            type = argv[i];
        } 
        if (strcmp(argv[i], "--avl") == 0) {
            type = argv[i];
        } 
        if (strcmp(argv[i], "-r") == 0) {
            reverse = 1;
        }
        if (strcmp(argv[i], "-m") == 0) {
            max = 1;
            moist = 1;
        } 
        if (strcmp(argv[i], "-h") == 0) {
            height = 1;
        } 
        if (strcmp(argv[i], "-w") == 0) {
            wind = 1;
        }
        if (strcmp(argv[i], "-t") == 0 || strcmp(argv[i], "-p") == 0) {
            tempPress = 1;
            if (strcmp(argv[i+1], "1") == 0) {
                mode = 1;
            }
            if (strcmp(argv[i+1], "2") == 0) {
                mode = 2;
            }
            if (strcmp(argv[i+1], "3") == 0) {
                mode = 3;
            }
        }
    }
    if (reverse == 0 && height == 1) {
        reverse = 1;        
    } else if (reverse == 1 && height == 1) {
        reverse = 0;
    }
    if (reverse == 0 && moist == 1) {
        reverse = 1;        
    } else if (reverse == 1 && moist == 1) {
        reverse = 0;
    }
    if (strcmp(input, "none") == 0) {
        printf("No input file provided.\n");
        return 1;
    } else if (strcmp(output, "none") == 0) {
        printf("No output file provided.\n");
        return 1;
    } else if (mode == 0 && tempPress == 1) {
        printf("Vous avez utilisé une option température ou pression, veuillez utiliser un mode listés dans la commande d'aide.\n");
    } else {
        snprintf(inputFile, sizeof(inputFile), "%s.txt", input);
        snprintf(outputFile, sizeof(outputFile), "%s.csv", output);
        in = fopen(inputFile, "r+");
        out = fopen(outputFile, "w+");
        tmp_out = fopen("tmp_out.csv", "w+");
        if (in == NULL || out == NULL) {
            if (in == NULL) {
                printf("Input file doesn't exist\n");
                return 2;
            }
            if (out == NULL) {
                printf("Output file doesn't exist\n");
                return 3;
            }
        } else {
            if (reverse == 1) {
                if (strcmp(type,"--abr") == 0) {
                    if (max == 1) {
                        do {
                            stop = fgetc(in);
                        } while (stop != '\n');
                        while (feof(in) == 0) {
                            fgets(line, sizeof(line), in);
                            if (feof(in) == 0) {
                                strcpy(name, strtok(line, ";"));
                                verif = strtok(NULL, ";");
                                if (verif) {
                                    value = atoi(verif);
                                } else {
                                    value = 0;
                                }
                                tmp = r_insertABR(tmp, name, value);
                            }
                        }
                        fclose(in);
                        parcInfWrite(tmp, tmp_out);
                        rewind(tmp_out);
                        while (feof(tmp_out) == 0) {
                            fgets(line, sizeof(line), tmp_out);
                             if (feof(tmp_out) == 0) {
                                strcpy(name, strtok(line, ";"));
                                verif = strtok(NULL, ";");
                                if (verif) {
                                    value = atoi(verif);
                                } else {
                                    value = 0;
                                }
                                tree = r_insertABR_strict(tree, name, value);
                            }
                        }
                        fclose(tmp_out);
                        parcInfWrite(tree, out);
                        fclose(out);
                    } else if (wind == 1) {
                        do {
                            stop = fgetc(in);
                        } while (stop != '\n');
                        while (feof(in) == 0) {
                            fgets(line, sizeof(line), in);
                            if (feof(in) == 0) {
                                strcpy(name, strtok(line, ";"));
                                verif = strtok(NULL, ";");
                                if (verif) {
                                    value = atoi(verif);
                                } else {
                                    value = 0;
                                }
                                verif = strtok(NULL, ";");
                                if (verif) {
                                    value2 = atof(verif);
                                } else {
                                    value2 = 0;
                                }
                                tmp = r_insertNameABR_coords(tmp, name, value, value2);
                            }
                        }
                        fclose(in);
                        parcInfWrite_coords(tmp, tmp_out);
                        rewind(tmp_out);
                        while (feof(tmp_out) == 0) {
                            i = 0;
                            do {
                                fgets(line, sizeof(line), tmp_out);
                                i++;
                            } while (i < skip);
                            num = 1;
                            if (feof(tmp_out) == 0) {
                                strcpy(name, strtok(line, ";"));
                                rewind(tmp_out);
                                while (feof(tmp_out) == 0) {
                                    fgets(line, sizeof(line), tmp_out);
                                    if (feof(tmp_out) == 0) {
                                        strcpy(name2, strtok(line, ";"));
                                        if (strcmp(name, name2) == 0) {
                                            num++;
                                            verif = strtok(NULL, ";");
                                            if (verif) {
                                                value = atoi(verif);
                                            } else {
                                                value = 0;
                                            }
                                            verif = strtok(NULL, ";");
                                            if (verif) {
                                                value2 = atof(verif);
                                            } else {
                                                value2 = 0;
                                            }
                                            sum = sum + value;
                                            sum2 = sum2 + value2;
                                        }
                                    }
                                }
                                rewind(tmp_out);
                            }
                            skip++;
                            sum = sum/num;
                            sum2 = sum2/num;
                            tree = r_insertNameABR_coords_strict(tree, name, sum, sum2);
                        }
                        fclose(tmp_out);
                        parcInfWrite_coords(tree, out);
                        fclose(out);
                    } else {
                        while (stop !='\n') {
                            stop = fgetc(in);
                        }
                        do {
                            fscanf(in, "%s", line);
                            strcpy(name, strtok(line, ";"));
                            verif = strtok(NULL, ";");
                                if (verif) {
                                    value = atoi(verif);
                                } else {
                                    value = 0;
                                }
                            tree = r_insertABR(tree, name, value);
                            stop = fgetc(in);
                        } while (stop != EOF);
                        fclose(in);
                        parcInfWrite(tree, out);
                        fclose(out);
                    }
                }
                if (strcmp(type,"--avl") == 0) {
                    if (max == 1) {
                        do {
                            stop = fgetc(in);
                        } while (stop != '\n');
                        while (feof(in) == 0) {
                            fgets(line, sizeof(line), in);
                            if (feof(in) == 0) {
                                strcpy(name, strtok(line, ";"));
                                verif = strtok(NULL, ";");
                                if (verif) {
                                    value = atoi(verif);
                                } else {
                                    value = 0;
                                }
                                tmp = r_insertAVL(tmp, name, value, &h);
                            }
                        }
                        fclose(in);
                        parcInfWrite(tmp, tmp_out);
                        rewind(tmp_out);
                        while (feof(tmp_out) == 0) {
                            fgets(line, sizeof(line), tmp_out);
                             if (feof(tmp_out) == 0) {
                                strcpy(name, strtok(line, ";"));
                                verif = strtok(NULL, ";");
                                if (verif) {
                                    value = atoi(verif);
                                } else {
                                    value = 0;
                                }
                                tree = r_insertAVL_strict(tree, name, value, &h);
                            }
                        }
                        fclose(tmp_out);
                        parcInfWrite(tree, out);
                        fclose(out);
                    } else if (wind == 1) {
                        do {
                            stop = fgetc(in);
                        } while (stop != '\n');
                        while (feof(in) == 0) {
                            fgets(line, sizeof(line), in);
                            if (feof(in) == 0) {
                                strcpy(name, strtok(line, ";"));
                                verif = strtok(NULL, ";");
                                if (verif) {
                                    value = atoi(verif);
                                } else {
                                    value = 0;
                                }
                                verif = strtok(NULL, ";");
                                if (verif) {
                                    value2 = atof(verif);
                                } else {
                                    value2 = 0;
                                }
                                tmp = r_insertNameAVL_coords(tmp, name, value, value2, &h);
                            }
                        }
                        fclose(in);
                        parcInfWrite_coords(tmp, tmp_out);
                        rewind(tmp_out);
                        while (feof(tmp_out) == 0) {
                            i = 0;
                            do {
                                fgets(line, sizeof(line), tmp_out);
                                i++;
                            } while (i < skip);
                            num = 1;
                            if (feof(tmp_out) == 0) {
                                strcpy(name, strtok(line, ";"));
                                rewind(tmp_out);
                                while (feof(tmp_out) == 0) {
                                    fgets(line, sizeof(line), tmp_out);
                                    if (feof(tmp_out) == 0) {
                                        strcpy(name2, strtok(line, ";"));
                                        if (strcmp(name, name2) == 0) {
                                            num++;
                                            verif = strtok(NULL, ";");
                                            if (verif) {
                                                value = atoi(verif);
                                            } else {
                                                value = 0;
                                            }
                                            verif = strtok(NULL, ";");
                                            if (verif) {
                                                value2 = atof(verif);
                                            } else {
                                                value2 = 0;
                                            }
                                            sum = sum + value;
                                            sum2 = sum2 + value2;
                                        }
                                    }
                                }
                                rewind(tmp_out);
                            }
                            skip++;
                            sum = sum/num;
                            sum2 = sum2/num;
                            tree = r_insertNameAVL_coords_strict(tree, name, sum, sum2, &h);
                        }
                        fclose(tmp_out);
                        parcInfWrite_coords(tree, out);
                        fclose(out);
                    } else {
                        do {
                            stop = fgetc(in);
                        } while (stop != '\n');
                        while (feof(in) == 0) {
                            fgets(line, sizeof(line), in);
                            if (feof(in) == 0) {
                                strcpy(name, strtok(line, ";"));
                                verif = strtok(NULL, ";");
                                if (verif) {
                                    value = atoi(verif);
                                } else {
                                    value = 0;
                                }
                                tree = r_insertAVL(tree, name, value, &h);
                            }
                        }
                        fclose(in);
                        parcInfWrite(tree, out);
                        fclose(out);
                    }
                }
                if (strcmp(type,"--tab") == 0) {
                    if (max == 1) {
                        do {
                            stop = fgetc(in);
                        } while (stop != '\n');
                        while (feof(in) == 0) {
                            fgets(line, sizeof(line), in);
                            if (feof(in) == 0) {
                                strcpy(name, strtok(line, ";"));
                                verif = strtok(NULL, ";");
                                if (verif) {
                                    value = atoi(verif);
                                } else {
                                    value = 0;
                                }
                                if (tmp2 == NULL) {
                                    tmp2 = createChain(name, value);
                                } else {
                                    tmp2 = insertEnd(tmp2, name, value);
                                }
                            }
                        }
                        r_sort(tmp2);
                        fclose(in);
                        writeList(tmp2, tmp_out);
                        rewind(tmp_out);
                        while (feof(tmp_out) == 0) {
                            fgets(line, sizeof(line), tmp_out);
                             if (feof(tmp_out) == 0) {
                                strcpy(name, strtok(line, ";"));
                                verif = strtok(NULL, ";");
                                if (verif) {
                                    value = atoi(verif);
                                } else {
                                    value = 0;
                                }
                                if (list == NULL) {
                                    list = createChain(name, value);
                                } else {
                                    list = insertEnd_strict(list, name, value);
                                }
                            }
                        }
                        r_sort(list);
                        fclose(tmp_out);
                        writeList(list, out);
                        fclose(out);
                    } else if (wind == 1) {
                        do {
                            stop = fgetc(in);
                        } while (stop != '\n');
                        while (feof(in) == 0) {
                            fgets(line, sizeof(line), in);
                            if (feof(in) == 0) {
                                strcpy(name, strtok(line, ";"));
                                verif = strtok(NULL, ";");
                                if (verif) {
                                    value = atoi(verif);
                                } else {
                                    value = 0;
                                }
                                verif = strtok(NULL, ";");
                                if (verif) {
                                    value2 = atof(verif);
                                } else {
                                    value2 = 0;
                                }
                                if (tmp2 == NULL) {
                                    tmp2 = createChain_coords(name, value, value2);
                                } else {
                                    tmp2 = insertEnd_coords(tmp2, name, value, value2);
                                    r_sortByName_coords(tmp2);
                                }
                            }
                        }
                        fclose(in);
                        writeList_coords(tmp2, tmp_out);
                        rewind(tmp_out);
                        while (feof(tmp_out) == 0) {
                            i = 0;
                            do {
                                fgets(line, sizeof(line), tmp_out);
                                i++;
                            } while (i < skip);
                            num = 1;
                            if (feof(tmp_out) == 0) {
                                strcpy(name, strtok(line, ";"));
                                rewind(tmp_out);
                                while (feof(tmp_out) == 0) {
                                    fgets(line, sizeof(line), tmp_out);
                                    if (feof(tmp_out) == 0) {
                                        strcpy(name2, strtok(line, ";"));
                                        if (strcmp(name, name2) == 0) {
                                            num++;
                                            verif = strtok(NULL, ";");
                                            if (verif) {
                                                value = atoi(verif);
                                            } else {
                                                value = 0;
                                            }
                                            verif = strtok(NULL, ";");
                                            if (verif) {
                                                value2 = atof(verif);
                                            } else {
                                                value2 = 0;
                                            }
                                            sum = sum + value;
                                            sum2 = sum2 + value2;
                                        }
                                    }
                                }
                                rewind(tmp_out);
                            }
                            skip++;
                            sum = sum/num;
                            sum2 = sum2/num;
                            if (list == NULL) {
                                list = createChain_coords(name, value, value2);
                            } else {
                                list = insertEnd_coords_strict(list, name, value, value2);
                                r_sortByName_coords(list);
                            }
                        }
                        fclose(tmp_out);
                        writeList_coords(list, out);
                        fclose(out);
                    } else {
                        do {
                            stop = fgetc(in);
                        } while (stop != '\n');
                        while (feof(in) == 0) {
                            fgets(line, sizeof(line), in);
                            if (feof(in) == 0) {
                                strcpy(name, strtok(line, ";"));
                                verif = strtok(NULL, ";");
                                    if (verif) {
                                        value = atoi(verif);
                                    } else {
                                        value = 0;
                                    }
                                if (list == NULL) {
                                    list = createChain(name, value);
                                } else {
                                    list = insertEnd(list, name, value);
                                    r_sort(list);
                                }
                            }
                        }
                        fclose(in);
                        writeList(list, out);
                        fclose(out); 
                    }
                }
            } else {
                if (strcmp(type,"--abr") == 0) {
                    if (max == 1) {
                        do {
                            stop = fgetc(in);
                        } while (stop != '\n');
                        while (feof(in) == 0) {
                            fgets(line, sizeof(line), in);
                            if (feof(in) == 0) {
                                strcpy(name, strtok(line, ";"));
                                verif = strtok(NULL, ";");
                                if (verif) {
                                    value = atoi(verif);
                                } else {
                                    value = 0;
                                }
                                tmp = insertABR(tmp, name, value);
                            }
                        }
                        fclose(in);
                        parcInfWrite(tmp, tmp_out);
                        rewind(tmp_out);
                        while (feof(tmp_out) == 0) {
                            i = 0;
                            do {
                                fgets(line, sizeof(line), tmp_out);
                                i++;
                            } while (i < skip);
                            if (feof(tmp_out) == 0) {
                                strcpy(name, strtok(line, ";"));
                                rewind(tmp_out);
                                while (feof(tmp_out) == 0) {
                                    fgets(line, sizeof(line), tmp_out);
                                    if (feof(tmp_out) == 0) {
                                        strcpy(name2, strtok(line, ";"));
                                        if (strcmp(name, name2) == 0) {
                                            verif = strtok(NULL, ";");
                                            if (verif) {
                                                value = atoi(verif);
                                            } else {
                                                value = 0;
                                            }
                                        }
                                    }
                                }
                                rewind(tmp_out);
                            }
                            skip++;
                            tree = insertABR_strict(tree, name, value);
                        }
                        fclose(tmp_out);
                        parcInfWrite(tree, out);
                        fclose(out);
                    } else if (wind == 1) {
                        do {
                            stop = fgetc(in);
                        } while (stop != '\n');
                        while (feof(in) == 0) {
                            fgets(line, sizeof(line), in);
                            if (feof(in) == 0) {
                                strcpy(name, strtok(line, ";"));
                                verif = strtok(NULL, ";");
                                if (verif) {
                                    value = atoi(verif);
                                } else {
                                    value = 0;
                                }
                                verif = strtok(NULL, ";");
                                if (verif) {
                                    value2 = atof(verif);
                                } else {
                                    value2 = 0;
                                }
                                tmp = insertNameABR_coords(tmp, name, value, value2);
                            }
                        }
                        fclose(in);
                        parcInfWrite_coords(tmp, tmp_out);
                        rewind(tmp_out);
                        while (feof(tmp_out) == 0) {
                            i = 0;
                            do {
                                fgets(line, sizeof(line), tmp_out);
                                i++;
                            } while (i < skip);
                            num = 1;
                            if (feof(tmp_out) == 0) {
                                strcpy(name, strtok(line, ";"));
                                rewind(tmp_out);
                                while (feof(tmp_out) == 0) {
                                    fgets(line, sizeof(line), tmp_out);
                                    if (feof(tmp_out) == 0) {
                                        strcpy(name2, strtok(line, ";"));
                                        if (strcmp(name, name2) == 0) {
                                            num++;
                                            verif = strtok(NULL, ";");
                                            if (verif) {
                                                value = atoi(verif);
                                            } else {
                                                value = 0;
                                            }
                                            verif = strtok(NULL, ";");
                                            if (verif) {
                                                value2 = atof(verif);
                                            } else {
                                                value2 = 0;
                                            }
                                            sum = sum + value;
                                            sum2 = sum2 + value2;
                                        }
                                    }
                                }
                                rewind(tmp_out);
                            }
                            skip++;
                            sum = sum/num;
                            sum2 = sum2/num;
                            tree = insertNameABR_coords_strict(tree, name, sum, sum2);
                        }
                        fclose(tmp_out);
                        parcInfWrite_coords(tree, out);
                        fclose(out);
                    } else {
                        do {
                            stop = fgetc(in);
                        } while (stop != '\n');
                        while (feof(in) == 0) {
                            fgets(line, sizeof(line), in);
                            if (feof(in) == 0) {
                                strcpy(name, strtok(line, ";"));
                                verif = strtok(NULL, ";");
                                if (verif) {
                                    value = atoi(verif);
                                } else {
                                    value = 0;
                                }
                                tree = insertABR(tree, name, value);
                            }
                        }
                        fclose(in);
                        parcInfWrite(tree, out);
                        fclose(out);
                    }
                }
                if (strcmp(type,"--avl") == 0) {
                    if (max == 1) {
                        do {
                            stop = fgetc(in);
                        } while (stop != '\n');
                        while (feof(in) == 0) {
                            fgets(line, sizeof(line), in);
                            if (feof(in) == 0) {
                                strcpy(name, strtok(line, ";"));
                                verif = strtok(NULL, ";");
                                if (verif) {
                                    value = atoi(verif);
                                } else {
                                    value = 0;
                                }
                                tmp = insertAVL(tmp, name, value, &h);
                            }
                        }
                        fclose(in);
                        parcInfWrite(tmp, tmp_out);
                        rewind(tmp_out);
                        while (feof(tmp_out) == 0) {
                            fgets(line, sizeof(line), tmp_out);
                             if (feof(tmp_out) == 0) {
                                strcpy(name, strtok(line, ";"));
                                verif = strtok(NULL, ";");
                                if (verif) {
                                    value = atoi(verif);
                                } else {
                                    value = 0;
                                }
                                tree = insertAVL_strict(tree, name, value, &h);
                            }
                        }
                        fclose(tmp_out);
                        parcInfWrite(tree, out);
                        fclose(out);
                    } else if (wind == 1) {
                        do {
                            stop = fgetc(in);
                        } while (stop != '\n');
                        while (feof(in) == 0) {
                            fgets(line, sizeof(line), in);
                            if (feof(in) == 0) {
                                strcpy(name, strtok(line, ";"));
                                verif = strtok(NULL, ";");
                                if (verif) {
                                    value = atoi(verif);
                                } else {
                                    value = 0;
                                }
                                verif = strtok(NULL, ";");
                                if (verif) {
                                    value2 = atof(verif);
                                } else {
                                    value2 = 0;
                                }
                                tmp = insertNameAVL_coords(tmp, name, value, value2, &h);
                            }
                        }
                        fclose(in);
                        parcInfWrite_coords(tmp, tmp_out);
                        rewind(tmp_out);
                        while (feof(tmp_out) == 0) {
                            i = 0;
                            do {
                                fgets(line, sizeof(line), tmp_out);
                                i++;
                            } while (i < skip);
                            num = 1;
                            if (feof(tmp_out) == 0) {
                                strcpy(name, strtok(line, ";"));
                                rewind(tmp_out);
                                while (feof(tmp_out) == 0) {
                                    fgets(line, sizeof(line), tmp_out);
                                    if (feof(tmp_out) == 0) {
                                        strcpy(name2, strtok(line, ";"));
                                        if (strcmp(name, name2) == 0) {
                                            num++;
                                            verif = strtok(NULL, ";");
                                            if (verif) {
                                                value = atoi(verif);
                                            } else {
                                                value = 0;
                                            }
                                            verif = strtok(NULL, ";");
                                            if (verif) {
                                                value2 = atof(verif);
                                            } else {
                                                value2 = 0;
                                            }
                                            sum = sum + value;
                                            sum2 = sum2 + value2;
                                        }
                                    }
                                }
                                rewind(tmp_out);
                            }
                            skip++;
                            sum = sum/num;
                            sum2 = sum2/num;
                            tree = insertNameAVL_coords_strict(tree, name, sum, sum2, &h);
                        }
                        fclose(tmp_out);
                        parcInfWrite_coords(tree, out);
                        fclose(out);
                    } else {
                        do {
                            stop = fgetc(in);
                        } while (stop != '\n');
                        while (feof(in) == 0) {
                            fgets(line, sizeof(line), in);
                            if (feof(in) == 0) {
                                strcpy(name, strtok(line, ";"));
                                verif = strtok(NULL, ";");
                                if (verif) {
                                    value = atoi(verif);
                                } else {
                                    value = 0;
                                }
                                tree = insertAVL(tree, name, value, &h);
                            }
                        }
                        fclose(in);
                        parcInfWrite(tree, out);
                        fclose(out);
                    }
                }
                if (strcmp(type,"--tab") == 0) {
                    if (max == 1) {
                        do {
                            stop = fgetc(in);
                        } while (stop != '\n');
                        while (feof(in) == 0) {
                            fgets(line, sizeof(line), in);
                            if (feof(in) == 0) {
                                strcpy(name, strtok(line, ";"));
                                verif = strtok(NULL, ";");
                                if (verif) {
                                    value = atoi(verif);
                                } else {
                                    value = 0;
                                }
                                if (tmp2 == NULL) {
                                    tmp2 = createChain(name, value);
                                } else {
                                    tmp2 = insertEnd(tmp2, name, value);
                                    sort(tmp2);
                                }
                            }
                        }
                        fclose(in);
                        writeList(tmp2, tmp_out);
                        rewind(tmp_out);
                        while (feof(tmp_out) == 0) {
                            i = 0;
                            do {
                                fgets(line, sizeof(line), tmp_out);
                                i++;
                            } while (i < skip);
                            if (feof(tmp_out) == 0) {
                                strcpy(name, strtok(line, ";"));
                                rewind(tmp_out);
                                while (feof(tmp_out) == 0) {
                                    fgets(line, sizeof(line), tmp_out);
                                    if (feof(tmp_out) == 0) {
                                        strcpy(name2, strtok(line, ";"));
                                        if (strcmp(name, name2) == 0) {
                                            verif = strtok(NULL, ";");
                                            if (verif) {
                                                value = atoi(verif);
                                            } else {
                                                value = 0;
                                            }
                                        }
                                    }
                                }
                                rewind(tmp_out);
                            }
                            skip++;
                            if (list == NULL) {
                                list = createChain(name, value);
                            } else {
                                list = insertEnd_strict(list, name, value);
                                sort(list);
                            }
                        }
                        fclose(tmp_out);
                        writeList(list, out);
                        fclose(out);
                    } else if (wind == 1) {
                        do {
                            stop = fgetc(in);
                        } while (stop != '\n');
                        while (feof(in) == 0) {
                            fgets(line, sizeof(line), in);
                            if (feof(in) == 0) {
                                strcpy(name, strtok(line, ";"));
                                verif = strtok(NULL, ";");
                                if (verif) {
                                    value = atoi(verif);
                                } else {
                                    value = 0;
                                }
                                verif = strtok(NULL, ";");
                                if (verif) {
                                    value2 = atof(verif);
                                } else {
                                    value2 = 0;
                                }
                                if (tmp2 == NULL) {
                                    tmp2 = createChain_coords(name, value, value2);
                                } else {
                                    tmp2 = insertEnd_coords(tmp2, name, value, value2);
                                    sortByName_coords(tmp2);
                                }
                            }
                        }
                        fclose(in);
                        writeList_coords(tmp2, tmp_out);
                        rewind(tmp_out);
                        while (feof(tmp_out) == 0) {
                            i = 0;
                            do {
                                fgets(line, sizeof(line), tmp_out);
                                i++;
                            } while (i < skip);
                            num = 1;
                            if (feof(tmp_out) == 0) {
                                strcpy(name, strtok(line, ";"));
                                rewind(tmp_out);
                                while (feof(tmp_out) == 0) {
                                    fgets(line, sizeof(line), tmp_out);
                                    if (feof(tmp_out) == 0) {
                                        strcpy(name2, strtok(line, ";"));
                                        if (strcmp(name, name2) == 0) {
                                            num++;
                                            verif = strtok(NULL, ";");
                                            if (verif) {
                                                value = atoi(verif);
                                            } else {
                                                value = 0;
                                            }
                                            verif = strtok(NULL, ";");
                                            if (verif) {
                                                value2 = atof(verif);
                                            } else {
                                                value2 = 0;
                                            }
                                            sum = sum + value;
                                            sum2 = sum2 + value2;
                                        }
                                    }
                                }
                                rewind(tmp_out);
                            }
                            skip++;
                            sum = sum/num;
                            sum2 = sum2/num;
                            if (list == NULL) {
                                list = createChain_coords(name, value, value2);
                            } else {
                                list = insertEnd_coords_strict(list, name, value, value2);
                                sortByName_coords(list);
                            }
                        }
                        fclose(tmp_out);
                        writeList_coords(list, out);
                        fclose(out);
                    } else {
                        do {
                            stop = fgetc(in);
                        } while (stop != '\n');
                        while (feof(in) == 0) {
                            fgets(line, sizeof(line), in);
                            if (feof(in) == 0) {
                                strcpy(name, strtok(line, ";"));
                                verif = strtok(NULL, ";");
                                if (verif) {
                                    value = atoi(verif);
                                } else {
                                    value = 0;
                                }
                                if (list == NULL) {
                                    list = createChain(name, value);
                                } else {
                                    list = insertEnd(list, name, value);
                                    sort(list);
                                }
                            }
                        }
                        fclose(in);
                        writeList(list, out);
                        fclose(out);
                    }
                }
            }
        }
    }
    remove("tmp_out.csv");
    return 0;
}