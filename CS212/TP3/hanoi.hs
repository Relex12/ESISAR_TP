
module Hanoi where

import Set


data Pos = A | B | C  deriving (Show, Eq)
data Movement = Mvt Int Pos Pos   deriving (Show)

hanoi :: Int -> [Movement]
hanoi k = hanoi_aux k A B


hanoi_aux :: Int -> Pos -> Pos -> [Movement]
hanoi_aux 1 pos1 pos2 = [Mvt 1 pos1 pos2]
hanoi_aux k pos1 pos2 	| pos1 /= pos2 = mise k pos1 pos2
			| pos1 == pos2 = []

mise k pos1 pos2 = (hanoi_aux (k-1) pos1 (other pos1 pos2)) ++ [Mvt k pos1 pos2] ++ (hanoi_aux (k-1) (other pos1 pos2) pos2)



{-
pour déplacer une pile de k objets de la position p1 à la position p2 , il suffit de déplacer k-1
objets de la position p1 à la position p3 , puis de déplacer l’objet de taille k de la position p1 à la
position p2 , puis finalement de déplacer k-1 objets de la position p3 à la position p2 , où p3
désigne la position qui n’est ni p1 , ni p2 
-}

other :: Pos -> Pos -> Pos 
other A B = C
other A C = B
other B A = C
other B C = A
other C A = B
other C B = A

{-
other :: Pos -> Maybe Pos -> Pos 	-- utiliser Maybe
other A Just B = C
other A Just C = B
other B Just A = C
other B Just C = A
other C Just A = B
other C Just B = A
-}


