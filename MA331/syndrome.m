% syndrome prend en argument entree le vecteur de taille 7
% dont on souhaite calculer le syndrome
% elle renvoit le syndrome sur 3 bits

function [resultat] = syndrome (entree)      
  entree;
  tH = [0 1 1 ; 
        1 0 1 ; 
        1 1 0 ; 
        1 1 1 ; 
        1 0 0 ; 
        0 1 0 ; 
        0 0 1];
  resultat = entree * tH;
  for i = 1 : 3
    resultat (i) = mod (resultat (i), 2);
  endfor
endfunction