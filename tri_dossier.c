#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node {
    char name[6];
    int var;
    struct Node *l, *r;
} Node;

Node* create(char name[], int value) {
    Node* t = malloc(sizeof(Node));
    if (t == NULL) {
        printf("Something wrong happened with the allocation\n");
        exit(1);
    }
    t->l = NULL;
    t->r = NULL;
    strcpy(t->name, name);
    t->var = value;
    return t;
}

int Lexist(Node *t) {
    return t->l == NULL ? 1 : 0;
}

int Rexist(Node *t) {
    return t->r == NULL ? 1 : 0;
}

void writeNode(Node *t, FILE *f) {
    fprintf(f, "%s;%d\n", t->name, t->var);
}

void parcInfWrite(Node *t, FILE *out) {
    if (t != NULL) {
        parcInfWrite(t->l, out);
        writeNode(t, out);
        parcInfWrite(t->r, out);
    }
}

Node *insert(Node *t, char* name, int value) {
    if (t == NULL) return create(name, value);
    if (value < t->var) {
        t->l = insert(t->l, name, value);
    } else if (value >= t->var) {
        t->r = insert(t->r, name, value);
    } else {
        printf("%s | %d est déjà dans l'arbre.\n", name, value);
    }
    return t;
}

Node *r_insert(Node *t, char* name, int value) {
    if (t == NULL) return create(name, value);
    if (value > t->var) {
        t->l = r_insert(t->l, name, value);
    } else if (value <= t->var) {
        t->r = r_insert(t->r, name, value);
    } else {
        printf("%s | %d est déjà dans l'arbre.\n", name, value);
    }
    return t;
}

int main(int argc, char *argv[]) {
    FILE *in = NULL, *out = NULL;
    Node *tree = NULL;
    int reverse = 0, max = 0, moy = 0, wind = 0, mode = 0, tempPress = 0, value, j = 0;
    char *type = "--avl", input[50] = "undefined", output[50] = "undefined", inputFile[100], outputFile[100], line[1024], stop, letter, name[6];
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
        out = fopen(outputFile, "w+");
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
                    while (stop !='\n') {
                        stop = fgetc(in);
                    }
                    do {
                        fscanf(in, "%s", line);
                        strcpy(name, strtok(line, ";"));
                        value = atoi(strtok(NULL, ";"));
                        tree = r_insert(tree, name, value);
                        stop = fgetc(in);
                    } while (stop != EOF);
                    fclose(in);
                    parcInfWrite(tree, out);
                    fclose(out);
                }
                if (strcmp(type,"--avl") == 0) {
                    printf("Reversus Amongus Volus Longinus\n");
                }
                if (strcmp(type,"--tab") == 0) {
                    printf("Reversus Tabulus Amongus Bingus\n");
                }
            } else {
                if (strcmp(type,"--abr") == 0) {
                    while (stop !='\n') {
                        stop = fgetc(in);
                    }
                    do {
                        fscanf(in, "%s", line);
                        strcpy(name, strtok(line, ";"));
                        value = atoi(strtok(NULL, ";"));
                        tree = insert(tree, name, value);
                        stop = fgetc(in);
                    } while (stop != EOF);
                    fclose(in);
                    parcInfWrite(tree, out);
                    fclose(out);
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