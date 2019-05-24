from graphes import *
from promenade import *




def puits_ou_circuit(graphe_o):
    # on prend un élement au hasard dans le graphe
    # ici toujours le premier pour reproductibilité
    x = list(graphe_o)[0]
    y = None
    M = []

    while len(graphe_o[x]) > 0:
        # Pareil : n'importe lequel
        # donc ça peut être le premier
        y = graphe_o[x][0]


        if y in M:
            # Circuit trouvé !
            # On va chercher le circuit car contrairement au cours
            # là il faut donner le circuit
            # Le circuit ne commence pas forcément au début de la liste

            for id, item in enumerate(M):
                if item == y:
                    return M

        M.append(y)
        x = y

    return [x]




def supprimer_noeud_graphe(graphe, noeud):
    # On retire ce noeud
    graphe.pop(noeud)
    # Obligé de parcourir tous les autres :(
    for id, items in graphe.items():
        # Si ref au noeud initial
        if noeud in items:
            # Faut supprimer
            items.remove(noeud)
            graphe[id] = items
    return graphe


def tri_topologique(graphe_o):
    liste_ordre = list()

    while len(graphe_o) > 0:
        retour = puits_ou_circuit(graphe_o)

        if len(retour) != 1:
            return retour
        liste_ordre.append(retour[0])
        graphe_o = supprimer_noeud_graphe(graphe_o, retour[0])

    liste_ordre.reverse()
    return liste_ordre



if __name__ == "__main__":
    graphe_o = graphe_oriente(6, 5)
    print(graphe_o)
    print(tri_topologique(graphe_o))
