#!/bin/sh

main=out/main
res=res.csv
report=compte-rendu.Rmd

echo "=== Compilation ==="
make || exit 1

echo "=== Exécution de la simulation ==="
$main > $res || exit 1

echo "=== Génération du compte-rendu ==="
Rscript -e "rmarkdown::render('$report')"
