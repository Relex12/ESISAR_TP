% chaine prend en argument entree le vecteur de taille 4
% à l'entrée de la chaine, bruit la probabilité d'erreur du canal
% elle renvoit la sortie du canal, corrigé par Hamming (7, 4)

function [sortie] = chaine (entree, bruit)
  entree;
  encode = enc_Hamming74(entree);
  sortie_c = canal_BS(7, bruit, encode);
  corrige = cor_erreur(sortie_c);
  decode = dec_Hamming74(corrige);
  sortie = decode;
endfunction