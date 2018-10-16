factorielle :: Int -> Int
factorielle 0 = 1
factorielle x = factorielle (x-1) * x
