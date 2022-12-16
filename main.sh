#!/bin/bash
if (($# < 1)); then 
    echo "Il n'y a pas assez d'arguments. Faites --help pour avoir la liste des arguments"
    exit 1
fi

echo `sort -k4 -t';' -n ../meteo_filtered_data_v1.csv >> cut -d ';' -f4 >> vitesse-vent.txt`

if [ $1 == "--help" ]; then 
    echo -e "Voici la liste des arguments: \n\t-t<mode>  \n\t-p<mode>  \n\t-w  \n\t-h  \n\t-m"
    exit 0
fi
