#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "base.h"

/*|  These are the "writing in the output file function". It uses the infix traversal to print the tree in the file*/
/*|*/void writeNode(Node *t, FILE *f) {
    fprintf(f, "%s;%f\n", t->name, t->var);
}
/*|*/
/*|*/void writeNode_coords(Node *t, FILE *f) {
    fprintf(f, "%s;%f;%f\n", t->name, t->x, t->y);
}
/*|*/
/*|*/void parcInfWrite(Node *t, FILE *out) {
    if (t != NULL) {
        parcInfWrite(t->l, out);
        writeNode(t, out);
        parcInfWrite(t->r, out);
    }
}
/*|*/
/*|*/void parcInfWrite_coords(Node *t, FILE *out) {
    if (t != NULL) {
        parcInfWrite_coords(t->l, out);
        writeNode_coords(t, out);
        parcInfWrite_coords(t->r, out);
    }
}

/*|  These two functions verifies that the left and right nodes are not NULL, they return 1 if it's the case, 0 else*/
/*|*/int Lexist(Node *t) {
    return t->l == NULL ? 1 : 0;
}
/*|*/
/*|*/int Rexist(Node *t) {
    return t->r == NULL ? 1 : 0;
}

/*|  Returns the greatest/smallest integer between two integers*/
/*|*/int max(int a, int b) {
    return a > b ? a : b;
}
/*|*/
/*|*/int min(int a, int b) {
    return a < b ? a : b;
}

//Search if a station is in the tree, return 1 if it is, -1 else
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

/*|  These functions create a node with one or two values*/
/*|*/Node* createTree(char name[], float value) {
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
/*|*/
/*|*/Node* createTree_coords(char name[], float value, float value2) {
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

/*|  These are the rotation function, they rotation a node by a pivot node to balance an avl tree*/
/*|*/Node *rotg(Node *t) {
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
/*|*/
/*|*/Node *rotd(Node *t) {
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
/*|*/
/*|*/Node *drotg(Node *t) {
    t->r = rotd(t->r);
    return rotg(t);
}
/*|*/
/*|*/Node *drotd(Node *t) {
    t->l = rotg(t->l);
    return rotd(t);
}

//This is the function that determines from which direction the program rotates the nodes (left or right)
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

/*|----------------------------------------------------------------------
/*|  These functions insert one value in an binary search tree or an avl tree.
/*|*/Node *insertAVL(Node *t, char* name, float value, int *h) {
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
/*|*/
/*|*/Node *insertAVL_strict(Node *t, char* name, float value, int *h) {
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
/*|*/
/*|*/Node *insertABR(Node *t, char* name, float value) {
    if (t == NULL) return createTree(name, value);
    if (value < t->var) {
        t->l = insertABR(t->l, name, value);
    } else if (value >= t->var) {
        t->r = insertABR(t->r, name, value);
    }
    return t;
}
/*|*/
/*|*/Node *insertABR_strict(Node *t, char* name, float value) {
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
/*|  The "strict" in the name of the function means that every station can only have one occurence in the tree */
/*------------------------------------------------------------------------*/

/*|----------------------------------------------------------------------
/*|  These functions insert two value in an binary search tree or an avl tree.
/*|*/Node *insertNameABR_coords(Node *t, char* name, float value, float value2) {
    if (t == NULL) return createTree_coords(name, value, value2);
    if (atoi(name) < atoi(t->name)) {
        t->l = insertNameABR_coords(t->l, name, value, value2);
    } else if (atoi(name) >= atoi(t->name)) {
        t->r = insertNameABR_coords(t->r, name, value, value2);
    }
    return t;
}
/*|*/
/*|*/Node *insertNameAVL_coords(Node *t, char* name, float value, float value2, int *h) {
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
/*|*/
/*|*/Node *insertNameAVL_coords_strict(Node *t, char* name, float value, float value2, int *h) {
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
/*|*/
/*|*/Node *insertNameABR_coords_strict(Node *t, char* name, float value, float value2) {
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
/*|  The "strict" in the name of the function means that every station can only have one occurence in the tree */
/*------------------------------------------------------------------------*/

/*|----------------------------------------------------------------------
/*| These functions do the same as the ones before, but in reverse
/*|*/Node *r_insertAVL(Node *t, char* name, float value, int *h) {
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
/*|*/
/*|*/Node *r_insertAVL_strict(Node *t, char* name, float value, int *h) {
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
/*|*/
/*|*/Node *r_insertABR(Node *t, char* name, float value) {
    if (t == NULL) return createTree(name, value);
    if (value > t->var) {
        t->l = r_insertABR(t->l, name, value);
    } else if (value <= t->var) {
        t->r = r_insertABR(t->r, name, value);
    }
    return t;
}
/*|*/
/*|*/Node *r_insertABR_strict(Node *t, char* name, float value) {
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
/*|*/
/*|*/Node *r_insertNameABR_coords(Node *t, char* name, float value, float value2) {
    if (t == NULL) return createTree_coords(name, value, value2);
    if (atoi(name) < atoi(t->name)) {
        t->l = r_insertNameABR_coords(t->l, name, value, value2);
    } else if (atoi(name) >= atoi(t->name)) {
        t->r = r_insertNameABR_coords(t->r, name, value, value2);
    }
    return t;
}
/*|*/
/*|*/Node *r_insertNameABR_coords_strict(Node *t, char* name, float value, float value2) {
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
/*|*/
/*|*/Node *r_insertNameAVL_coords(Node *t, char* name, float value, float value2, int *h) {
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
/*|*/
/*|*/Node *r_insertNameAVL_coords_strict(Node *t, char* name, float value, float value2, int *h) {
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
/*------------------------------------------------------------------------*/
