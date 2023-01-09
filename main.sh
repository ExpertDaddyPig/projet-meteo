#!/bin/bash
if [ $# -lt 1 ]; then 
    echo "Il n'y a pas assez d'arguments. Faites --help pour avoir la liste des arguments";
    exit 1;
fi

if [ $1 = "--help" ]; then
    echo -e "---------------------------------------------------------------\nUSAGE: [ ./main.sh -f <fichier d'entrée> [autres options]  ]\n    Le fichier d'entrée est une option obligatoire. Afin que le programme fonctionne, veuillez utiliser au moins d'un option.\n---------------------------------------------------------------\nVoici la liste des arguments: \n\t-t <mode>\t Trie les données en fonction de la température et les affiche en fonction du mode. (Modes référencés en bas)\n\t-p <mode>\t Trie les données en fonction de la pression et les affiche en fonction du mode. \n\t-w\t         Affiche un diagramme de type VECTEUR contenant la direction et la vitesse du vent par station. \n\t-h\t         Affiche une carte interpolée et colorée en fonction de l'altitude enregistrée dans chaque station. \n\t-m\t         Affiche une carte interpolée et colorée en fonction de l'humidité enregistrée dans chaque station.\n\t-d <min> <max>\t Sélectionne un intervalle de temps (sous format YYYY-MM-DD) dans lequel les données seront traitées\n\n---------------------------------------------------------------\n     MODES :\n\t1 : Affiche les données sous forme d'un diagramme à batons.\n\t2 : Affiche les données sous forme d'un graphique à ligne simple. \n\t3 : Affiche les données sous forme d'un graphique à multi-lignes. \n---------------------------------------------------------------";
    exit 0;
fi

if [ $# -lt 3 ]; then 
    echo "Il n'y a pas assez d'arguments. Faites --help pour avoir la liste des arguments";
    exit 1;
fi
