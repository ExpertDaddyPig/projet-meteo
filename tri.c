#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tree.h"
#include "list.h"

int main(int argc, char *argv[]) {
    //Declaration of every needed variable
    FILE *in = NULL, *out = NULL, *tmp_out = NULL;
    Node *tree = NULL, *tmp = NULL;
    Chain *list = NULL, *tmp2 = NULL;
    float value, value2, sum2 = 0;
    int reverse = 0, min = 0, max = 0, moy = 0, wind = 0, moist = 0, height = 0, mode = 0, tempPress = 0, h = 0, i = 0, skip = 0, sum = 0, num;
    char *type = "--avl", input[50] = "undefined", output[50] = "undefined", inputFile[100], outputFile[100], line[1024], stop, letter, name[6], name2[6], *verif, *option;
    
    //Activates the option aksed by the user
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
            option = "moisture";
        } 
        if (strcmp(argv[i], "-h") == 0) {
            height = 1;
            option = "height";
        } 
        if (strcmp(argv[i], "-w") == 0) {
            wind = 1;
            option = "wind";
        }
        if (strcmp(argv[i], "-t") == 0 || strcmp(argv[i], "-p") == 0) {
            tempPress = 1;
            if (strcmp(argv[i], "-t") == 0) option = "temp";
            if (strcmp(argv[i], "-t") == 0) option = "press";
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
    
    //Checks if an input and an output file as been given, and also checks if the temperature and pression modes have been entered, exits the program if one check is not valid
    if (strcmp(input, "none") == 0) {
        printf("No input file provided.\n");
        return 1;
    } else if (strcmp(output, "none") == 0) {
        printf("No output file provided.\n");
        return 1;
    } else if (mode == 0 && tempPress == 1) {
        printf("Vous avez utilisé une option température ou pression, veuillez utiliser un mode listés dans la commande d'aide.\n");
    } else {
        //Create the input and output files names and open them with a temporary output file in case it is needed
        snprintf(inputFile, sizeof(inputFile), "%s.txt", input);
        snprintf(outputFile, sizeof(outputFile), "%s-%s.csv", output, option);
        in = fopen(inputFile, "r+");
        out = fopen(outputFile, "w+");
        tmp_out = fopen("tmp_out.csv", "w+");

        //Checks if the oppening of the files is successful, exits if not
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
            //Checks if the reverse option has been selected. If yes the program will do the reversed sort, if no, it will sort normally.
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
                //Checks which sort option has been selected and use the right function to sort the file and write it in the output file
                //Default option is the avl sort if no sort option has been selected.
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
    //Removing the temporay output file since it's not useful anymore, and return the 0 code to inform the shell script that the sort is successful
    remove("tmp_out.csv");
    return 0;
}