--import Data.List
--quick_sort x = sort x

quick_sort :: Ord a => [a] -> [a]
quick_sort [] = []
quick_sort (x:xs) = tri x (quick_sort(xs))

tri :: Ord a => a -> [a] -> [a]
tri a [] = [a]
tri a (x:xs) 	| a < x = a:(tri x xs)
		| otherwise = x:(tri a xs)


maxi :: Ord a => [a] -> a
maxi [a] = a
maxi (x:xs)	| x < (maxi (xs)) = maxi (xs)
		| otherwise = x

mini :: Ord a => [a] -> a
mini [a] = a
mini (x:xs)	| x < (mini (xs)) = x
		| otherwise = mini (xs)



--quick_sort :: Ord a => Enum a => [a] -> [a]
--quick_sort xs = [ x | x <- [mini (xs) .. maxi (xs)], y <- (xs), y == x] 	-- bon nombre grâce à y

--quick_sort xs = [ x | x <- [mini (xs) .. maxi (xs)], x <- (xs)]		--trop d'éléments





--quick_sort (x:y) = if x <= y then (x:y) else (y:x)			ne fonctionne pas
--quick_sort (x:y:xs) = if x <= y then (x:quick_sort(y:xs) else (y:quick_sort(x:xs))

--combinaison k xs = [ zs | zs <- parties xs, length zs == k]



-- 		[4,1,3,2]	4 [1,3,2]
