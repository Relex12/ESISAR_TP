% dec_Hamming74 est la fonction de décodage de Hamming (7, 4)

% elle prend en argument entree le vecteur de taille 7
% que l'on souhaite décoder
% elle renvoit le message décodé de taille 4

function [sortie] = dec_Hamming74 (entree)
  sortie = [entree(1) entree(2) entree(3) entree(4)];
endfunction