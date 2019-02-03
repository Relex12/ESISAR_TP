% cor_erreur est la fonction de correction d'erreur de Hamming (7, 4)

% elle prend en argument entree le vecteur de taille 7
% elle le message corrigé de taille 7 
% le message corrigé est identique à entree si aucune erreur n'est détectée

function [resultat] = cor_erreur (entree)
  tH = [0 1 1 ; 
        1 0 1 ; 
        1 1 0 ; 
        1 1 1 ; 
        1 0 0 ; 
        0 1 0 ; 
        0 0 1];
  S = syndrome(entree);
  resultat = entree;
  if (!det_erreur (entree))
    for i = 1 : 7
      temp = [tH(i) tH(i+7) tH(i+14)];
      if (S == temp)
         resultat (i) = mod (resultat (i) + 1, 2);
      endif
    endfor
  endif
endfunction