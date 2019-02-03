% BER entre 0 et 0.1

f = 0.005 : 0.005 : 0.1;
N = 500;
vectBER = zeros (1, 20);
for n = 1 : 20
  vectBER(n) = BER (f(n), N);
endfor

figure; 
plot(f,vectBER); hold on;
plot(f,f, '-r'); hold off;
title("BER en fonction de f");



% WER entre 0 et 0.1

f = 0.005 : 0.005 : 0.1;
N = 500;
vectWER = zeros (1, 20);
for n = 1 : 20
  vectWER(n) = WER (f(n), N);
endfor

figure; 
plot(f,vectWER); hold on;
plot(f,f, '-r'); hold off;
title("WER en fonction de f");






% BER entre 0 et 0.5

f = 0.005 : 0.005 : 0.5;
N = 500;
vectBER = zeros (1, 100);
for n = 1 : 100
  vectBER(n) = BER (f(n), N);
endfor

figure; 
plot(f,vectBER); hold on;
plot(f,f, '-r'); hold off;
title("BER en fonction de f");



% WER entre 0 et 0.5

f = 0.005 : 0.005 : 0.5;
N = 500;
vectWER = zeros (1, 100);
for n = 1 : 100
  vectWER(n) = WER (f(n), N);
endfor

figure; 
plot(f,vectWER); hold on;
plot(f,f, '-r'); hold off;
title("WER en fonction de f");



