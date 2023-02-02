#!/bin/bash
if [ $# -lt 1 ]; then 
    echo "Il n'y a pas assez d'arguments. Faites --help pour avoir la liste des arguments";
    exit 1;
fi

if [ $1 = "--help" ]; then
    echo -e "---------------------------------------------------------------\nUSAGE: [ ./main.sh -f <fichier d'entrée> [autres options]  ]\n    Le fichier d'entrée est une option obligatoire. Afin que le programme fonctionne, veuillez utiliser au moins une option.\n---------------------------------------------------------------\nVoici la liste des arguments: \n\t-t <mode>\t Trie les données en fonction de la température et les affiche en fonction du mode. (Modes référencés en bas)\n\t-p <mode>\t Trie les données en fonction de la pression et les affiche en fonction du mode. \n\t-w\t         Affiche un diagramme de type VECTEUR contenant la direction et la vitesse du vent par station. \n\t-h\t         Affiche une carte interpolée et colorée en fonction de l'altitude enregistrée dans chaque station. \n\t-m\t         Affiche une carte interpolée et colorée en fonction de l'humidité enregistrée dans chaque station.\n\t-d <min> <max>\t Sélectionne un intervalle de temps (sous format YYYY-MM-DD) dans lequel les données seront traitées\n\n---------------------------------------------------------------\n     MODES :\n\t1 : Affiche les données sous forme d'un diagramme à batons.\n\t2 : Affiche les données sous forme d'un graphique à ligne simple. \n\t3 : Affiche les données sous forme d'un graphique à multi-lignes. \n---------------------------------------------------------------";
    exit 0;
fi

if [ $# -lt 3 ]; then 
    echo "Il n'y a pas assez d'arguments. Faites --help pour avoir la liste des arguments";
    exit 1;
fi

type="--avl";
input="undefined";
reverse="undefined";
temp="undefined";
alti="undefined"
press="undefined";
wind="undefined";
humi="undefined";
mode1="undefined";
mode2="undefined";

for ((i=1; i<$#; i++)); do
    if [ ${!i} = "-f" ]; then 
        input=$((i+1));
    fi
    if [ ${!i} = "--abr" ]; then
        type=${!i};
    fi
    if [ ${!i} = "--tab" ]; then
        type=${!i};
    fi 
    if [ ${!i} = "--avl" ]; then
        type=${!i};
    fi 
    if [ ${!i} = "-r" ]; then
        reverse=${!i};
    fi 
    if [ ${!i} = "-m" ]; then
        humi=${!i};
    fi
    if [ ${!i} = "-w" ]; then
        wind=${!i};
    fi
    if [ reverse = "undefined" ] && [ ${!i} = "-h" ]; then  
        reverse="-r";
    fi
    if [ reverse = "-r" ] && [ ${!i} = "-h" ]; then  
        reverse="undefined";
    fi
    if [ reverse = "undefined" ] && [ ${!i} = "-m" ]; then  
        reverse="-r";
    fi
    if [ reverse = "-r" ] && [ ${!i} = "-m" ]; then  
        reverse="undefined";
    fi
    if [ ${!i} = "-t" ] || [ ${!i} = "-p" ]; then
        if [ ${!i} = "-t" ]; then   
            temp=${!i};
            mode1=$((i+1));
        fi
        if [ ${!i} = "-p" ]; then
            press=${!i};
            mode2=$((i+1));
        fi
    fi
done

if [ ${!input} = "undefined" ]; then 
    echo -e "Veuillez inserer le fichier d'entrée contenant les données.\n";
    exit 1;
fi

if [ temp = "undefined" ] && [ wind = "undefined" ] && [ humi = "undefined" ] && [ press = "undefined" ] && [ alti = "undefined" ]; then
    echo -e "Veuillez inserer une option de tri afin que le programme fonction.\n";
    exit 1;
fi

if [ temp != "undefined" ]; then
    echo `cut -d ';' --fields=11,1 ./${!input} >> temperature.txt`;
    code=$?;
    if [ code -ne 0 ]; then
        echo "Il y a eu une problème avec le filtrage du fichier, veuillez réessayer."
        exit 1;
    fi
    echo `./tri -f temperature ${!temp} ${!mode1} -o out`
    code=$?;
    if [ code -ne 0 ]; then
        echo "Il y a eu une problème avec le tri du fichier, veuillez réessayer."
        exit 1;
    fi
fi

if [ press != "undefined" ]; then
    echo `cut -d ';' --fields=11,1 ./${!input} >> temperature.txt`;
    code=$?;
    if [ code -ne 0 ]; then
        echo "Il y a eu une problème avec le filtrage du fichier, veuillez réessayer."
        exit 1;
    fi
    echo `./tri -f temperature ${!press} ${!mode2} -o out`
    code=$?;
    if [ code -ne 0 ]; then
        echo "Il y a eu une problème avec le tri du fichier, veuillez réessayer."
        exit 1;
    fi
fi

if [ wind != "undefined" ]; then
    echo `cut -d ';' --fields=11,1 ./${!input} >> temperature.txt`;
    code=$?;
    if [ code -ne 0 ]; then
        echo "Il y a eu une problème avec le filtrage du fichier, veuillez réessayer."
        exit 1;
    fi
    echo `./tri -f temperature ${!wind} -o out`
    code=$?;
    if [ code -ne 0 ]; then
        echo "Il y a eu une problème avec le tri du fichier, veuillez réessayer."
        exit 1;
    fi
fi

if [ humi != "undefined" ]; then
    echo `cut -d ';' --fields=6,1 ./${!input} >> humidite.txt`;
    code=$?;
    if [ code -ne 0 ]; then
        echo "Il y a eu une problème avec le filtrage du fichier, veuillez réessayer."
        exit 1;
    fi
    echo `./tri -f humidite ${!humi} ${!reverse} -o out`
    code=$?;
    if [ code -ne 0 ]; then
        echo "Il y a eu une problème avec le tri du fichier, veuillez réessayer."
        exit 1;
    fi
fi

if [ alti != "undefined" ]; then
    echo `cut -d ';' --fields=14,1 ./${!input} >> altitude.txt`;
    code=$?;
    if [ code -ne 0 ]; then
        echo "Il y a eu une problème avec le filtrage du fichier, veuillez réessayer."
        exit 1;
    fi
    echo `./tri -f altitude ${!alti} ${!reverse} -o out`
    code=$?;
    if [ code -ne 0 ]; then
        echo "Il y a eu une problème avec le tri du fichier, veuillez réessayer."
        exit 1;
    fi
fi
