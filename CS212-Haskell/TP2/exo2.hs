

--halve :: [Int] -> ([Int], [Int])
halve :: [a] -> ([a], [a])
halve a = splitAt (div (length a) 2) a






combine :: ([Int],[Int]) -> [Int]
combine (xs,[]) = xs
combine ([],ys) = ys
combine ((x:xs),(y:ys)) = if x<=y then x : (combine (xs,(y:ys))) else y : (combine ((x:xs),ys)) 


trifusion :: [Int] -> [Int]
trifusion [] = []
trifusion [i] = [i]
trifusion i = combine ((trifusion(fst (halve i))), (trifusion(snd(halve i))))

