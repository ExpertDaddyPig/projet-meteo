#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node {
    int name;
    int var;
    struct Node *l, *r;
} Node;

Node* create(int value, int name) {
    Node* t = malloc(sizeof(Node));
    if (t == NULL) {
        printf("Something wrong happened with the allocation\n");
        exit(1);
    }
    t->l = NULL;
    t->r = NULL;
    t->name = name;
    t->var = value;
    return t;
}

int Lexist(Node *t) {
    return t->l == NULL ? 1 : 0;
}

int Rexist(Node *t) {
    return t->r == NULL ? 1 : 0;
}

void printNode(Node *t) {
    printf("%d ", t->var);
}

void parcInf(Node *t) {
    if (t != NULL) {
        parcInf(t->l);
        printNode(t);
        parcInf(t->r);
    }
}

Node *insert(Node *t, int value, int name) {
    if (t == NULL) return create(value, name);
    if (value < t->var) {
        t->l = insert(t->l, value, name);
    } else if (value > t->var) {
        t->r = insert(t->r, value, name);
    } else {
        printf("%d | %d est déjà dans l'arbre.\n", name, value);
        return t;
    }
}

int main(int argc, char *argv[]) {
    FILE *in = NULL, *out = NULL;
    int reverse = 0, max = 0, moy = 0, wind = 0, mode = 0;
    char *type = "--avl", input[50] = "undefined", output[50] = "undefined", inputFile[100], outputFile[100];
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
        } 
        if (reverse == 0 && strcmp(argv[i], "-h") == 0) {
            reverse = 1;
        } 
        if (reverse == 1 && strcmp(argv[i], "-h") == 0) {
            reverse = 0;
        } 
        if (reverse == 0 && strcmp(argv[i], "-m") == 0) {
            reverse = 1;
        } 
        if (reverse == 1 && strcmp(argv[i], "-m") == 0) {
            reverse = 0;
        } 
        if (strcmp(argv[i], "-w") == 0) {
            wind = 1;
        } 
        if (strcmp(argv[i], "-t") == 0 || strcmp(argv[i], "-p") == 0) {
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
    if (strcmp(input, "none") == 0) {
        printf("No input file provided.\n");
        return 1;
    } else if (strcmp(output, "none") == 0) {
        printf("No output file provided.\n");
        return 1;
    } else if (mode == 0) {
        printf("Vous avez utilisé une option température ou pression, veuillez utiliser un mode listés dans la commande d'aide.\n");
    } else {
        snprintf(inputFile, sizeof(inputFile), "%s.txt", input);
        snprintf(outputFile, sizeof(outputFile), "%s.txt", output);
        in = fopen(inputFile, "r+");
        out = fopen(outputFile, "r+");
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
                    printf("Reversus Amongus Bugus Ridiculus\n");
                }
                if (strcmp(type,"--avl") == 0) {
                    printf("Reversus Amongus Volus Longinus\n");
                }
                if (strcmp(type,"--tab") == 0) {
                    printf("Reversus Tabulus Amongus Bingus\n");
                }
            } else {
                if (strcmp(type,"--abr") == 0) {
                    printf("Amongus Bugus Ridiculus\n");
                }
                if (strcmp(type,"--avl") == 0) {
                    printf("Amongus Volus Longinus\n");
                }
                if (strcmp(type,"--tab") == 0) {
                    printf("Tabulus Amongus Bingus\n");
                }
            }
        }
    }
    return 0;
}