factorielle :: Integer -> Integer
factorielle 0 = 1
factorielle x = factorielle (x-1) * x



creator :: Int -> [Int]
creator 0 = []
creator n = [n] ++ creator (n-1)

--	partie A

ajoute :: a -> [a] -> [a]
ajoute x xs = x:xs

parties :: [a] -> [[a]]
parties [] = [[]]
parties (x:xs) = (parties xs) ++ (map (ajoute x) (parties xs))



nb_parties :: [a] -> Int
nb_parties [] = 1
nb_parties (x:xs) = 2 * (nb_parties xs)

--	partie B
-- question 1

cutter :: Int -> [[a]] -> [[a]]
cutter k [] = []
cutter k (x:xs) = if length x == k then x:cutter k xs else cutter k xs

combinaison :: Int -> [a] -> [[a]]
combinaison k x = cutter k (parties (x))

-- question 2

nb_combi :: Int -> [a] -> Int	
nb_combi k x = length (combinaison k x)

parmi_1 :: Int -> Int -> Int	
parmi_1 k n = length (combinaison k (creator n))

--parmi_2 :: Int -> Int -> Int	
--parmi_2 k n = div (factorielle n) (factorielle (k) * factorielle (n-k))



