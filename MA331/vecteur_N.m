% vecteur_N prend en argument N la longueur du vecteur
% et p0 la probabilité d'avoir un 1 pour chaque bitand
% elle renvoit un vecteur de N bits

function [vecteur] = vecteur_N (N, p0)
  vecteur = [];
  for i = 1 : N
    if (rand(1) < p0)
      vecteur = [vecteur, 1];
    else 
      vecteur = [vecteur, 0];
    endif
  endfor
endfunction  