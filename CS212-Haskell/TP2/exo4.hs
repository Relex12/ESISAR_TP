
espace :: Char -> Bool
espace a = esp_x a
	where	esp_x ' ' = True
		esp_x a = False


separe :: (Char -> Bool) -> [Char] -> ([Char], [Char])
separe f [] = ([], [])
separe f (a:as) | (f a) == True = (  ((sep1) ++ ( fst (separe f as)))  , ((sep2) ++ (snd (separe f as))))
                | otherwise = (sep1, sep2)
        where sep1 | (f a) == True = [a]
                   | otherwise = []

              sep2 | (f a) == True = []
                   | otherwise = [a] ++ as




grignote_espaces :: String -> String
--grignote_espaces [] = []
grignote_espaces x = snd (separe espace x)


carac :: Char -> Bool
carac ' ' = False
carac a = True

un_mot :: [Char]->([Char], [Char])
un_mot [] = ([], [])
un_mot a = ((fst(separe carac a)), (grignote_espaces (snd(separe carac a))))



mots :: String -> [String]
mots [] = []
mots x = [fst (mot_aux x)] ++ (mots (snd (mot_aux x)))
	where mot_aux (x) = un_mot (grignote_espaces (x))






