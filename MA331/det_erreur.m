% det_erreur est la fonction de détection d'erreur de Hamming (7, 4)

% elle prend en argument entree le vecteur de taille 7
% elle renvoit 1 si le syndrome est nul, 0 sinon

function [sortie] = det_erreur(entree)
  S = syndrome(entree);
  if (isequal(S, zeros(1, 3)))
    sortie = 1;
  else 
    sortie = 0;
  endif
endfunction