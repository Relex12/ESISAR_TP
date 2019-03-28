
echange :: (a -> a -> a) -> (a -> a -> a)
echange f a b = f b a


cube a = echange (^) 3 a


moinsDeux a = echange (-) 2 a


