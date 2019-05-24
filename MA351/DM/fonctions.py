from accessibilite import *
from promenade import *
from graphes import *

"Retour de deux feuilles "
def deux_feuilles(arbre):
	feuilles = list()
	for (i, item) in arbre.items():
		if len(item) == 1:
			feuilles.append(i)
			if len(feuilles) == 2:
				break
	return feuilles

def decompose(arbre):
	init = deux_feuilles(arbre)[0]
	element = init
	parent = None
	liste = list()
	recurDecompo (arbre, liste, element, parent)
	return (init, liste)


def recurDecompo (arbre, liste, element, parent):
	for (i, item) in arbre.items():
		if i == element:
			for suivant in item:
				if (suivant != parent):
					liste.append((element, suivant))
					recurDecompo (arbre, liste, suivant, element)

def mise_en_forme (couple):
	print("On part du sommet " + str(couple[0]))
	couples = couple[1]
	for i, j in couples:
		print("On attache le sommet " + str(j) + " au sommet " + str(i))


def couleur (arbre):
	element = deux_feuilles(arbre)[0]
	parent = None
	dico = {}
	couleur = 0
	recurCoul (arbre, dico, element, parent, couleur)
	return (dico)


def recurCoul (arbre, dico, element, parent, couleur):
	for (i, item) in arbre.items():
		if i == element:
			for suivant in item:
				dico[element] = couleur
				if (suivant != parent):
					recurCoul (arbre, dico, suivant, element, (couleur + 1) % 2)

def mise_en_couleur (dico):
	for i, j in dico.items():
		if j == 0:
			print("Le sommet " + str(i) + " est en bleu")
		else:
			print("Le sommet " + str(i) + " est en rouge")

mise_en_forme(decompose(arbre(10, 4)))
mise_en_couleur(couleur(arbre(10, 4)))
