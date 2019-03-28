{-
cumule :: (a -> a -> a) -> a -> [a] -> a
cumule f x [] = x
cumule f x (k:ks) = (cumule f (f x k) ks)

somme2 :: [Int] -> Int
somme2 (i:is) = cumule (+) i is


somme :: Num a => [a] -> a
somme (i:is) = cumule (+) i is
-}


module IE where 

--module IE (Agregeable, cumule , operation, neutre)


class Agregeable a where 
    operation :: a -> a -> a
    neutre :: a

instance Agregeable Int where
    neutre = 0
    operation = (+) 

cumule :: Agregeable a => [a] -> a
cumule [] = neutre 
cumule (x:xs) = operation x (cumule xs)

l1 :: [Int]
l1 = [1,2,3,4,5]

l2 :: [Int]
l2 = [6,7,8,9]


instance Agregeable Bool where
    neutre = False
    operation a b = a || b

instance Agregeable [a] where
    neutre = []
    operation a b = a ++ b



