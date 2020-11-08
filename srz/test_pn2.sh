#!/bin/bash
# Usage: rien du tout

touch ./scripts/data

echo -e "proba\tk\tnbStations\tnbSlots\tnbSlotsUtiles\tnbMessagesEnAttente" > ./scripts/data

echo "u ou b (uniforme/beb)"
read typeR

echo "nombre de slots max :"
read nb_slots_max


echo "proba :"
read proba

echo "p*n min :"
read pn_min

echo "p*n max :"
read pn_max

echo "pas :"
read pas

echo "k :"
read k

./main_t2 $typeR $nb_slots_max $proba $pn_min $pn_max $pas $k >> ./scripts/data



