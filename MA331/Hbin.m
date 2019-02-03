function [y] = Hbin(x)
  y = x*log2(1/x) + (1-x)*log2(1/(1-x));
end