% BER prend en argument f la probabilité d'erreur du canal 
% et N le nombre de de mot à faire passer dans le canal
% elle renvoit le BER estimé du canal 

% il faut f < 0.0.5, sinon le code rajoute des erreurs, 
% et N < 10000 sinon le temps de calcul est très long

function [resultat] = BER (f, N)
  nombre = 0;
  entree = zeros (1, 4);
  for i = 1 : N
    vecteur = chaine (entree, f);
    for j = 1 : 4
      if (vecteur(j) != entree(j))
        nombre = nombre + 1;
      endif
    endfor
  endfor
  resultat = (nombre / N / 4);
endfunction