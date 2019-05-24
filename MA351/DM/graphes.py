"""Exemples de graphes"""

from accessibilite import *

"Generateur de graphe oriente"
def graphe_oriente(n, k):
	d = {}
	for i in range(1, n+1):
		d[i] = list()
		for j in range(1, n+1):
			if ((i + j)^2) % (i % k + k) == 0 and i != j:
				d[i].append(j)
	return d


"Generateur d'arbre"
def arbre(n, k):
	g1 = graphe_oriente(n, k)
	(M, O) = accessibles(g1, 1)
	g2 = {}
	for x in M:
		g2[x] = list()
	for x in M:
		if x != 1:
			g2[x].append(O[x])
			g2[O[x]].append(x)
	return g2
