% enc_Hamming74 est la fonction d'encodage de Hamming (7, 4)

% elle prend en argument entree le vecteur de taille 4
% que l'on souhaite encoder
% elle renvoit le message encodé de taille 7

function [sortie] = enc_Hamming74 (entree) 
  M =  [1 0 0 0 0 1 1 ; 
        0 1 0 0 1 0 1 ; 
        0 0 1 0 1 1 0 ; 
        0 0 0 1 1 1 1 ];
  sortie = mod(entree*M, 2);
endfunction