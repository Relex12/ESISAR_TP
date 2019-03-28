#1:
def exposant (x, n):
    resultat = 1
    for i in range (n):
        resultat = resultat * x
    return (resultat)
    
#2: exposant (3,19)
#Out[28]: 1162261467

#3: on effectue n multiplications pour x ^ n (complixité linéaire)

#4:
def exposant_bis (x, n):
    resultat = 1
    for i in range (n // 2):
        resultat = resultat * x
    resultat = resultat * resultat
    if n % 2 != 0:
        resultat = resultat * x
    return (resultat)

# exposant_bis (3,19)
#Out[25]: 1162261467

# pour calculer x ^ 1023, on effectue 513 multiplications



#soustraction de matrices
def sous_matr (m,n):
    assert len (m[0]) == len (n[0]) and len(m) == len (n)
    p = [[None] * len (m[0]) for l in range (len(m))]
    for i in range (len(m)):
        for j in range (len(m[0])):
            p[i][j] = m[i][j] - n[i][j]
    return (p)

#multiplication de tableau
def multi_matri(m,k):
    for i in  range (len(m)):
        for j in range (len(m[0])):
            m[i][j] = k * m[i][j]
    return (m)
    

#saisir une liste
def créer_list ():
    print('veuillez saisir votre liste  ')
    l = input().split(',')
    print (l)

#intersection
def inter (k,l):
    k = list(set(k))
    l = list(set(l))
    resultat = []
    for i in range (len(k)):
        for j in range (len(l)):
            if k[i] == l[j]:
                resultat = resultat + [k[i]]
    resultat = set(resultat)
    return (resultat)
    
#réunion
def union (k,l):
    m = set(k+l)
    return (m)
    
#inclusion
def inclu (k,l):
    if inter (k,l) == set(k):
        print ('k inclu dans l')
        return (True)
    else :
        print ('k non inclu dans l')
        return (False)
        
        
#palindrôme
def test (mot):
    mot = list (mot)
    for i in range (len(mot)):
        if mot[i]!= mot[-i-1]:
            return (False)
    return (True)

def test2 (): #ce programme est une deuxième version du précédent car une fonction n'accepte pas une chaîne de caractères en paramètres sans guillemets
    print ('entrez vote mot : ')
    mot = list(input())
    for i in range (len(mot)):
        if mot[i]!= mot[-i-1]:
            return (False)
    return (True)
    
def test_complet2 ():
    print ('entrez votre phrase : ')
    m = input ()
    m = list(m)
    p = []
    n = list('a''b''c''d''e''f''g''h''i''j''k''l''m''n''o''p''q''r''s''t''u''v''w''x''y''z')
    for i in range (len(m)):
        if m[i] in n :
            p += m[i]
    for i in range (len(p)):
        if p[i]!= p[-i-1]:
            return (False)
    return (True)
        