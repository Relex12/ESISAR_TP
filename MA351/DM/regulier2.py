from accessibilite import *
from promenade import *
from graphes import *

def estReg2 (graphe):
	for i, items in graphe.items():
		if len(items) != 2:
			return False
	return True

def cycle(graphe, i):
	liste = list()
	init = i
	p = init
	s = graphe[init][0]
	liste.append(init)
	liste.append(s)
	while (s != init):
		for e in graphe[s]:
			if e != p:
				p = s
				s = e
				liste.append(s)
				break
	return liste

def retour_de_deux_reguliers_de_degre_2():
	liste = list()
	for i in range (1, 10):
		for j in range (1, 10):
			if estReg2(graphe_oriente(i, j)):
				liste.append((i, j))
	return liste

def est_dans_liste (liste, i):
	for x in liste:
		if x == i:
			return True
	return False

def structure_en_cycles (graphe):
	liste = list()
	for i, item in graphe.items():
		if est_dans_liste(liste, i) == False:
			liste = liste + cycle (graphe, i)
	for i, item in graphe.items():
		if est_dans_liste(liste, i) == False:
			return False
	return True

regulier1 = graphe_oriente(3, 1)
regulier2 = {1: [2, 4], 2:[1, 3], 3:[2, 4], 4:[3, 1]}

retour_de_deux_reguliers_de_degre_2()
