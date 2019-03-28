
data Liste = Vide | Cell Int Liste deriving Show



vide :: Liste -> Bool
vide Vide = True
vide (Cell x l) = False


premier :: Liste -> Int
premier (Cell x l) = x


premier Vide = 0

reste :: Liste -> Liste
reste Vide = Vide
reste (Cell x l) = l


longueur :: Liste -> Int
longueur Vide = 0
longueur (Cell x l) = 1 + longueur (l)


dernier :: Liste -> Int
dernier (Cell x Vide) = x
dernier (Cell x l) = dernier (l)



applique :: (Int -> Int) -> Liste -> Liste
applique a Vide = Vide
applique a (Cell x l) = (Cell (a x) (applique a l))


ajoute :: Int -> Liste -> Liste
ajoute a Vide = (Cell a Vide)
ajoute a (Cell x l) = (Cell x (ajoute a l))


renverse :: Liste -> Liste
renverse Vide = Vide
renverse (Cell x l) = ajoute x (renverse l)


