\\[p,E]=gen_courbe_ecc()
gen_courbe_ecc()={
      local(p,E);
\\      p = randomprime(2^100);
      p = randomprime(2^30);
      E = ellinit([2,3],p);
      return([p,E]);
}

\\[P, check1, check2]= point_and_check(E)
point_and_check(E)={
    local(P, x, y, check1, check2);
    P = random(E);
    [x, y] = P;
    check1 = ellisoncurve(E,P);
    check2 = y^2 == x ^ 3 + 2 * x + 3;
    return([P, check1, check2]);
}


roh_pollard_ECC(E,G,P)={
    local(R, S);
    n = ellcard(E);
    R = f([P,1,0],P,G,E);
    S = f(f([P,1,0],P,G,E),P,G,E);
    while(R[1]!=S[1],
        R = f(R,P,G,E);
        S = f(f(S,P,G,E),P,G,E)
    );

\\ TODO changer le % et mettre un lift(Mod(   ))
    return((S[3]-R[3])/(R[2]-S[2]) % (n/gcd(n,S[3]-R[3])));
\\    return((S[3]-R[3])/(R[2]-S[2]) % n);

}

/* f(Q) = Q+P   if   x mod 3 = 0
          2Q    if   x mod 3 = 1
          Q+G   if   x mod 3 = 2 */

f(Q,P,G,E)={
    mod = lift(Q[1][1]) % 3;
    if(mod == 0, return([elladd(E,Q[1],P), Q[2]+1, Q[3]]));
    if(mod == 1, return([ellmul(E,Q[1],2), Q[2]*2, Q[3]*2]));
    if(mod == 2, return([elladd(E,Q[1],G), Q[2], Q[3]+1]));
}

test_roh_pollard()={
    local(p,E,G,P,a);
    [p,E] = gen_courbe_ecc();
    G = random(E);
    /*
    a = random(10);
    P = ellmul(E,G,a);
    print (a);
    return (roh_pollard_ECC(E,G,P));

    */
for(a=0,100,
  P = ellmul(E,G,a);
  print (roh_pollard_ECC(E,G,P) == a, " ",a);
);
}


complexity()={
    local(R, S, boucle);
    local(p,E,G,P,a);
    [p,E] = gen_courbe_ecc();
    boucle = 0;

    for(a=0,10,
        G = random(E);
        a = 2;
        P = ellmul(E,G,a);
        n = ellcard(E);
        R = f([P,1,0],P,G,E);
        S = f(f([P,1,0],P,G,E),P,G,E);
        while(R[1]!=S[1],
                R = f(R,P,G,E);
                S = f(f(S,P,G,E),P,G,E);
                boucle = boucle + 1;
        );

        print(ellorder(E, G), "      ", boucle);
/*
        print("ordreG : ");
        print(ellorder(E, G));
        print("boucle : ");
        print(boucle);
        print("rapport : ");
        print(round(ellorder(E, G) / boucle));
*/

    );
    return ((S[3]-R[3])/(R[2]-S[2])%(n/gcd(n,S[3]-R[3])));
}


hasse_theorem()={
  local(rp,p,a,b);
  p = randomprime(2^100);
  rp = 2*sqrt(p);
  for(i=0,200,
    a = random(10) + 1;
    b = random(10) + 1;
    E = ellinit([a,b],p);
    print (abs(ellcard(E)-p-1) < rp, " ",abs(ellcard(E)-p-1));
  );
}
