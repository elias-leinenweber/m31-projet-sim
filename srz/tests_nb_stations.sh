#!/bin/bash
# Usage: rien du tout

touch ./scripts/data

echo -e "proba\tk\tnbStations\tnbSlots\tnbSlotsUtiles\tnbMessagesEnAttente" > ./scripts/data

rand_type=""
while [[ $rand_type != "u" && $rand_type != "b" ]]
do	
	echo "uniforme ou beb (u/b) :"
	read rand_type
done

if [[ $rand_type = "u" ]]
then
	script_name="plot_uniform"
else
	script_name="plot_beb"
fi

y_axis=""
while [[ $y_axis != "m" && $y_axis != "n" ]]
do
	echo "nombre de slots utiles ou moyenne de messages en attente (n/m) :"
	read y_axis
done

if [[ $y_axis = "m" ]]
then
	script_name=$script_name+"stack_mean"
else
	script_name=$script_name+"stack_mean"
fi

script_name=$script_name+".R"

echo "nombre de slots :"
read nb_slots


echo "min nombre de stations:"
read nb_stations_min

echo "max nombre de stations"
read nb_stations_max

echo "proba :"
read proba

kmin=0
kmax=0
if [[ $rand_type = "u" ]]
then
	echo "k min :"
	read kmin
	echo "k_max :"
	read kmax
fi

for (( nb_stations=nb_stations_min; nb_stations<=nb_stations_max; nb_stations++ ))
do
	if [[ $rand_type = "u" ]]
	then
		for (( k=kmin; k<=kmax; k++ ))
		do
			./main u $nb_slots $nb_stations $proba $k >> ./scripts/data
		done
	else
		./main b $nb_slots $nb_stations $proba >> ./scripts/data
	fi
done



Rscript --vanilla ./scripts/plot_nb_stations.R $rand_type $y_axis
