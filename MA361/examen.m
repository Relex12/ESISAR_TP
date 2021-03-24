%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%                       EXAMEN DE TP MA 361
%  Duree : 1h30
%  Sans documents, sans calculatrice, sans acces internet
%
% Nom :
%
% Prenom : 
%
% Consignes :
%       - le script matlab ou octave doit etre enregistre sous le format : Nom.m
%       - repondre directement dans le script avec des commentaires
%       - Commenter chaque ligne de votre script exemple :
%             a = 10 ; % a : frequence du signal x(t)
%       - affichage : les courbes doivent etre lisibles avec une legende si
%       plusieurs courbes sur un meme graphique
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Fonction utiles (utilisez l'aide pour en savoir plus):
%
% find(A==ii) : trouver l'indice d'un element ii dans un vecteur A
% plot : affichage 2D
% zeros : vecteur de 0
% ones : vecteur de 1
% max : maximum d'un vecteur
% log : logarithme neperien (ln)
% log10 : ln base 10
% sum : somme
% spectrogram (Matlab) / specgram (Octave) : calcul et affiche le sprectrogramme
% blackman : fenetre de ponderation de blackman
% rectwin : fenetre de ponderation rectangle
% hamming : fenetre de ponderation de hamming
% sinc : sinus cardinal
% filter : applique le filter a un signal
% selection d'une partie d'un vecteur : a(ii:jj)
%
% exemple de figure avec subplot:
% figure(ii)
% subplot(2,1,1)
% plot(A,B,'-b','linewidth',3)
% xlabel('frequence (Hz)','fontsize',14)
% ylabel('Y(f)','fontsize',14)
% set(gca,'fontsize',14)
% subplot(2,1,2)
% plot(A,C,'-r','linewidth',3)
% xlabel('frequence (Hz)','fontsize',14)
% ylabel('Z(f)','fontsize',14)
% set(gca,'fontsize',14)
% set(gcf,'color','white')

%%
clear all,
close all;
clc;
pkg load signal;        % ajout du paquet
%
%% Etude d'un signal

% 1. Creez et affichez un signal z(t) representant une cosinusoide
% de frequence 10 kHz  de duree 1 millisecondes. Vous prendrez une
% frequence d'echantillonnage de 10 fois la limite de Shannon


Fe = 200000;        % 200 kHz
Te = 1/Fe;

t = Te : Te : 1e-3;    % vecteur temps


F = 10000;          % 10 kHz
zt = cos(2*pi*F*t);       % signal z(t)

%figure; plot (t, zt);    % affichage du signal si décommenté


% 2. calculez l'energie du signal z(t)

E = 0;
for i = 1 : 200
  E = E + zt(i)*zt(i);
endfor
E     % E = 100 (J)

% 3. calculez la puissance du signal z(t)

P = 0;
for i = 1 : 1/F
  P = P + zt(i)*zt(i);
endfor
P     % P = 0 (W)     cela était prévisible car le signal est périodique, donc de puissance nulle

% 4. a. tracez le module du spectre de z(t) sur 1000 points grace a la
% technique de prolongement par des zeros.

N = 1000;

f = 0 : Fe/(N-1): Fe;       % vecteur fréquentiel de N = 1000 points

Zf = fft (zt, N);

figure; hold on;
plot(f, abs(Zf));
title ("Spectre de z(t) par la méthode du prolongement par des zéros");

%    b. Quel est l'interet de cette technique?

%--------------------------------- REPONSE --------------------------------------------
% Le prolongement par l'ajout de zeros permet d'augmenter la résolution du spectre


%   c. la frequence du signal obtenue grace au spectre est-elle correcte?

%--------------------------------- REPONSE --------------------------------------------
% On observe un pic de fréquence à 10 kHz, soit la fréquence du signal attendue
% ainsi que un autre pic à 190 kHz, du à l'échantillonnage, soit Fe - F

%% modulation d'amplitude

%5. Nous allons a present moduler le signal z(t) par un signal cosinusoidal
% p(t) de frequence 25 kHz.
% le signal module est egal a : m(t) = p(t) x z(t) avec x la multiplication
% tracer le signal m(t)

F2 = 25000;         % 25 kHz;
pt = cos(2*pi*F2*t);        % signal p(t)

for i = 1 : 200
  mt(i) = pt(i)*zt(i);      % signal m(t)
endfor

figure;
plot (t, mt);
title ("Signal m(t), soit z(t) modulé par p(t)");

%6. a. tracez le module du spectre de m(t) sur 1000 points en utilisant un
%prolongement par des zeros


Mf = fft (mt, N);

figure; hold on;
plot(f, abs(Mf));
title ("Spectre de m(t) par la méthode du prolongement par des zéros");



% b. Justifiez les frequences contenues dans le spectre.

%--------------------------------- REPONSE --------------------------------------------
% Nous observons 4 pics de fréquence dans le spectre :
% 15 kHz la fréquence (négative) de m(t) - 10 kHz décalé vers la droite de 25 kHz par la multiplication par p(t)
% 35 kHz la fréquence (positive) de m(t) 10 kHz décalé vers la droite de 25 kHz par la multiplication par p(t)
% 165 kHz, du à l'échantillonnage et à la fréquence de 35 kHz :  Fe - 35 kHz
% 185 kHz, du à l'échantillonnage et à la fréquence de 15 kHz :  Fe - 15 kHz


%7. Nous allons a present demoduler le signal m(t). Pour cela il faut
%d'abord multiplier le signal m(t) par la porteuse p(t). Nous appelerons ce
%signal zm(t).

% a. tracez le spectre de zm(t).

for i = 1 : 200
  zmt(i) = mt(i)*pt(i);      % signal zm(t)
endfor

ZMf = fft (zmt, N);

figure; hold on;
plot(f, abs(ZMf));
title ("Spectre de zm(t), soit z(t) démodulé");


% b. Quelle operation est necessaire pour obtenir z(t)?

%--------------------------------- REPONSE --------------------------------------------
% Pour passer de zm(t) démodulé au signal original z(t), il va falloir appliquer
% un filtre passe-bas à z(t), filtre de fréquence de coupure Fc = 15 kHz
% pour ne pas avoir les autres pics de fréquence du spectre de zm(t)


%% filtre passe-bas

% 8. En utilisant la methode de la fenetre (decrite dans le cours),
% determinez theoriquement la reponse impulsionnelle h(n) d'un filtre
% RIF passe-bas ideal de frequence de coupure 15kHz. Le nombre de coefficients est fixe a 51
% La frequence d'echantillonnage est celle de la question 1. La fenetre de ponderation est un fenetre rectangle.


%--------------------------------- REPONSE --------------------------------------------
%H(f) = rect (f/ 2Fc)
%h(t) = 2*Fc*sinc(2*pi*Fc*t)            attention, sur octave pi est déjà compris dans le calcul du sinc
%h(n) = 2*Fc*sinc(2*pi*Fc*n/Fe)
%hC(n) = 2*Fc*sinc(2*pi*Fc*(n-25)/Fe)   hC(n) est donc le filtre h(n) mais causal


% Affichez la reponse impulsionnelle en fonction du temps puis le module en dB et
% la phase de la fonction de transfert en fonction de la frequence.


Fc = 15000;       % 15 kHz
nb = 51;

n = 0 : nb-1;

hCn = 2*Fc*sinc(2*Fc*(n-25)/Fe);   % hC(n) est donc le filtre h(n) mais causal

figure;
plot (n, hCn);
title ("Réponse impulsionnelle en temps de h(t)");

%9. Appliquez le filtre au signal zm(t).

% a. Tracez le signal et le module du spectre du signal en sortie du filtre.



% b. La frequence du signal est-elle coherente avec ce que vous attendiez?




% c. Expliquez le phenomene qui apparait au debut du signal temporel entre t= 0 et t = 0.1 ms.


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Bonus %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%10. Refaite le filtre de la question 9 en utilisant une fenetre de
% hamming. Affichez le module de la fonction de transfert du filtre en
% fonction de la frequence.
