data Couleur = Rouge | Bleu | Vert | Jaune | Orange | Violet

primaire :: Couleur -> Bool
primaire Rouge = True
primaire Bleu = True
primaire Jaune = True
primaire Vert = False
primaire Orange = False
primaire Violet = False

defcl :: Couleur -> String
defcl Rouge = "Rouge"
defcl Bleu = "Bleu"
defcl Jaune = "Jaune"
defcl Vert = "Bleu + Jaune"
defcl Orange = "Rouge + Jaune"
defcl Violet = "Rouge + Bleu"


