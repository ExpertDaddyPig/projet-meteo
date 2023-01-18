#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define PART 10000

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

void printNode(Node *t, char *s, FILE *f) {
    fprintf(f, "%d", t->name);
    fprintf(f, "%c", ';');
    fprintf(f, "%d", t->var);
    fprintf(f, "%c", '\n');
}

char *writeString(Node *t, char *s) {
    return s;
}

void parcInfWrite(Node *t, FILE *out) {
    char buf[50], skip = fgetc(out), stop;
    int name, value;
    if (t != NULL) {
        parcInfWrite(t->l, out);
        if (skip != EOF) {
            while (skip != '\n') {
                skip = fgetc(out);
            }
        }
        if (stop != EOF) {
            do {
                fscanf(out, "%d", &name);
                stop = fgetc(out);
                fscanf(out, "%d", &value);
                stop = fgetc(out);
            } while (value < t->var && stop != EOF);
            printNode(t, buf, out);
        } else {
            printNode(t, buf, out);
        }
        parcInfWrite(t->r, out);
    }
}

Node *insert(Node *t, int value, int name) {
    if (t == NULL) return create(value, name);
    if (value < t->var) {
        t->l = insert(t->l, value, name);
    } else if (value >= t->var) {
        t->r = insert(t->r, value, name);
    } else {
        printf("%d | %d est déjà dans l'arbre.\n", name, value);
    }
    return t;
}

int main(int argc, char *argv[]) {
    FILE *in = NULL, *out = NULL;
    Node *tree = NULL;
    int reverse = 0, max = 0, moy = 0, wind = 0, mode = 0, tempPress = 0, name, value, skip = 0, line = 0, start = 1;
    char *type = "--avl", input[50] = "undefined", output[50] = "undefined", inputFile[100], outputFile[100], stop;
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
                    while (stop != '\n') {
                        stop = fgetc(in);
                    }
                    for (int i = 0; i < 2; i++) {
                        printf("PASSAGE %d\n", i+1);
                        fscanf(in, "%d", &name);
                        fgetc(in);
                        fscanf(in, "%d", &value);
                        tree = create(value, name);
                        do {
                            fscanf(in, "%d", &name);
                            fgetc(in);
                            fscanf(in, "%d", &value);
                            tree = insert(tree, value, name);
                            stop = fgetc(in);
                            line++;
                        } while (line < PART);
                        parcInfWrite(tree, out);
                        line = 0;
                    }
                    printf("\n");
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
