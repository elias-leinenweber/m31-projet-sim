#!/bin/sh

# Fichiers utilisés
main=out/aloha
res=res.csv
report=compte-rendu.Rmd

# Paramètres par défaut
# TODO Utiliser `getopt` : https://www.shellscript.sh/tips/getopt/
p=${1:-0.01}
k=${2:-10}
n=${3:-200}

[ -z $v ] && debug_out=/dev/null || debug_out=/dev/stdout

echo "=== Compilation ==="
make > $debug_out || exit 1

echo "=== Exécution de la simulation ==="
$main $p $k $n > $res 2>$debug_out || exit 1

echo "=== Génération du compte-rendu ==="
if Rscript -e "rmarkdown::render('$report')" 1>/dev/null 2>&1
then
	echo "Compte-rendu généré avec succès : `echo $report | cut -d'.' -f1`.pdf"
	exit 0
else
	echo "Échec dans la génération du compte-rendu."
	exit 1
fi
