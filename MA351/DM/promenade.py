from graphes import *

"Promenade dans les arbres"
def promenade(g, x):
	y = g[x][0]
	while degre(g, y) != 1:
		z = g[y][0]
		if z == x:
			z = g[y][1]
		x = y
		y = z
	return y

def degre(g, x):
	return len(g[x])
