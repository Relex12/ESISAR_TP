"""Accessibilite dans les graphes orientes.

"""

"Calcule les sommets de g accessibles depuis s"
def accessibles(g, s):
	M = set()
	O = {}
	M.add(s)
	"Prendre tous les voisinnages de sommets de S; voir s'il y en a un de non vide"
	a = arc_sortant(g, M)
	while a != None:
		M.add(a[1])
		O[a[1]] = a[0]
		a = arc_sortant(g, M)
	return (M, O)

"Arcs sortant de M dans g"
def arc_sortant(g, M):
	for i in M:
		s = set(g[i])
		s.difference_update(M)
		l = list(s)
		if len(l) != 0:
			return (i, (list(s))[0])
	return None

"""
Test:
g = {1: [3, 4], 2: [3, 1], 3: [], 4: []}
arc_sortant(g, [3])
arc_sortant(g, [1, 2, 3])
"""
