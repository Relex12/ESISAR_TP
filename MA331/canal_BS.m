% canal_BS prend en argument N la taille du vecteur, f la probabilité 
% d'erreur du canal et entree le mot à faire passer dans le canal
% elle renvoit le vecteur de taille N en sortie de canal

function [vecteur] = canal_BS (N, f, entree)
  vecteur = [];
  for i = 1 : N
    vecteur (i) = entree(i);
    if (rand(1) < f)
        vecteur (i) = mod (vecteur (i) + 1, 2) ;
    endif
  endfor
endfunction  
