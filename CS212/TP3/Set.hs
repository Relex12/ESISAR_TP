
module Set where

data Set a = Set [a] 		deriving Show 		-- deriving Show ajouté a posteriori

set :: [a] -> Set a
set l = Set l

set_difference :: (Eq a) => Set a -> Set a -> Set a
set_difference s1 (Set []) = s1
set_difference s1 (Set (x:xs)) = remove x (set_difference s1 (Set xs))

remove :: (Eq a) => a -> Set a -> Set a
remove x (Set []) = Set []
remove x (Set (u:us)) | x == u = Set us
                      | otherwise = Set (u:r)
                          where Set r = remove x (Set us)

grab :: Set a -> a
grab (Set (x:xs)) = x



