/*  Generate a prime number on exactly b bits */
gen_prime(b)=
{
    local(p);    \\ local variables
    \\ First generate a number on exactly b bits
    p = 2^(b-1)+random(2^(b-1));
    \\ Return next prime number greater than p
        while(!isprime(p), p = nextprime(p+1));
    return(p);
}

/*  Generate a RSA prime number on exactly b bits */
gen_RSA_prime(b)=
{
    local(p);
    p = gen_prime(b);
    while( isprime((p-1)/2) && isprime( (((p-1)/2)-1)/2 ) ,  p=gen_prime(b));
    return(p);
}

number_of_primes(m)={
    local (r);
    if (m<2, return (0));
    r = 1;     \\ on inclut 2 dans les nombres premiers
    for (i=1,m,if(isprime(i)==1, r+=1;);i+=1);
    print(m/log(m));
    return (r);
}

/*  Generate a RSA prime number on exactly b bits */
gen_RSA_modulus(b)= {
	local(N,phi);
	\\ TODO
	return([N,phi]);
}

/*  Generate a pair of RSA exponents given phi(N) */
gen_RSA_exponents(phi)= {
	local(e,d);
	\\ TODO
	return([e,d]);
}

/*  Generate a set of RSA parameters  */
gen_RSA_parameters(b)=
{
		local(N,e,d,p,q,tmp,reste,u);
		p = gen_RSA_prime(b);
		q = gen_RSA_prime(b);
		N = p*q;
		tmp = (p-1)*(q-1);     \\    =eulerphi(N)

		e=3;    \\    car e est entre 3 et N-1 et e coprime de eulerphi(N)
		while(gcd(e,tmp)!= 1, e=e+1);

		\\ on sait que e*d = 1 modulo eulerphi(N)
		[reste,u,d] = algoeuclide(tmp,e);

		return([N,e,d%tmp]); \\   d%tmp pour être sûr qu'il soit positif
}

algoeuclide(a,b)=
{
        local(d,u,v);
        if(b==0, return([a,1,0]));
        [d,u,v] = algoeuclide(b,a%b);
        return([d,v,u-(a\b)*v]);
}


/*  Encrypt a message M using a public key [N, e] */
RSA_encrypt(M,N,e)= {
	return (lift(Mod(M, N)^e));
}

/*  Decrypt a message C using a public key [N, d] */
RSA_decrypt(C,N,d)= {
  return (lift(Mod(C, N)^d));
}

/*  Test for RSA_encrypt and RSA_decrypt  */
RSA_ed_test ()= {
  local(N, e, d, M, C);
  [N, e, d] = gen_RSA_parameters(512);
  M = 1 + random(100);
  C = RSA_encrypt(M,N,e);
  return ([M, C, RSA_decrypt(C,N,d)]);
}


/*	Sign a message M using a private key [N, d mod p−1, d mod q−1, p, q] */
RSA_sign_CRT(M,N,d_p,d_q,p,q)=
{
    local(s, s_p, s_q);
    \\ On chiffre la signature avec d_p et d_q
    s_p = Mod(M, p)^lift(d_p);
    s_q = Mod(M, q)^lift(d_q);
    \\ On applique le CRT aux résultats obtenus
    return(lift(chinese(s_q, s_p)));
}


call_RSA_sign()={
    local(S,M,N,dp,dq,p,q);
    [N,dp,dq,p,q] = gen_RSA_parameters(512);
    M = 1 + random(100);
    S = RSA_sign_CRT(M,N,dp,dq,p,q);
}


/*
gen_RSA_parameters(b)={
    local(N,e,d,p,q,tmp,reste,u);
    p = gen_RSA_prime(b);
    q = gen_RSA_prime(b);
    N = p*q;
    tmp = (p-1)*(q-1);     \\    =eulerphi(N)

    e=3; \\ car e est compris entre 3 et N-1 et e coprime de eulerphi(N)
    while(gcd(e,tmp)!= 1, e=e+1);

    \\on sait que e*d = 1 modulo eulerphi(N)
    [reste,u,d] = algoeuclide(tmp,e);
    d = d%tmp;
    return([N,Mod(d,q-1),Mod(d,p-1),q,p]);
}
*/



/*	Compute p and q from N and Phi	*/
factor_from_phi(N,phi)={
    local(b,delta);
    b = -(N + 1 - phi);
    delta = b*b-4*N;
    if(delta==0,return([-b/2, -b/2]));
    return([(-b-sqrtint(delta))/2, (-b+sqrtint(delta))/2]);
}

factor_from_d(N,e,d)={
    local(k,t,g,x,y,g1,tmp);
    k = e*d - 1;\\ on initialise k = d*e-1
    tmp=3;\\on sait que tmp est compris entre 3 et N-1
    while(gcd(tmp,N)!= 1, tmp=tmp+1);
    for(g1=1,N-1,
        g = g1;
        if(g1==1,g=tmp);\\dans nos tests, g=3 marchera souvent
        t = k;
        \\Si t est divisible par 2, on a t=t/2 et x=g^t.
        \\Sinon on continue la boucle for
        while(t%2==0,
            t = t/2;
            x = lift(Mod(g, N)^t);
            \\On regarde si on a trouvé p et q avec nos conditions
            if(x > 1,
                y = gcd(x-1,N);
                if(y > 1,
                    return([y,N/y]);
                );
            );
        );
    );
}


/*	Process the broacast attack using CTR 	*/
broacast_attack(M1,N1,M2,N2,M3,N3)={
\\ on cherche à construire c tel que c = M3 % Na, c = M3 % Nb et c = M3 % Nc
\\ pour cela on utilse le CTR
\\ ensuite comme 0 < c, M^3 < Na.Nb.Nc, alors cubicroot(c) = M
    local(tmp,r);
    tmp = chinese(M1,M2);
    r =chinese(tmp,M3);	\\	<=>r = M^3 modulo N1*N2*N3
    return(lift(r)^(1/3));
}


/*	Process the Weiner attack 	*/
wiener_attack(N,e)={
    local(liste_num,matr_ratio,len,i,k,d,maxorder);

    \\Développement en fraction continu de e/N
    liste_num = contfrac(e/N,10);
    len = length(liste_num);

    \\Les convergents de k/d =
    matr_ratio = contfracpnqn(liste_num,len);

   \\Valeur maximale de d
    maxorder = 1/3*N^(1/4);
    i=2;
    [d,k] = [matr_ratio[2,i],matr_ratio[1,i]];
    \\On va regarder pour chaque valeur de k si on peut retrouver d
    while(i <= len  &&  type((e*d-1)/k) != "t_INT"  &&  (e*d-1)/k != N,
        i = i + 1;
        if(matr_ratio[2,i] < maxorder,
            [d,k] = [matr_ratio[2,i],matr_ratio[1,i]];,
        );
    );

    return(d);
}
