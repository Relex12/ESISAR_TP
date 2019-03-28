
import IE

data Int_ex = Moins_inf | I Int deriving Show

max_ie :: Int_ex -> Int_ex -> Int_ex
max_ie Moins_inf Moins_inf = Moins_inf 
max_ie Moins_inf (I a) = (I a) 
max_ie (I a) Moins_inf = (I a)
max_ie (I a) (I b) | a < b = (I b)
                   | otherwise = (I a)

instance Agregeable Int_ex where
    neutre = Moins_inf
    operation a b = max_ie a b

listex1 :: [Int_ex]
listex1 = [(I 4),(I 2),(I 6),Moins_inf]

listex2 :: [Int_ex]
listex2 = [(I 4),(I 2),(I 6),(I 8)]

max_liste :: [Int] -> Int_ex
max_liste [] = Moins_inf
max_liste x = cumule (map I x)


