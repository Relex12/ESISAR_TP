# usage : gnuplot graph.plt


# par défaut, affiche à l'écran
# pour générer un fichier, décommenter les lignes appropriées

# type de fichier
#set term postscript eps
#set term pdf
#set term png

#set output "graph.eps"
#set output "graph.pdf"
#set output "graph.png"

# pour les caractères accentués (en latin 1)
set encoding iso_8859_1

set title "mon titre"
set ylabel "efficacité"
set xlabel "taux de perte"
plot "log1" w lp title "trace 1", "log2" w lp title "trace 2"

# attend que l'on tape entrée
pause -1
