#!/bin/bash
#Verify is there is an argument when the script is launched, exits the script is there is no arguments
if [ $# -lt 1 ]; then 
    echo "Il n'y a pas assez d'arguments. Faites --help pour avoir la liste des arguments";
    exit 1;
fi

#Display the help section when the user ask it
if [ $1 == "--help" ]; then
    echo -e "---------------------------------------------------------------\nUSAGE: [ ./main.sh -f <fichier d'entrée> [autres options]  ]\n    Le fichier d'entrée est une option obligatoire. Afin que le programme fonctionne, veuillez utiliser au moins une option.\n---------------------------------------------------------------\nVoici la liste des arguments: \n\t-t <mode>\t Trie les données en fonction de la température et les affiche en fonction du mode. (Modes référencés en bas)\n\t-p <mode>\t Trie les données en fonction de la pression et les affiche en fonction du mode. \n\t-w\t         Affiche un diagramme de type VECTEUR contenant la direction et la vitesse du vent par station. \n\t-h\t         Affiche une carte interpolée et colorée en fonction de l'altitude enregistrée dans chaque station. \n\t-m\t         Affiche une carte interpolée et colorée en fonction de l'humidité enregistrée dans chaque station.\n\t-d <min> <max>\t Sélectionne un intervalle de temps (sous format YYYY-MM-DD) dans lequel les données seront traitées\n\n---------------------------------------------------------------\n     MODES :\n\t1 : Affiche les données sous forme d'un diagramme à batons.\n\t2 : Affiche les données sous forme d'un graphique à ligne simple. \n\t3 : Affiche les données sous forme d'un graphique à multi-lignes. \n---------------------------------------------------------------";
    exit 0;
fi

#Verify is there is enough arguments when the script is launched, exits the script is there is not enough arguments
if [ $# -lt 3 ]; then 
    echo "Il n'y a pas assez d'arguments. Faites --help pour avoir la liste des arguments";
    exit 1;
fi

#Creating all the files that are necessary to run the script
make all

#Defining every option available
type="--avl";
input="NULL";
reverse="NULL";
temp="NULL";
alti="NULL"
press="NULL";
wind="NULL";
humi="NULL";
mode1="NULL";
mode2="NULL";

#Activating all the option asked by the user
for ((i=1; i<=$#; i++)); do
    if [[ "${!i}" == "-f" ]]; then 
        i=$(($i+1));
        input=${!i};
        i=$(($i-1));
    fi
    if [[ "${!i}" == "--abr" ]]; then
        type=${!i};
    fi
    if [[ "${!i}" == "--tab" ]]; then
        type=${!i};
    fi 
    if [[ "${!i}" == "--avl" ]]; then
        type=${!i};
    fi 
    if [[ "${!i}" == "-r" ]]; then
        reverse=${!i};
    fi 
    if [[ "${!i}" == "-m" ]]; then
        humi=${!i};
    fi
    if [[ "${!i}" == "-w" ]]; then
        wind=${!i};
    fi
    if [[ "${!i}" == "-h" ]]; then
        alti=${!i};
    fi
    if [[ "$reverse" == "NULL" ]] && [[ "${!i}" == "-h" ]]; then  
        reverse="-r";
    fi
    if [[ "$reverse" == "-r" ]] && [[ "${!i}" == "-h" ]]; then  
        reverse="NULL";
    fi
    if [[ "$reverse" == "NULL" ]] && [[ "${!i}" == "-m" ]]; then  
        reverse="-r";
    fi
    if [[ "$reverse" == "-r" ]] && [[ "${!i}" == "-m" ]]; then  
        reverse="NULL";
    fi
    if [[ "${!i}" == "-t" ]] || [[ "${!i}" == "-p" ]]; then
        if [[ "${!i}" == "-t" ]]; then   
            temp=${!i};
            mode1=$((i+1));
        fi
        if [[ "${!i}" == "-p" ]]; then
            press=${!i};
            mode2=$((i+1));
        fi
    fi
done

#Cheking if an input file has been entered, if not the script exits
if [[ "$input" == "NULL" ]]; then 
    echo -e "Veuillez inserer le fichier d'entrée contenant les données.\n";
    exit 1;
fi

#Cheking if at least one sort option has been choosed, if not the script exits
if [[ "$temp" == "NULL" ]] && [[ "$wind" == "NULL" ]] && [[ "$humi" == "NULL" ]] && [[ "$press" == "NULL" ]] && [[ "$alti" == "NULL" ]]; then
    echo -e "Veuillez inserer une option de tri afin que le programme fonctionne.\n";
    exit 1;
fi

#Sorting if the option is on, if there is a problem in the execution, it returns a error message
if [[ "$temp" != "NULL" ]]; then
    echo "Malheureusement cette option n'est pas fonctionnelle."
fi

if [[ "$press" != "NULL" ]]; then
    echo "Malheureusement cette option n'est pas fonctionnelle."
fi

if [[ "$wind" != "NULL" ]]; then
    cut -d ';' --fields=5,4,1 ./$input > vent.txt;
    code=$?;
    if [[ code -ne 0 ]]; then
        echo "Il y a eu une problème avec le filtrage du fichier, veuillez réessayer."
        exit 1;
    fi
    ./tri -f vent $wind $reverse $type -o out
    code=$?;
    if [[ code -ne 0 ]]; then
        echo "Il y a eu une problème avec le tri du fichier, veuillez réessayer."
        exit 1;
    fi
fi

if [[ "$humi" != "NULL" ]]; then
    cut -d ';' --fields=6,1 ./$input > humidite.txt;
    code=$?;
    if [[ code -ne 0 ]]; then
        echo "Il y a eu une problème avec le filtrage du fichier, veuillez réessayer."
        exit 1;
    fi
    ./tri -f humidite $humi $reverse $type -o out
    code=$?;
    if [[ code -ne 0 ]]; then
        echo "Il y a eu une problème avec le tri du fichier, veuillez réessayer."
        exit 1;
    fi
fi

if [[ "$alti" != "NULL" ]]; then
    cut -d ';' --fields=14,1 ./$input > altitude.txt;
    code=$?;
    if [[ code -ne 0 ]]; then
        echo "Il y a eu une problème avec le filtrage du fichier, veuillez réessayer."
        exit 1;
    fi
    ./tri -f altitude $alti $reverse $type -o out
    code=$?;
    if [[ code -ne 0 ]]; then
        echo "Il y a eu une problème avec le tri du fichier, veuillez réessayer."
        exit 1;
    fi
fi

#Execution successful -> sends a message to say where are the output files and how the output files are names
if [[ code -eq 0 ]]; then
    echo "Le fichier $input a été trié selon les options avec succès. Les fichiers de sorties sont nommés 'out-<nom-de-l'option-choisie>.csv' et se trouvent dans le répertoire dans lequel le programme a été lancé."
fi

#Cleaning the folder and exit
make clean
exit 0