#!/bin/sh

# Décommenter pour activer le mode "verbose"
#v=1

# Décommenter pour uniquement générer le compte-rendu
#nosim=1

# Fichiers utilisés
main=out/aloha
res=res.csv
report=compte-rendu.Rmd

# Paramètres par défaut
p=${1:-0.01}
k=${2:-10}
n=${3:-200}

[ -z $v ] && debug_out=/dev/null || debug_out=/dev/stderr

if [ -z $nosim ]
then
	echo "=== Compilation ==="
	make > $debug_out || exit 1

	echo "=== Exécution de la simulation ==="
	$main $p $k $n 1>$res 2>$debug_out || exit 1
fi

echo "=== Génération du compte-rendu ==="
if Rscript -e "rmarkdown::render('$report')" 1>$debug_out 2>&1
then
	echo "Compte-rendu généré avec succès : `echo $report | cut -d'.' -f1`.pdf"
	exit 0
else
	echo "Échec dans la génération du compte-rendu."
	exit 1
fi
