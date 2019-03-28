
repeter 1 c = c
repeter n c = c ++ (repeter (n-1) c)


etoile n c = (repeter n "*") ++ c ++ (repeter n "*")


slashes c = "/" ++ c ++ "/"


commentaireC c =  (slashes . etoile 12) c


