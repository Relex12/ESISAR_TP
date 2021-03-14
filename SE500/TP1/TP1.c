#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "tables.h"
#include "rdtsc.h"
#include "aes.h"

/* Representation of the field GF2[X]/(x^8+x^4+x^3+x+1) */
const uint8_t field = 0x1B;

static inline uint8_t GF256_add (uint8_t a, uint8_t b) {
	/* TODO Field addition of a and b*/
 	return (a^b);
}

static inline uint8_t GF256_mulx (uint8_t a) {
	/* TODO Multiply a field element by x */
	// si le MSB de a est à 1, on renvoie a<<1 modulo x, sinon on renvoie a<<1
	return ( (a >> 7) == 1 ?  a << 1 ^ field : a << 1);
}

static inline uint8_t GF256_mul (uint8_t a, uint8_t b) {
	/* TODO Multiply field elements a and b */
	uint8_t tmp = a; /* Will compute a*x^i */
  uint8_t res = 0;
	// tant qu'il reste au moins un bit à 1 dans b
	while (b) {
			// si le bit qu'on regarde est à 1, alors on ajoute tmp au résultat
      if(b&1)		res = GF256_add(res, tmp);
			// on augmente la puissance de tmp
      tmp = GF256_mulx(tmp);
			// on regarde le bit suivant dans b (suivant à gauche, décalage à droite)
			b = b >>1;
  }
  return res ;
}

static inline uint8_t GF256_pow (uint8_t a, uint8_t i) {
	/* TODO Compute a^i */
 	uint8_t res = 1;
  // on multiplie i fois a par lui-même
	for(;i > 0; i--)	    res = GF256_mul(res,a);
	return res;
}

static uint8_t log_table[256];
static uint8_t pow_table[256];

static uint8_t GF256_mul_table(uint8_t a, uint8_t b) {
	/* TODO Multiply field elements a and b using log and pow tables */
	// si a ou b = 0, on renvoie 0 (valeur arbitraire)
	// sinon on renvoie le contenu dans la table d'exposants, à l'indice du
	// contenu de la table de log indice a + contenu de la table de log indice a,
	// modulo 255 pour ne pas faire d'overflow et car on peut faire modulo
  return (a==0 || b==0) ? 0 : pow_table[ (log_table[a] + log_table[b]) % 255];
}

static uint8_t GF256_inv(uint8_t a) {
	/* TODO Return a^-1*/
  // si a = 0, on renvoie 0 (valeur arbitraire)
  // sinon on renvoi le contenu dans la table d'exposants, à l'indice 255 - le
  // contenu de la table de log à l'indice a
  return (a == 0) ? 0 : pow_table[ 255 - log_table[a]];
}

static inline uint8_t SBOX_matmul (uint8_t a) {
	/* TODO Compute multiplication of a (seen as a vector with matrix)
			1 1 1 1 1 0 0 0   a_7
			0 1 1 1 1 1 0 0   a_6
			0 0 1 1 1 1 1 0   a_5
			0 0 0 1 1 1 1 1 x a_4
			1 0 0 0 1 1 1 1   a_3
			1 1 0 0 0 1 1 1   a_2
			1 1 1 0 0 0 1 1   a_1
			1 1 1 1 0 0 0 1   a_0
	*/

  if(a==0)      return 0;
  uint8_t res;
  for(int i = 0; i < 8; i++)
  // d'après la formule suivante :
  // s_i = b_i + b_(i+4)%8 + b_(i+5)%8 + b_(i+6)%8 + b_(i+7)%8
    res = (res<<1) + (a>>(7-i)&1) ^ (a>>((7-i+4) % 8)&1) ^ (a>>((7-i+5) % 8)&1) ^ (a>>((7-i+6) % 8)&1) ^ (a>>((7-i+7) % 8)&1);
  // les décalages permettents de gérer le nombre comme un vecteur
  return res;
}

/**
 * Dummy implementation of the AES
**/
static inline void AES_Shiftrows (uint8_t *in) {
	uint8_t tmp1;
	tmp1 = in[1];
	for (int i = 0; i < 3; i++){
		in[1+4*i] = in[5+4*i];
	}
	in[13] = tmp1;
	for (int i = 0; i < 2; i++){
		tmp1       = in[2+4*i];
		in[2+4*i]  = in[10+4*i];
		in[10+4*i] = tmp1;
	}
	tmp1 = in[15];
	for (int i = 2; i >= 0; i--){
		in[7+4*i] = in[3+4*i];
	}
	in[3] = tmp1;
}

static inline void AES_Subbytes (uint8_t *in) {
	for (int i = 0; i < 16; i++){
		in[i]=SBOX[in[i]];
	}
}

static inline void AES_MixColumns (const uint8_t *in, uint8_t *out) {
	for (int i = 0; i < 4; i++){
		out[4*i]   = GF256_mul_table(in[4*i],0x02) ^ GF256_mul_table(in[4*i+1],0x03) ^ in[4*i+2] ^ in[4*i+3];
		out[4*i+1] = in[4*i] ^ GF256_mul_table(in[4*i+1],0x02) ^ GF256_mul_table(in[4*i+2],0x03) ^ in[4*i+3];
		out[4*i+2] = in[4*i] ^ in[4*i+1] ^ GF256_mul_table(in[4*i+2],0x02) ^ GF256_mul_table(in[4*i+3],0x03);
		out[4*i+3] = GF256_mul_table(in[4*i],0x03) ^ in[4*i+1] ^ in[4*i+2] ^ GF256_mul_table(in[4*i+3],0x02);
	}
}

static inline void AES_AddRoundkey (uint8_t *in, const uint8_t *key) {
	((uint64_t *)in)[0] ^= ((uint64_t *)key)[0];
	((uint64_t *)in)[1] ^= ((uint64_t *)key)[1];
}

static inline void AES_Round(uint8_t *in, const uint8_t *key, uint8_t *out) {
	uint8_t tmp[16];
	memcpy(tmp,in,16*sizeof(uint8_t));
	AES_Shiftrows(tmp);
	AES_Subbytes(tmp);
	AES_MixColumns(tmp,out);
	AES_AddRoundkey(out,key);
}

int main () {
	int ret;
	printf("Checking field addition: %s\n",(
		GF256_add(0x75,0xBA)==0xCF
		? "PASS":"FAILED"));
	printf("Checking multiplication by x: %s\n",(
		((GF256_mulx(0x75)==0xEA) && (GF256_mulx(0xEA)==0xCF))
		? "PASS":"FAILED"));
	printf("Checking field multiplication: ");
	ret = 0;
	for (int i = 0; i < 256; i++){
		for (int j = 0; j < 256; j++){
			if (GF256_mul(i,j) != GF256_table[i][j]){
				ret = -1;
				break;
			}
		}
		if (ret) break;
	}
	printf("%s\n",(ret ? "FAILED":"PASS"));
	printf("Checking power: ");
	uint8_t a = 1;
	ret = 0;
	/* TODO Find suitable value for g */
	uint8_t g = 0x03;  	// avec g = 0x03, la log table contient uniquement deux 0
	for (int i = 0; i < 256; i++){
		if (GF256_pow(g,i) != a){
			ret = -1;
			break;
		}
		log_table[a]=(i % 255);
		pow_table[i]=a;
		a = GF256_mul(a,g);
	}
	printf("%s\n",(ret ? "FAILED":"PASS"));
	printf("Log table:\n");
	for (int i = 0; i < 256; i++){
		printf("%02x ",log_table[i]);
		if (i % 16 == 15) printf("\n");
	}
	printf("Checking field multiplication using tables: ");
	ret = 0;
	for (int i = 0; i < 256; i++){
		for (int j = 0; j < 256; j++){
			if (GF256_mul_table(i,j) != GF256_table[i][j]){
				ret = -1;
				break;
			}
		}
		if (ret) break;
	}
	printf("%s\n",(ret ? "FAILED":"PASS"));
	printf("Checking field inversion using tables: ");
	ret = 0;
	for (int i = 1; i < 256; i++){
		if (GF256_mul(i,GF256_inv(i)) != 0x01){
			ret = -1;
			break;
		}
	}
	printf("%s\n",(ret ? "FAILED":"PASS"));

	printf("Checking SBOX computation: ");
	for (int i = 1; i < 256; i++){       // changing start point from 0 to 1
		if (GF256_add(SBOX_matmul(GF256_inv(i)),0x63)!= SBOX[i]){
			ret = -1;
			break;
		}
	}
	printf("%s\n",(ret ? "FAILED":"PASS"));
	if (ret) return -1;

	printf ("Performances: \n");
	int reps = 100000000;
	printf("Using multiplication table:     ");
	unsigned long long start = read_tsc();
	uint8_t x = 0xab;
	uint8_t y = 0xcd;
	uint8_t res = 0;
	for (int k = 0; k < reps; k++){
		if (k % 2) x = GF256_table[x][y];
		else y = GF256_table[x][y];
	}
	printf("%llu cycles per computation\n", (read_tsc()-start)/reps);

	printf("Using dummy multiplication:     ");
	start = read_tsc();
	x = 0xab;
	y = 0xcd;
	res = 0;
	for (int k = 0; k < reps; k++){
		if (k % 2) x = GF256_mul(x,y);
		else y = GF256_mul(x,y);
	}
	printf("%llu cycles per computation\n", (read_tsc()-start)/reps);

	printf("Using log table multiplication: ");
	start = read_tsc();
	x = 0xab;
	y = 0xcd;
	res = 0;
	for (int k = 0; k < reps; k++){
		if (k % 2) x = GF256_mul_table(x,y);
		else y = GF256_mul_table(x,y);
	}
	printf("%llu cycles per computation\n", (read_tsc()-start)/reps);

	printf("AES Round performance:          ");
	unsigned char in [16] = "0123456789abcdef";
	unsigned char key[16] = "deadbeefdeadbeef";
	unsigned char out[16];
	start = read_tsc();
	for (int k = 0; k < reps/10; k++){
		in[0]=k;
		key[0]=k+1;
		AES_Round((uint8_t *)in,(uint8_t*)key,(uint8_t *)out);
	}
	printf("%llu cycles per computation\n", (read_tsc()-start)/reps*10);

	if (Check_CPU_support_AES()){
		printf("Using AES builtin function:     ");
		start = read_tsc();
		for (int k = 0; k < reps; k++){
			in[0]=k;
			key[0]=k+1;
			AES_ECB_encrypt(in,out,key);
		}
		printf("%llu cycles per computation\n", (read_tsc()-start)/reps);
	}

	return 0;
}
