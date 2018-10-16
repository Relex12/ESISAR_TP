
somme :: [Int] -> Int
somme [] = 0
somme (i:is) = i + somme is


produit :: [Int] -> Int
produit [] = 1
produit (i:is) = i * produit is



cumule f x [] = x
cumule f x (k:ks) = (cumule f (f x k) ks)


somme2 (i:is) = cumule (+) i is

produit2 (i:is) = cumule (*) i is


maxi :: [Int] -> Int
maxi (x:xs) = max_aux xs x



max_aux :: [Int] -> Int -> Int
max_aux [] x = x
max_aux (i:is) x = if x>i then (max_aux is x) else (max_aux is i)

cumule2 f x [] = x
cumule2 f x (k:ks) = f x (cumule f k ks)





