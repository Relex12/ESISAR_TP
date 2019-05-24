from accessibilite import *
from promenade import *
from graphes import *


def puits_ou_circuit (graphe):
	x = 1;
	liste = list()
	liste.append(x)
	while (graphe[x] != []):
		y = graphe[x][0]
		for i in liste:
			if y == i:
				return (liste, "liste")
		liste.append(y)
		x = y
	return (x, "sommet")

def estCircuit (liste, graphe):
	for i, items in graphe.items():
		if i == liste[0]:
			for j in items:
				if j == liste[len(liste)-1]:
					return True
		if i == liste[len(liste)-1]:
			for j in items:
				if j == liste[0]:
					return True
	return False

def circuit_ou_tri_topologique(graphe):
	if graphe == {}:
		return {}
	(result, type) = puits_ou_circuit(graphe)
	if type == "liste":
		return result
	return graphe
#	graphe.pop(result)
#	R2 = circuit_ou_tri_topologique(graphe)
#	if estCircuit (R2):
#		return R2
#	return R2 + (R, len(graphe))

puits_ou_circuit(graphe_oriente(5, 3))
#circuit_ou_tri_topologique(graphe_oriente(5, 3))		#renvoie un circuit
#circuit_ou_tri_topologique(graphe_oriente(6, 4))		#renvoie un tri topologique
