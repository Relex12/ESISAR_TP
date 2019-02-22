#!/bin/bash

log=$1
longueur=50000

echo "# taux_de_perte efficacit�" > $log

for tdp in 0 2 4 6 8 10  12 15 20; do
    echo -n "$tdp " >> $log
    ./swp $longueur $tdp 0 0 0
    echo $? >> $log
done
