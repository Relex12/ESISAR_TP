% WER prend en argument f la probabilité d'erreur du canal 
% et N le nombre de de mot à faire passer dans le canal
% elle renvoit le WER estimé du canal 

% il faut f < 0.0.5, sinon le code rajoute des erreurs, 
% et N < 1000 sinon le temps de calcul est très long

function [resultat] = WER (f, N)
  nombre = 0;
  entree = zeros (1, 4);
    for i = 1 : N
    vecteur = chaine (entree, f);
    if (!isequal(vecteur, entree))
      nombre = nombre + 1;
    endif
  endfor
  resultat = (nombre / N);
endfunction