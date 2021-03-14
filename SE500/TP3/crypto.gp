md5(n="")=extern(Str("var=`echo -n '"n"' |md5sum|tr -d '-'`; echo \"0x$var\" "));
sha1(n="")=extern(Str("var=`echo -n '"n"' |sha1sum|tr -d '-'`; echo \"0x$var\" "));
sha224(n="")=extern(Str("var=`echo -n '"n"' |sha224sum|tr -d '-'`; echo \"0x$var\" "));
sha256(n="")=extern(Str("var=`echo -n '"n"' |sha256sum|tr -d '-'`; echo \"0x$var\" "));
sha384(n="")=extern(Str("var=`echo -n '"n"' |sha384sum|tr -d '-'`; echo \"0x$var\" "));
sha512(n="")=extern(Str("var=`echo -n '"n"' |sha512sum|tr -d '-'`; echo \"0x$var\" "));

/************************** RSA OAEP **************************/

RSA_OAEP_enc(m,N,e)= {
    local(n,k,r,X,Y,M);
    n = 768;
    k = 256;
    r = 2^(k-1)+random(2^(k-1));
    if(m<=0,return(0));
    if(round((log(m)/log(2)))>=n,return(0));
    X = bitxor(m,sha224(r));
    Y = bitxor(sha256(X),r);
    M = X*2^256+Y;
    return(lift(Mod(M,N)^e));
}

RSA_OAEP_dec(c,N,d)= {
    local(M,Y,X,r,m);
    M = lift(Mod(c,N)^d);
    X = M>>256;
    Y = M - X*2^256;
    r = bitxor(sha256(X),Y);
    m = bitxor(X,sha224(r));
    return(m);
}

do_RSA_OAEP()={
	local(N,e,d,c,m);
	[N,e,d] = gen_RSA_parameters(512);
	m = 2^(512-1)+random(2^(512-1));
	print (m);
	c = RSA_OAEP_enc(m,N,e);
	print(c);
	print(RSA_OAEP_dec(c,N,d))
}

/************************** RSA PSS **************************/

RSA_PSS_sign(m,N,d)={
	local(k,l,n,G,G1,G2,a,s);
	k = 256;
	l = 256;
	r = 2^(k-1)+random(2^(k-1));
	n = 640;
	x = sha256(M*2^k+r);
	\\H=SHA256=l and G=SHA384=n-l
	G = sha384(x);
	G1 = G>>(n-(l+k));
	G2 = G - G1*2^(n-(l+k));
	a = x*2^n + bitxor(G1,r)*2^(n-(l+k)) + G2;
	s = RSA_decrypt(a,N,d);
	return(s);
}

RSA_PSS_sign(m, N, d)={
    local(k, l, r, n, x, G, G1, G2, temp, s);
    k = 256;
    l = 256;
    r = 2^(k - 1) + random( 2^(k - 1));
    n = 640;
    if(ceil((log(m)/log(2)))!=n,return("longueur du message incorrecte"));
    x = sha256(m * 2^k + r);
    \\H=SHA256=l and G=SHA384=n-l;
    G = sha384(x);
    G1 = G >> (n - (l + k));
    G2 = G - G1 * 2^(n - (l + k));
    temp = x * 2^n + bitxor(G1, r) * 2^(n - (l + k)) + G2;
    s = RSA_decrypt(temp, N, d);
    return(s);
}

RSA_PSS_verify(m, s, N, e)={
    local(temp1, k, l, r, n, xtemp, Gtemp, G1temp, x, G, G1, G2, temp2);
    temp1 = RSA_encrypt(s, N, e);
    if(ceil((log(temp1)/log(2))) != n, return("longueur de signature incorrecte"));
    k = 256;
    l = 256;
    n = 640;
    xtemp = temp1 >> n;
    Gtemp = sha384(xtemp);
    G1temp = Gtemp >> (n - (l + k) );
    r = bitxor(G1temp, ( (temp1 - xtemp * 2 ^ n) >> (n - (l + k) ) ) );
    x = sha256(m * 2^k + r);
    \\H=SHA256=l and G=SHA384=n-l;
    G = sha384(x);
    G1 = G >> (n - (l + k));
    G2 = G - G1 * 2^(n - (l + k));
    temp2 = x * 2^n + bitxor(G1, r) * 2^(n - (l + k)) + G2;
    if(temp1 != temp2, return("vérification incorrecte"), return("vérification ok"));
}

do_RSA_PSS()={
	local(N,e,d,s,m);
	[N,e,d] = gen_RSA_parameters(512);
  b = 640;
  m = 2^(b-1) + random(2^(b-1));
	print (m);
	s = RSA_PSS_sign(m,N,d);
	print(s);
	print(RSA_PSS_verify(m,s,N,e));
}

/************************** DLP solving difficulty **************************/

plot_rand_behavior()={
  local(g, x, p);
  p = gen_prime(768);
  g = Mod( random(p), p);
  ploth(x=0, 200, [x, lift(g^round(x))]);
}

find_x_DLP(b)={
  local(g, x, p, r, t1, t2);
  p = gen_prime(b);
  g = Mod( random(p), p);
  x = random(200);
  t1 = getwalltime();
  print (znlog(x, g));
  t2 = getwalltime();
  print ("Time:", t2-t1);
}

gen_DLP_parameters(g,p) = {
    local(kpriv, kpublic);
    kpriv = 1 + random(p - 1);
    kpublic = g ^ kpriv;
    return([kpublic, kpriv]);
}

/************************** ElGamal **************************/

ElGamal_enc(g, p, pub, M)={
    local(r, Kr, C);
    r = 1 + random(p - 1);
    Kr = g ^ r;
    C = M * pub^r;
    return([Kr, C]);
}

ElGamal_dec(g, p, priv, K, C) = {
    local(M);
    \\ C = M * (g ^ priv)^r = M * (g ^ r)^priv = M * K^priv
    M = C / (K ^ priv);
    return(M);
}

test_ElGamal(b1, b2)={
  local(p, g, pub, priv, Kr, M, C);
  p = gen_prime(b1);
  g = random(2^b2);
  [pub, priv] = gen_DLP_parameters(g, p);
  M = random(2^512);
  print (M);
  [Kr, C] = ElGamal_enc(g, p, pub, M);
  print (ElGamal_dec(g, p, priv, Kr, C));
}

/************************** DSS **************************/

DSS_sign(g,p,priv,M)={
    local(r, q, a, ga, kr, km, temp1, rinv, temp2);

    \\p and q large primes (log2(p) = 3072)
    if(log(p) / log(2) != 3072, return("log2(p) != 3072"));

    \\Draws a random r ∈ Z/qZx
    r = random(q);

    \\p = aq + 1 with log2(q) = 256
    q = 2 ^ 256 + 1;
    while((p - 1) / q != round((p - 1) / q), q = nextprime(q + 1));
    a = (p - 1) / q;

    \\ga = g^a (of order q)
    ga = g ^ a;

    \\ computes kr = ((ga)r mod p) mod q
    kr = lift( Mod( lift( Mod(ga, p) ^ r), q));

    \\ Compute km = (skr + H(M))r^(−1) mod q   , on calcule r^(-1) mod q= rinv
    [temp1, rinv, temp2] = algoeuclide(r, q);
    if(rinv < 0, rinv = rinv + q);
    km = lift(Mod((priv * kr + sha256(M)) * rinv, q));

    return([M, kr, km]);
}

DSS_verify(g, p, pub, M, Kr, Km)={
    local(q, a, ga, priv, temp1, kminv, temp2, r, kr2);

    \\p and q large primes (log2(p) = 3072)
    if(log(p) / log(2) != 3072, return("log2(p) != 3072"));

    \\p = aq + 1 with log2(q) = 256
    q = 2 ^ 256 + 1;
    while((p - 1) / q != round((p - 1) / q), q = nextprime(q + 1));
    a = (p - 1) / q;

    \\ga = g^a (of order q)
    ga = g ^ a;

    \\ pub = ga ^ priv
    priv = log(pub) / log(ga);

    \\kminv * ( s * kr + H(M)) * r^(-1) = 1 mod q
    \\ donc r = kminv * (s * kr + H(M)) mod q
    [temp1, kminv, temp2] = algoeuclide(r, q);
    if(kminv < 0, kminv = kminv + q);
    r = lift(Mod(kminv * (priv * kr + H(M)), q));

    \\on vérifie qu'on retombe bien sur le même kr quand on le calcule
    \\ computes kr = ((ga)r mod p) mod q
    kr2 = lift( Mod( lift( Mod(ga, p) ^ r), q));

    return(kr==kr2);
}

test_DSS(b1, b2)={
  local(p, g, pub, priv, Kr, KM, M);
  p = gen_prime(b1);
  g = random(2^b2);
  [pub, priv] = gen_DLP_parameters(g, p);
  M = random(2^512);
  [M, Kr, Km] = DSS_sign(g, p, priv, M);
  print (DSS_verify(g, p, pub, M, Kr, Km));
}


/************************** fonctions du TP2 **************************/

RSA_encrypt(M,N,e)= {
return (lift(Mod(M, N)^e));
}

RSA_decrypt(C,N,d)= {
return (lift(Mod(C, N)^d));
}

gen_prime(b)={
    local(p);    \\ local variables
    p = 2^(b-1)+random(2^(b-1));
    while(!isprime(p), p = nextprime(p+1));
    return(p);
}

gen_RSA_prime(b)={
    local(p);
    p = gen_prime(b);
    while( isprime((p-1)/2) && isprime( (((p-1)/2)-1)/2 ) ,  p=gen_prime(b));
    return(p);
}

algoeuclide(a,b)={
    local(d,u,v);
    if(b==0, return([a,1,0]));
    [d,u,v] = algoeuclide(b,a%b);
    return([d,v,u-(a\b)*v]);
}

gen_RSA_parameters(b)={
		local(N,e,d,p,q,tmp,reste,u);
		p = gen_RSA_prime(b);
		q = gen_RSA_prime(b);
		N = p*q;
		tmp = (p-1)*(q-1);
		e=3;
		while(gcd(e,tmp)!= 1, e=e+1);
		[reste,u,d] = algoeuclide(tmp,e);
		return([N,e,d%tmp]);
}
