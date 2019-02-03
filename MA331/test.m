%% Rendement hamming

f = 0.1;

figure;
pb = logspace(10e-9, 10e-2, 1000)-1; % pour obtenir une echelle log
for i = 1:1000 % on remplit tous les rendements avec la formule
  R(i) = (1-Hbin(f)) / (1-Hbin(pb(i)));
end
%figure;
semilogy(R, pb); % plot pour les log
xlim([0 1]); % pour que x soit dans 0;1 sinon ça déborde
hold on;
plot (4/7, BER(0.05, 10000), 'r*', 'linewidth', 8);
hold off;
title("Performance du code de Hamming (7, 4) avec f = 0,05 avec limite de Shannon");
