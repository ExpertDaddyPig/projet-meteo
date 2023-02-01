all: exec

files: 
	echo `cut -d ';' --fields=5,1 ./meteo_filtered_data_v1.csv > vitesse-vent.txt`
	echo `cut -d ';' --fields=4,1 ./meteo_filtered_data_v1.csv > direction-vent.txt`
	echo `cut -d ';' --fields=11,1 ./meteo_filtered_data_v1.csv > temperature.txt`
	echo `cut -d ';' --fields=12,1 ./meteo_filtered_data_v1.csv > temperature-min.txt`
	echo `cut -d ';' --fields=13,1 ./meteo_filtered_data_v1.csv > temperature-max.txt`
	echo `cut -d ';' --fields=3,1 ./meteo_filtered_data_v1.csv > pression-station.txt`
	echo `cut -d ';' --fields=7,1 ./meteo_filtered_data_v1.csv > pression-mer.txt`
	echo `cut -d ';' --fields=14,1 ./meteo_filtered_data_v1.csv > altitude.txt`
	echo `cut -d ';' --fields=6,1 ./meteo_filtered_data_v1.csv > humidite.txt`

exec: files
	gcc -o tri tri_dossier.c

clean: 
	rm -f *.txt
	rm tri
	@echo "TOUT LES FICHIERS TEMPORAIRES SONT EFFACES"