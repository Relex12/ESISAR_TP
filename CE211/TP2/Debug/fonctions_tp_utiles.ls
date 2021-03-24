   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.10.2 - 02 Nov 2011
   3                     ; Generator (Limited) V4.3.7 - 29 Nov 2011
  44                     ; 35 void init_Ports(void) // inséré le 31 aout 2017
  44                     ; 36  {
  46                     	switch	.text
  47  0000               _init_Ports:
  51                     ; 37      GPIOA->DDR = PORT_A_DIRECTION; // lignes 3 à 6 en sortie
  53  0000 35785002      	mov	20482,#120
  54                     ; 38      GPIOA->CR1 = PORT_A_TECHNO_LIGNES; // open drain
  56  0004 35785003      	mov	20483,#120
  57                     ; 39      GPIOA->ODR = 0x78;  // extinction 4 leds	rouges
  59  0008 35785000      	mov	20480,#120
  60                     ; 41      GPIOB->DDR = PORT_B_DIRECTION; // 8 lignes en sortie
  62  000c 35ff5007      	mov	20487,#255
  63                     ; 42      GPIOB->CR1 = PORT_B_TECHNO_LIGNES; // 8 lignes en push pull
  65  0010 35ff5008      	mov	20488,#255
  66                     ; 43      GPIOB->ODR = 0x0; // extinction afficheur TIL321
  68  0014 725f5005      	clr	20485
  69                     ; 45      GPIOC->DDR = PORT_C_DIRECTION; // 7 lignes en entrée
  71  0018 725f500c      	clr	20492
  72                     ; 46      GPIOC->CR1 = PORT_C_TECHNO_LIGNES; // 7 lignes en pull up 
  74  001c 35ff500d      	mov	20493,#255
  75                     ; 48      GPIOD->DDR = PORT_D_DIRECTION;  // ligne 0 en sortie pour led verte
  77  0020 35095011      	mov	20497,#9
  78                     ; 49      GPIOD->CR1 = PORT_D_TECHNO_LIGNES; // ligne 7 en pull up pour BP1 extérieur
  80  0024 35885012      	mov	20498,#136
  81                     ; 51      GPIOD->ODR = GPIO_PIN_0; // extinction led verte
  83  0028 3501500f      	mov	20495,#1
  84                     ; 53      GPIOE->DDR = PORT_E_DIRECTION;  // 2 signaux WR pour HDLX
  86  002c 35285016      	mov	20502,#40
  87                     ; 54      GPIOE->CR1 = PORT_E_TECHNO_LIGNES;  // ligne 7 en pull up pour BP2 extérieur
  89  0030 35a85017      	mov	20503,#168
  90                     ; 56      GPIOG->DDR = PORT_G_DIRECTION;  // sortie pour signaux A0 et A1
  92  0034 35035020      	mov	20512,#3
  93                     ; 57      GPIOG->CR1 = PORT_G_TECHNO_LIGNES; // push pull
  95  0038 35035021      	mov	20513,#3
  96                     ; 59      GPIOD->ODR = HDLX_NBL;  // pas Blanking
  98  003c 3508500f      	mov	20495,#8
  99                     ; 60      GPIOE->ODR = HDLX_NWR1 + HDLX_NWR2; // 2 signaux /WR au repos
 101  0040 35285014      	mov	20500,#40
 102                     ; 61  }
 105  0044 81            	ret
 139                     ; 65 u8 lire_Etat_BP2(void)
 139                     ; 66 {
 140                     	switch	.text
 141  0045               _lire_Etat_BP2:
 143  0045 88            	push	a
 144       00000001      OFST:	set	1
 147                     ; 67 	u8 valeur = NON_ACTIF;
 149  0046 a601          	ld	a,#1
 150  0048 6b01          	ld	(OFST+0,sp),a
 151                     ; 68 		if ( GPIO_PIN_7 != (GPIOE->IDR & GPIO_PIN_7 ))
 153  004a c65015        	ld	a,20501
 154  004d a480          	and	a,#128
 155  004f a180          	cp	a,#128
 156  0051 2702          	jreq	L73
 157                     ; 70 		valeur = ACTIF;
 159  0053 0f01          	clr	(OFST+0,sp)
 160  0055               L73:
 161                     ; 71 		return valeur;
 163  0055 7b01          	ld	a,(OFST+0,sp)
 166  0057 5b01          	addw	sp,#1
 167  0059 81            	ret
 201                     ; 76 u8 lire_Etat_BP1(void)
 201                     ; 77 {
 202                     	switch	.text
 203  005a               _lire_Etat_BP1:
 205  005a 88            	push	a
 206       00000001      OFST:	set	1
 209                     ; 78 	u8 valeur = NON_ACTIF;
 211  005b a601          	ld	a,#1
 212  005d 6b01          	ld	(OFST+0,sp),a
 213                     ; 79 		if ( GPIO_PIN_7 != (GPIOD->IDR & GPIO_PIN_7 ))
 215  005f c65010        	ld	a,20496
 216  0062 a480          	and	a,#128
 217  0064 a180          	cp	a,#128
 218  0066 2702          	jreq	L75
 219                     ; 81 		valeur = ACTIF;
 221  0068 0f01          	clr	(OFST+0,sp)
 222  006a               L75:
 223                     ; 82 		return valeur;
 225  006a 7b01          	ld	a,(OFST+0,sp)
 228  006c 5b01          	addw	sp,#1
 229  006e 81            	ret
 263                     ; 89 u8 afficher_TIL321(u8 valeur)
 263                     ; 90 {
 264                     	switch	.text
 265  006f               _afficher_TIL321:
 267  006f 88            	push	a
 268       00000000      OFST:	set	0
 271                     ; 91 	if( valeur < 0 || valeur > 9)
 273  0070 a10a          	cp	a,#10
 274  0072 2509          	jrult	L321
 275                     ; 93 			GPIOB->ODR = LETTRE_E;
 277  0074 359e5005      	mov	20485,#158
 278                     ; 95 			return -1;
 280  0078 a6ff          	ld	a,#255
 283  007a 5b01          	addw	sp,#1
 284  007c 81            	ret
 285  007d               L321:
 286                     ; 99 		switch (valeur)
 288  007d 7b01          	ld	a,(OFST+1,sp)
 290                     ; 130 			break;
 291  007f 4d            	tnz	a
 292  0080 271d          	jreq	L16
 293  0082 4a            	dec	a
 294  0083 2720          	jreq	L36
 295  0085 4a            	dec	a
 296  0086 2723          	jreq	L56
 297  0088 4a            	dec	a
 298  0089 2726          	jreq	L76
 299  008b 4a            	dec	a
 300  008c 2729          	jreq	L17
 301  008e 4a            	dec	a
 302  008f 272c          	jreq	L37
 303  0091 4a            	dec	a
 304  0092 272f          	jreq	L57
 305  0094 4a            	dec	a
 306  0095 2732          	jreq	L77
 307  0097 4a            	dec	a
 308  0098 2735          	jreq	L101
 309  009a 4a            	dec	a
 310  009b 2738          	jreq	L301
 311  009d 203a          	jra	L131
 312  009f               L16:
 313                     ; 101 			case 0 :
 313                     ; 102 			GPIOB->ODR = ZERO;
 315  009f 35fc5005      	mov	20485,#252
 316                     ; 103 			break;
 318  00a3 2034          	jra	L131
 319  00a5               L36:
 320                     ; 104 			case 1 :
 320                     ; 105 			GPIOB->ODR = UN;
 322  00a5 35605005      	mov	20485,#96
 323                     ; 106 			break;
 325  00a9 202e          	jra	L131
 326  00ab               L56:
 327                     ; 107 			case 2 :
 327                     ; 108 			GPIOB->ODR = DEUX;
 329  00ab 35da5005      	mov	20485,#218
 330                     ; 109 			break;
 332  00af 2028          	jra	L131
 333  00b1               L76:
 334                     ; 110 			case 3 :
 334                     ; 111 			GPIOB->ODR = TROIS;
 336  00b1 35f25005      	mov	20485,#242
 337                     ; 112 			break;
 339  00b5 2022          	jra	L131
 340  00b7               L17:
 341                     ; 113 			case 4 :
 341                     ; 114 			GPIOB->ODR = QUATRE;
 343  00b7 35665005      	mov	20485,#102
 344                     ; 115 			break;
 346  00bb 201c          	jra	L131
 347  00bd               L37:
 348                     ; 116 			case 5 :
 348                     ; 117 			GPIOB->ODR = CINQ;
 350  00bd 35b65005      	mov	20485,#182
 351                     ; 118 			break;
 353  00c1 2016          	jra	L131
 354  00c3               L57:
 355                     ; 119 			case 6 :
 355                     ; 120 			GPIOB->ODR = SIX;
 357  00c3 35be5005      	mov	20485,#190
 358                     ; 121 			break;
 360  00c7 2010          	jra	L131
 361  00c9               L77:
 362                     ; 122 			case 7 :
 362                     ; 123 			GPIOB->ODR = SEPT;
 364  00c9 35e05005      	mov	20485,#224
 365                     ; 124 			break;
 367  00cd 200a          	jra	L131
 368  00cf               L101:
 369                     ; 125 			case 8 :
 369                     ; 126 			GPIOB->ODR = HUIT;
 371  00cf 35fe5005      	mov	20485,#254
 372                     ; 127 			break;
 374  00d3 2004          	jra	L131
 375  00d5               L301:
 376                     ; 128 			case 9 :
 376                     ; 129 			GPIOB->ODR = NEUF;
 378  00d5 35f65005      	mov	20485,#246
 379                     ; 130 			break;
 381  00d9               L131:
 382                     ; 132 		return 1;
 384  00d9 a601          	ld	a,#1
 387  00db 5b01          	addw	sp,#1
 388  00dd 81            	ret
 432                     ; 138 void afficher_Digit_HDLX1(u8 numero, u8 caractere)
 432                     ; 139 {
 433                     	switch	.text
 434  00de               _afficher_Digit_HDLX1:
 436  00de 89            	pushw	x
 437       00000000      OFST:	set	0
 440                     ; 140 GPIOB->ODR = caractere + DISPLAY_ASCII; // MSB = 1 pour ASCII
 442  00df 9f            	ld	a,xl
 443  00e0 ab80          	add	a,#128
 444  00e2 c75005        	ld	20485,a
 445                     ; 141 GPIOG->ODR = numero ; //  numero digit
 447  00e5 7b01          	ld	a,(OFST+1,sp)
 448  00e7 c7501e        	ld	20510,a
 449                     ; 142 GPIOE->ODR = GPIOE->ODR & ~HDLX_NWR1; // activation WR1
 451  00ea 72175014      	bres	20500,#3
 452                     ; 143 GPIOE->ODR = GPIOE->ODR | HDLX_NWR1; // deactivation WR1
 454  00ee 72165014      	bset	20500,#3
 455                     ; 144 }
 458  00f2 85            	popw	x
 459  00f3 81            	ret
 503                     ; 148 void afficher_Digit_HDLX2(u8 numero, u8 caractere)
 503                     ; 149 {
 504                     	switch	.text
 505  00f4               _afficher_Digit_HDLX2:
 507  00f4 89            	pushw	x
 508       00000000      OFST:	set	0
 511                     ; 150 GPIOB->ODR = caractere + DISPLAY_ASCII; // MSB = 1 pour ASCII
 513  00f5 9f            	ld	a,xl
 514  00f6 ab80          	add	a,#128
 515  00f8 c75005        	ld	20485,a
 516                     ; 151 GPIOG->ODR = numero ; //  numero digit
 518  00fb 7b01          	ld	a,(OFST+1,sp)
 519  00fd c7501e        	ld	20510,a
 520                     ; 152 GPIOE->ODR = GPIOE->ODR & ~HDLX_NWR2; // activation WR2
 522  0100 721b5014      	bres	20500,#5
 523                     ; 153 GPIOE->ODR = GPIOE->ODR | HDLX_NWR2; // deactivation WR2
 525  0104 721a5014      	bset	20500,#5
 526                     ; 154 }
 529  0108 85            	popw	x
 530  0109 81            	ret
 574                     ; 158 void ecrire_Registre_Controle_Digit_HDLX1(u8 numero, u8 valeur)
 574                     ; 159 {
 575                     	switch	.text
 576  010a               _ecrire_Registre_Controle_Digit_HDLX1:
 580                     ; 160 GPIOB->ODR = valeur ; // MSB = 0 pour controle
 582  010a 9f            	ld	a,xl
 583  010b c75005        	ld	20485,a
 584                     ; 161 GPIOG->ODR = numero ; //  numero digit
 586  010e 9e            	ld	a,xh
 587  010f c7501e        	ld	20510,a
 588                     ; 162 GPIOE->ODR = GPIOE->ODR & ~HDLX_NWR1; // activation WR1
 590  0112 72175014      	bres	20500,#3
 591                     ; 163 GPIOE->ODR = GPIOE->ODR | HDLX_NWR1; // deactivation WR1
 593  0116 72165014      	bset	20500,#3
 594                     ; 164 }
 597  011a 81            	ret
 641                     ; 168 void ecrire_Registre_Controle_Digit_HDLX2(u8 numero, u8 valeur)
 641                     ; 169 {
 642                     	switch	.text
 643  011b               _ecrire_Registre_Controle_Digit_HDLX2:
 647                     ; 170 GPIOB->ODR = valeur ; // MSB = 0 pour controle
 649  011b 9f            	ld	a,xl
 650  011c c75005        	ld	20485,a
 651                     ; 171 GPIOG->ODR = numero ; //  numero digit
 653  011f 9e            	ld	a,xh
 654  0120 c7501e        	ld	20510,a
 655                     ; 172 GPIOE->ODR = GPIOE->ODR & ~HDLX_NWR2; // activation WR2
 657  0123 721b5014      	bres	20500,#5
 658                     ; 173 GPIOE->ODR = GPIOE->ODR | HDLX_NWR2; // deactivation WR2
 660  0127 721a5014      	bset	20500,#5
 661                     ; 174 }
 664  012b 81            	ret
 720                     ; 179 void afficher_Module_HDLX2(u8* chaine) 
 720                     ; 180 {
 721                     	switch	.text
 722  012c               _afficher_Module_HDLX2:
 724  012c 5203          	subw	sp,#3
 725       00000003      OFST:	set	3
 728                     ; 183 pointeur = chaine;
 730  012e 1f01          	ldw	(OFST-2,sp),x
 731                     ; 184 for ( numero = 3 ; numero > -1 ; numero -- )
 733  0130 a603          	ld	a,#3
 734  0132 6b03          	ld	(OFST+0,sp),a
 735  0134               L172:
 736                     ; 186 	afficher_Digit_HDLX2(numero, *pointeur);
 738  0134 1e01          	ldw	x,(OFST-2,sp)
 739  0136 f6            	ld	a,(x)
 740  0137 97            	ld	xl,a
 741  0138 7b03          	ld	a,(OFST+0,sp)
 742  013a 95            	ld	xh,a
 743  013b adb7          	call	_afficher_Digit_HDLX2
 745                     ; 187 	pointeur ++;
 747  013d 1e01          	ldw	x,(OFST-2,sp)
 748  013f 1c0001        	addw	x,#1
 749  0142 1f01          	ldw	(OFST-2,sp),x
 750                     ; 184 for ( numero = 3 ; numero > -1 ; numero -- )
 752  0144 0a03          	dec	(OFST+0,sp)
 755  0146 9c            	rvf
 756  0147 7b03          	ld	a,(OFST+0,sp)
 757  0149 a100          	cp	a,#0
 758  014b 2ee7          	jrsge	L172
 759                     ; 189 }
 762  014d 5b03          	addw	sp,#3
 763  014f 81            	ret
 819                     ; 194 void afficher_Module_HDLX1(u8* chaine)
 819                     ; 195 {
 820                     	switch	.text
 821  0150               _afficher_Module_HDLX1:
 823  0150 5203          	subw	sp,#3
 824       00000003      OFST:	set	3
 827                     ; 198 pointeur = chaine;
 829  0152 1f01          	ldw	(OFST-2,sp),x
 830                     ; 199 for ( numero = 3 ; numero > -1 ; numero -- )
 832  0154 a603          	ld	a,#3
 833  0156 6b03          	ld	(OFST+0,sp),a
 834  0158               L523:
 835                     ; 201 	afficher_Digit_HDLX1(numero, *pointeur);
 837  0158 1e01          	ldw	x,(OFST-2,sp)
 838  015a f6            	ld	a,(x)
 839  015b 97            	ld	xl,a
 840  015c 7b03          	ld	a,(OFST+0,sp)
 841  015e 95            	ld	xh,a
 842  015f cd00de        	call	_afficher_Digit_HDLX1
 844                     ; 202 	pointeur ++;
 846  0162 1e01          	ldw	x,(OFST-2,sp)
 847  0164 1c0001        	addw	x,#1
 848  0167 1f01          	ldw	(OFST-2,sp),x
 849                     ; 199 for ( numero = 3 ; numero > -1 ; numero -- )
 851  0169 0a03          	dec	(OFST+0,sp)
 854  016b 9c            	rvf
 855  016c 7b03          	ld	a,(OFST+0,sp)
 856  016e a100          	cp	a,#0
 857  0170 2ee6          	jrsge	L523
 858                     ; 204 }
 861  0172 5b03          	addw	sp,#3
 862  0174 81            	ret
 910                     ; 208 void afficher_Modules_HDLX(u8 *adresse)
 910                     ; 209 {
 911                     	switch	.text
 912  0175               _afficher_Modules_HDLX:
 914  0175 89            	pushw	x
 915       00000002      OFST:	set	2
 918                     ; 210 	u8 *pointeur = adresse;
 920  0176 1f01          	ldw	(OFST-1,sp),x
 921                     ; 211 	afficher_Module_HDLX2(pointeur);
 923  0178 1e01          	ldw	x,(OFST-1,sp)
 924  017a adb0          	call	_afficher_Module_HDLX2
 926                     ; 212 	pointeur += 4;
 928  017c 1e01          	ldw	x,(OFST-1,sp)
 929  017e 1c0004        	addw	x,#4
 930  0181 1f01          	ldw	(OFST-1,sp),x
 931                     ; 213 	afficher_Module_HDLX1(pointeur);
 933  0183 1e01          	ldw	x,(OFST-1,sp)
 934  0185 adc9          	call	_afficher_Module_HDLX1
 936                     ; 214 }
 939  0187 85            	popw	x
 940  0188 81            	ret
1003                     ; 219 void piloter_Clignotement_HDLX1(u8 digit3, u8 digit2, u8 digit1, u8 digit0)
1003                     ; 220 {	
1004                     	switch	.text
1005  0189               _piloter_Clignotement_HDLX1:
1007  0189 89            	pushw	x
1008       00000000      OFST:	set	0
1011                     ; 221     ecrire_Registre_Controle_Digit_HDLX1(3, digit3);
1013  018a 9e            	ld	a,xh
1014  018b 97            	ld	xl,a
1015  018c a603          	ld	a,#3
1016  018e 95            	ld	xh,a
1017  018f cd010a        	call	_ecrire_Registre_Controle_Digit_HDLX1
1019                     ; 222     ecrire_Registre_Controle_Digit_HDLX1(2, digit2);
1021  0192 7b02          	ld	a,(OFST+2,sp)
1022  0194 97            	ld	xl,a
1023  0195 a602          	ld	a,#2
1024  0197 95            	ld	xh,a
1025  0198 cd010a        	call	_ecrire_Registre_Controle_Digit_HDLX1
1027                     ; 223     ecrire_Registre_Controle_Digit_HDLX1(1, digit1);
1029  019b 7b05          	ld	a,(OFST+5,sp)
1030  019d 97            	ld	xl,a
1031  019e a601          	ld	a,#1
1032  01a0 95            	ld	xh,a
1033  01a1 cd010a        	call	_ecrire_Registre_Controle_Digit_HDLX1
1035                     ; 224     ecrire_Registre_Controle_Digit_HDLX1(0, digit0);
1037  01a4 7b06          	ld	a,(OFST+6,sp)
1038  01a6 97            	ld	xl,a
1039  01a7 4f            	clr	a
1040  01a8 95            	ld	xh,a
1041  01a9 cd010a        	call	_ecrire_Registre_Controle_Digit_HDLX1
1043                     ; 225 }
1046  01ac 85            	popw	x
1047  01ad 81            	ret
1110                     ; 230 void piloter_Clignotement_HDLX2(u8 digit3, u8 digit2, u8 digit1, u8 digit0)
1110                     ; 231 {	
1111                     	switch	.text
1112  01ae               _piloter_Clignotement_HDLX2:
1114  01ae 89            	pushw	x
1115       00000000      OFST:	set	0
1118                     ; 232     ecrire_Registre_Controle_Digit_HDLX2(3, digit3);
1120  01af 9e            	ld	a,xh
1121  01b0 97            	ld	xl,a
1122  01b1 a603          	ld	a,#3
1123  01b3 95            	ld	xh,a
1124  01b4 cd011b        	call	_ecrire_Registre_Controle_Digit_HDLX2
1126                     ; 233     ecrire_Registre_Controle_Digit_HDLX2(2, digit2);
1128  01b7 7b02          	ld	a,(OFST+2,sp)
1129  01b9 97            	ld	xl,a
1130  01ba a602          	ld	a,#2
1131  01bc 95            	ld	xh,a
1132  01bd cd011b        	call	_ecrire_Registre_Controle_Digit_HDLX2
1134                     ; 234     ecrire_Registre_Controle_Digit_HDLX2(1, digit1);
1136  01c0 7b05          	ld	a,(OFST+5,sp)
1137  01c2 97            	ld	xl,a
1138  01c3 a601          	ld	a,#1
1139  01c5 95            	ld	xh,a
1140  01c6 cd011b        	call	_ecrire_Registre_Controle_Digit_HDLX2
1142                     ; 235     ecrire_Registre_Controle_Digit_HDLX2(0, digit0);
1144  01c9 7b06          	ld	a,(OFST+6,sp)
1145  01cb 97            	ld	xl,a
1146  01cc 4f            	clr	a
1147  01cd 95            	ld	xh,a
1148  01ce cd011b        	call	_ecrire_Registre_Controle_Digit_HDLX2
1150                     ; 236 }
1153  01d1 85            	popw	x
1154  01d2 81            	ret
1178                     ; 243 void init_Timer3_PWM_canal2(void)
1178                     ; 244 {
1179                     	switch	.text
1180  01d3               _init_Timer3_PWM_canal2:
1184                     ; 245   TIM3-> CR1 |= TIM3_CR1_URS; // pour empecher UIF lors de UG
1186  01d3 72145320      	bset	21280,#2
1187                     ; 248 	TIM3-> PSCR = 3;
1189  01d7 3503532a      	mov	21290,#3
1190                     ; 249 	TIM3-> ARRH = 0x09; // pour période ...
1192  01db 3509532b      	mov	21291,#9
1193                     ; 250 	TIM3-> ARRL = 0xC4; // ... 10 ms
1195  01df 35c4532c      	mov	21292,#196
1196                     ; 253 	TIM3-> CCR2H = 0x00; //
1198  01e3 725f532f      	clr	21295
1199                     ; 254 	TIM3-> CCR2L = 0x7D; // 1/20ème de T
1201  01e7 357d5330      	mov	21296,#125
1202                     ; 256 	TIM3-> CCMR2 = 0x70; // PWM en mode 2 OC2 en sortie
1204  01eb 35705326      	mov	21286,#112
1205                     ; 257 	TIM3-> CCER1 = TIM3_CCER1_CC2P | TIM3_CCER1_CC2E ; // canal2 actif bas
1207  01ef 35305327      	mov	21287,#48
1208                     ; 260 	TIM3-> EGR = TIM3_EGR_UG; // chargement des registres
1210  01f3 35015324      	mov	21284,#1
1211                     ; 261 }
1214  01f7 81            	ret
1238                     ; 266 void init_Timer2_PWM_canal1(void)
1238                     ; 267 {
1239                     	switch	.text
1240  01f8               _init_Timer2_PWM_canal1:
1244                     ; 268   TIM2-> CR1 |= TIM2_CR1_URS; // pour empecher UIF lors de UG
1246  01f8 72145300      	bset	21248,#2
1247                     ; 270 	TIM2-> PSCR = 0x02;    // diviseur par 4 pour periode CLK_CNT 2µs
1249  01fc 3502530c      	mov	21260,#2
1250                     ; 273 	TIM2-> ARRH = 0x04;    // constante pour une ...
1252  0200 3504530d      	mov	21261,#4
1253                     ; 274 	TIM2-> ARRL = 0x6F;    // ... duree de 2,273 ms
1255  0204 356f530e      	mov	21262,#111
1256                     ; 277 	TIM2-> CCR1H = 0x02; //
1258  0208 3502530f      	mov	21263,#2
1259                     ; 278 	TIM2-> CCR1L = 0x38; // 1,136 msec
1261  020c 35385310      	mov	21264,#56
1262                     ; 280 	TIM2-> CCMR1 = 0x60; // PWM mode 1 - CC1 en sortie
1264  0210 35605305      	mov	21253,#96
1265                     ; 286 	TIM2-> EGR = TIM2_EGR_UG; // chargement des registres
1267  0214 35015304      	mov	21252,#1
1268                     ; 288 }
1271  0218 81            	ret
1295                     ; 293 void init_Timer2_PWM_canal2_10ms(void)
1295                     ; 294 {
1296                     	switch	.text
1297  0219               _init_Timer2_PWM_canal2_10ms:
1301                     ; 295   TIM2-> CR1 |= TIM2_CR1_URS; // pour empecher UIF lors de UG
1303  0219 72145300      	bset	21248,#2
1304                     ; 298 	TIM2-> PSCR = 3;
1306  021d 3503530c      	mov	21260,#3
1307                     ; 299 	TIM2-> ARRH = 0x09; // pour période ...
1309  0221 3509530d      	mov	21261,#9
1310                     ; 300 	TIM2-> ARRL = 0xC4; // ... 10 ms
1312  0225 35c4530e      	mov	21262,#196
1313                     ; 303 	TIM2-> CCR2H = 0x00; //
1315  0229 725f5311      	clr	21265
1316                     ; 304 	TIM2-> CCR2L = 0x7D; // 1/20ème de T
1318  022d 357d5312      	mov	21266,#125
1319                     ; 306 	TIM2-> CCMR2 = 0x70; // PWM en mode 2 OC2 en sortie
1321  0231 35705306      	mov	21254,#112
1322                     ; 307 	TIM2-> CCER1 = TIM2_CCER1_CC2P | TIM2_CCER1_CC2E ; // canal2 actif bas
1324  0235 35305308      	mov	21256,#48
1325                     ; 310 	TIM2-> EGR = TIM2_EGR_UG; // chargement des registres
1327  0239 35015304      	mov	21252,#1
1328                     ; 311 	TIM2-> CR1 |= TIM2_CR1_CEN; // démarrage Timer 2
1330  023d 72105300      	bset	21248,#0
1331                     ; 312 }
1334  0241 81            	ret
1358                     ; 317 void init_Timer2_PWM_canal2_6ms(void)
1358                     ; 318 {
1359                     	switch	.text
1360  0242               _init_Timer2_PWM_canal2_6ms:
1364                     ; 319   TIM2-> CR1 |= TIM2_CR1_URS; // pour empecher UIF lors de UG
1366  0242 72145300      	bset	21248,#2
1367                     ; 322 	TIM2-> PSCR = 3;
1369  0246 3503530c      	mov	21260,#3
1370                     ; 323 	TIM2-> ARRH = 0x05; // pour période ...
1372  024a 3505530d      	mov	21261,#5
1373                     ; 324 	TIM2-> ARRL = 0xDC; // ... 6 ms
1375  024e 35dc530e      	mov	21262,#220
1376                     ; 327 	TIM2-> CCR2H = 0x00; //
1378  0252 725f5311      	clr	21265
1379                     ; 328 	TIM2-> CCR2L = 0x7D; // 1/20ème de T
1381  0256 357d5312      	mov	21266,#125
1382                     ; 330 	TIM2-> CCMR2 = 0x70; // PWM en mode 2 OC2 en sortie
1384  025a 35705306      	mov	21254,#112
1385                     ; 331 	TIM2-> CCER1 = TIM2_CCER1_CC2P | TIM2_CCER1_CC2E ; // canal2 actif bas
1387  025e 35305308      	mov	21256,#48
1388                     ; 334 	TIM2-> EGR = TIM2_EGR_UG; // chargement des registres
1390  0262 35015304      	mov	21252,#1
1391                     ; 335 	TIM2-> CR1 |= TIM2_CR1_CEN; // démarrage Timer 2
1393  0266 72105300      	bset	21248,#0
1394                     ; 336 }
1397  026a 81            	ret
1421                     ; 342 void init_Timer2_PWM_canal2_1s(void)
1421                     ; 343 {
1422                     	switch	.text
1423  026b               _init_Timer2_PWM_canal2_1s:
1427                     ; 344   TIM2-> CR1 |= TIM2_CR1_URS; // pour empecher UIF lors de UG
1429  026b 72145300      	bset	21248,#2
1430                     ; 346 	TIM2-> PSCR = 0x05;    // diviseur par 32 pour periode CLK_CNT 16µs
1432  026f 3505530c      	mov	21260,#5
1433                     ; 349 	TIM2-> ARRH = 0xF4;    // constante pour une ...
1435  0273 35f4530d      	mov	21261,#244
1436                     ; 350 	TIM2-> ARRL = 0x23;    // ... duree de 1s
1438  0277 3523530e      	mov	21262,#35
1439                     ; 353 	TIM2-> CCR2H = 0x7A; //
1441  027b 357a5311      	mov	21265,#122
1442                     ; 354 	TIM2-> CCR2L = 0x11; // 0,5 sec
1444  027f 35115312      	mov	21266,#17
1445                     ; 356 	TIM2-> CCMR2 = 0x60; // PWM mode 1 CC2 en sortie
1447  0283 35605306      	mov	21254,#96
1448                     ; 361 	TIM2-> EGR = TIM2_EGR_UG; // chargement des registres
1450  0287 35015304      	mov	21252,#1
1451                     ; 362 	TIM2-> CR1 |= TIM2_CR1_CEN; // démarrage Timer 2
1453  028b 72105300      	bset	21248,#0
1454                     ; 363 }
1457  028f 81            	ret
1520                     ; 368 void conv_BCD_ASCII(u8 valeur_BCD, u8 *adresse)
1520                     ; 369 {
1521                     	switch	.text
1522  0290               _conv_BCD_ASCII:
1524  0290 88            	push	a
1525  0291 5203          	subw	sp,#3
1526       00000003      OFST:	set	3
1529                     ; 371 	u8 *pointeur = adresse;
1531  0293 1e07          	ldw	x,(OFST+4,sp)
1532  0295 1f01          	ldw	(OFST-2,sp),x
1533                     ; 373 	valeur = valeur_BCD; 
1535  0297 6b03          	ld	(OFST+0,sp),a
1536                     ; 374 	valeur = valeur & GPIO_PIN_HNIB; // conserve quartet fort
1538  0299 7b03          	ld	a,(OFST+0,sp)
1539  029b a4f0          	and	a,#240
1540  029d 6b03          	ld	(OFST+0,sp),a
1541                     ; 375 	valeur = valeur >> 4; // decalage droite 4 positions
1543  029f 7b03          	ld	a,(OFST+0,sp)
1544  02a1 4e            	swap	a
1545  02a2 a40f          	and	a,#15
1546  02a4 6b03          	ld	(OFST+0,sp),a
1547                     ; 376 	valeur += CODE_ASCII_0; // conversion ASCII
1549  02a6 7b03          	ld	a,(OFST+0,sp)
1550  02a8 ab30          	add	a,#48
1551  02aa 6b03          	ld	(OFST+0,sp),a
1552                     ; 377 	*pointeur = valeur; // mise en mémoire
1554  02ac 7b03          	ld	a,(OFST+0,sp)
1555  02ae 1e01          	ldw	x,(OFST-2,sp)
1556  02b0 f7            	ld	(x),a
1557                     ; 378 	pointeur ++;
1559  02b1 1e01          	ldw	x,(OFST-2,sp)
1560  02b3 1c0001        	addw	x,#1
1561  02b6 1f01          	ldw	(OFST-2,sp),x
1562                     ; 380 	valeur = valeur_BCD; 
1564  02b8 7b04          	ld	a,(OFST+1,sp)
1565  02ba 6b03          	ld	(OFST+0,sp),a
1566                     ; 381 	valeur = valeur & GPIO_PIN_LNIB; // conserve quartet faible
1568  02bc 7b03          	ld	a,(OFST+0,sp)
1569  02be a40f          	and	a,#15
1570  02c0 6b03          	ld	(OFST+0,sp),a
1571                     ; 382 	valeur += CODE_ASCII_0; // conversion ASCII
1573  02c2 7b03          	ld	a,(OFST+0,sp)
1574  02c4 ab30          	add	a,#48
1575  02c6 6b03          	ld	(OFST+0,sp),a
1576                     ; 383 	*pointeur = valeur; // mise en mémoire
1578  02c8 7b03          	ld	a,(OFST+0,sp)
1579  02ca 1e01          	ldw	x,(OFST-2,sp)
1580  02cc f7            	ld	(x),a
1581                     ; 385 }
1584  02cd 5b04          	addw	sp,#4
1585  02cf 81            	ret
1648                     ; 389 void conv_Bin_ASCII(u8 valeur_binaire, u8 *adresse)
1648                     ; 390 {
1649                     	switch	.text
1650  02d0               _conv_Bin_ASCII:
1652  02d0 88            	push	a
1653  02d1 5203          	subw	sp,#3
1654       00000003      OFST:	set	3
1657                     ; 391 	u8 *pointeur = adresse;
1659  02d3 1e07          	ldw	x,(OFST+4,sp)
1660  02d5 1f01          	ldw	(OFST-2,sp),x
1661                     ; 393 	valeur = valeur_binaire; 
1663  02d7 6b03          	ld	(OFST+0,sp),a
1664                     ; 394 	valeur = valeur & GPIO_PIN_HNIB; // conserve quartet fort
1666  02d9 7b03          	ld	a,(OFST+0,sp)
1667  02db a4f0          	and	a,#240
1668  02dd 6b03          	ld	(OFST+0,sp),a
1669                     ; 395 	valeur = valeur >> 4; // decalage droite 4 positions
1671  02df 7b03          	ld	a,(OFST+0,sp)
1672  02e1 4e            	swap	a
1673  02e2 a40f          	and	a,#15
1674  02e4 6b03          	ld	(OFST+0,sp),a
1675                     ; 396 	if (valeur > 9)
1677  02e6 7b03          	ld	a,(OFST+0,sp)
1678  02e8 a10a          	cp	a,#10
1679  02ea 2506          	jrult	L575
1680                     ; 398 		valeur += 7; // pour affichage de lettres
1682  02ec 7b03          	ld	a,(OFST+0,sp)
1683  02ee ab07          	add	a,#7
1684  02f0 6b03          	ld	(OFST+0,sp),a
1685  02f2               L575:
1686                     ; 400 	valeur += CODE_ASCII_0; // conversion ASCII
1688  02f2 7b03          	ld	a,(OFST+0,sp)
1689  02f4 ab30          	add	a,#48
1690  02f6 6b03          	ld	(OFST+0,sp),a
1691                     ; 401 	*pointeur = valeur; // mise en mémoire
1693  02f8 7b03          	ld	a,(OFST+0,sp)
1694  02fa 1e01          	ldw	x,(OFST-2,sp)
1695  02fc f7            	ld	(x),a
1696                     ; 402 	pointeur ++;
1698  02fd 1e01          	ldw	x,(OFST-2,sp)
1699  02ff 1c0001        	addw	x,#1
1700  0302 1f01          	ldw	(OFST-2,sp),x
1701                     ; 404 	valeur = valeur_binaire; 
1703  0304 7b04          	ld	a,(OFST+1,sp)
1704  0306 6b03          	ld	(OFST+0,sp),a
1705                     ; 405 	valeur = valeur & GPIO_PIN_LNIB; // conserve quartet faible
1707  0308 7b03          	ld	a,(OFST+0,sp)
1708  030a a40f          	and	a,#15
1709  030c 6b03          	ld	(OFST+0,sp),a
1710                     ; 406 	if (valeur > 9)
1712  030e 7b03          	ld	a,(OFST+0,sp)
1713  0310 a10a          	cp	a,#10
1714  0312 2506          	jrult	L775
1715                     ; 408 		valeur += 7; // pour affichage de lettres
1717  0314 7b03          	ld	a,(OFST+0,sp)
1718  0316 ab07          	add	a,#7
1719  0318 6b03          	ld	(OFST+0,sp),a
1720  031a               L775:
1721                     ; 410 	valeur += CODE_ASCII_0; // conversion ASCII
1723  031a 7b03          	ld	a,(OFST+0,sp)
1724  031c ab30          	add	a,#48
1725  031e 6b03          	ld	(OFST+0,sp),a
1726                     ; 411 	*pointeur = valeur; // mise en mémoire
1728  0320 7b03          	ld	a,(OFST+0,sp)
1729  0322 1e01          	ldw	x,(OFST-2,sp)
1730  0324 f7            	ld	(x),a
1731                     ; 412 }
1734  0325 5b04          	addw	sp,#4
1735  0327 81            	ret
1798                     ; 417 void conv1_BCD_ASCII(u16 valeur_BCD, u8 *adresse)
1798                     ; 418 {
1799                     	switch	.text
1800  0328               _conv1_BCD_ASCII:
1802  0328 89            	pushw	x
1803  0329 5204          	subw	sp,#4
1804       00000004      OFST:	set	4
1807                     ; 422 u8 *pointeur = adresse;
1809  032b 1e09          	ldw	x,(OFST+5,sp)
1810  032d 1f01          	ldw	(OFST-3,sp),x
1811                     ; 424 valeur = valeur_BCD;
1813  032f 1e05          	ldw	x,(OFST+1,sp)
1814  0331 1f03          	ldw	(OFST-1,sp),x
1815                     ; 425 valeur = valeur & 0x0F00;
1817  0333 0f04          	clr	(OFST+0,sp)
1818  0335 7b03          	ld	a,(OFST-1,sp)
1819  0337 a40f          	and	a,#15
1820  0339 6b03          	ld	(OFST-1,sp),a
1821                     ; 426 valeur = valeur >> 8; // decalage pour traitement des 4 bits des centaines
1823  033b 7b03          	ld	a,(OFST-1,sp)
1824  033d 6b04          	ld	(OFST+0,sp),a
1825  033f 0f03          	clr	(OFST-1,sp)
1826                     ; 427 	valeur += CODE_ASCII_0; // conversion ASCII
1828  0341 1e03          	ldw	x,(OFST-1,sp)
1829  0343 1c0030        	addw	x,#48
1830  0346 1f03          	ldw	(OFST-1,sp),x
1831                     ; 428 	*pointeur = valeur; // mise en mémoire
1833  0348 7b04          	ld	a,(OFST+0,sp)
1834  034a 1e01          	ldw	x,(OFST-3,sp)
1835  034c f7            	ld	(x),a
1836                     ; 429 	pointeur ++;
1838  034d 1e01          	ldw	x,(OFST-3,sp)
1839  034f 1c0001        	addw	x,#1
1840  0352 1f01          	ldw	(OFST-3,sp),x
1841                     ; 431 valeur = valeur_BCD; 
1843  0354 1e05          	ldw	x,(OFST+1,sp)
1844  0356 1f03          	ldw	(OFST-1,sp),x
1845                     ; 432 valeur = valeur & GPIO_PIN_HNIB; // conserve quartet fort
1847  0358 7b04          	ld	a,(OFST+0,sp)
1848  035a a4f0          	and	a,#240
1849  035c 6b04          	ld	(OFST+0,sp),a
1850  035e 0f03          	clr	(OFST-1,sp)
1851                     ; 433 valeur = valeur >> 4; // decalage droite 4 positions
1853  0360 a604          	ld	a,#4
1854  0362               L65:
1855  0362 0403          	srl	(OFST-1,sp)
1856  0364 0604          	rrc	(OFST+0,sp)
1857  0366 4a            	dec	a
1858  0367 26f9          	jrne	L65
1859                     ; 435 	valeur += CODE_ASCII_0; // conversion ASCII
1861  0369 1e03          	ldw	x,(OFST-1,sp)
1862  036b 1c0030        	addw	x,#48
1863  036e 1f03          	ldw	(OFST-1,sp),x
1864                     ; 436 	*pointeur = valeur; // mise en mémoire
1866  0370 7b04          	ld	a,(OFST+0,sp)
1867  0372 1e01          	ldw	x,(OFST-3,sp)
1868  0374 f7            	ld	(x),a
1869                     ; 437 	pointeur ++;
1871  0375 1e01          	ldw	x,(OFST-3,sp)
1872  0377 1c0001        	addw	x,#1
1873  037a 1f01          	ldw	(OFST-3,sp),x
1874                     ; 439 valeur = valeur_BCD; 
1876  037c 1e05          	ldw	x,(OFST+1,sp)
1877  037e 1f03          	ldw	(OFST-1,sp),x
1878                     ; 440 valeur = valeur & GPIO_PIN_LNIB; // conserve quartet faible
1880  0380 7b04          	ld	a,(OFST+0,sp)
1881  0382 a40f          	and	a,#15
1882  0384 6b04          	ld	(OFST+0,sp),a
1883  0386 0f03          	clr	(OFST-1,sp)
1884                     ; 442 	valeur += CODE_ASCII_0; // conversion ASCII
1886  0388 1e03          	ldw	x,(OFST-1,sp)
1887  038a 1c0030        	addw	x,#48
1888  038d 1f03          	ldw	(OFST-1,sp),x
1889                     ; 443 	*pointeur = valeur; // mise en mémoire
1891  038f 7b04          	ld	a,(OFST+0,sp)
1892  0391 1e01          	ldw	x,(OFST-3,sp)
1893  0393 f7            	ld	(x),a
1894                     ; 444 }
1897  0394 5b06          	addw	sp,#6
1898  0396 81            	ret
1950                     ; 446 u16 Ajustement_BCD(u16 valeur, u16 valeur_pre)
1950                     ; 447  {
1951                     	switch	.text
1952  0397               _Ajustement_BCD:
1954  0397 89            	pushw	x
1955  0398 5204          	subw	sp,#4
1956       00000004      OFST:	set	4
1959                     ; 448 	 short val = valeur;
1961  039a 1f03          	ldw	(OFST-1,sp),x
1962                     ; 449 	 if (((valeur & 0x000F )> 9) || ((valeur & 0x000F )<(valeur_pre & 0x000F ) ))
1964  039c 01            	rrwa	x,a
1965  039d a40f          	and	a,#15
1966  039f 5f            	clrw	x
1967  03a0 02            	rlwa	x,a
1968  03a1 a3000a        	cpw	x,#10
1969  03a4 2419          	jruge	L366
1971  03a6 7b09          	ld	a,(OFST+5,sp)
1972  03a8 97            	ld	xl,a
1973  03a9 7b0a          	ld	a,(OFST+6,sp)
1974  03ab a40f          	and	a,#15
1975  03ad 5f            	clrw	x
1976  03ae 02            	rlwa	x,a
1977  03af 1f01          	ldw	(OFST-3,sp),x
1978  03b1 01            	rrwa	x,a
1979  03b2 7b05          	ld	a,(OFST+1,sp)
1980  03b4 97            	ld	xl,a
1981  03b5 7b06          	ld	a,(OFST+2,sp)
1982  03b7 a40f          	and	a,#15
1983  03b9 5f            	clrw	x
1984  03ba 02            	rlwa	x,a
1985  03bb 1301          	cpw	x,(OFST-3,sp)
1986  03bd 2407          	jruge	L166
1987  03bf               L366:
1988                     ; 451 	  valeur = valeur + 6;
1990  03bf 1e05          	ldw	x,(OFST+1,sp)
1991  03c1 1c0006        	addw	x,#6
1992  03c4 1f05          	ldw	(OFST+1,sp),x
1993  03c6               L166:
1994                     ; 453 	 if ((valeur & 0x00F0) > 0x90)
1996  03c6 7b05          	ld	a,(OFST+1,sp)
1997  03c8 97            	ld	xl,a
1998  03c9 7b06          	ld	a,(OFST+2,sp)
1999  03cb a4f0          	and	a,#240
2000  03cd 5f            	clrw	x
2001  03ce 02            	rlwa	x,a
2002  03cf a30091        	cpw	x,#145
2003  03d2 2507          	jrult	L566
2004                     ; 455 	  valeur = valeur + 0x60;
2006  03d4 1e05          	ldw	x,(OFST+1,sp)
2007  03d6 1c0060        	addw	x,#96
2008  03d9 1f05          	ldw	(OFST+1,sp),x
2009  03db               L566:
2010                     ; 457 		return (valeur);
2012  03db 1e05          	ldw	x,(OFST+1,sp)
2015  03dd 5b06          	addw	sp,#6
2016  03df 81            	ret
2115                     ; 460 u16 Bin_BCD(u8 valeur)
2115                     ; 461  {
2116                     	switch	.text
2117  03e0               _Bin_BCD:
2119  03e0 88            	push	a
2120  03e1 520b          	subw	sp,#11
2121       0000000b      OFST:	set	11
2124                     ; 462 	 short reference_BCD = 1;
2126  03e3 ae0001        	ldw	x,#1
2127  03e6 1f0a          	ldw	(OFST-1,sp),x
2128                     ; 463 	 short reference_BCD_precedent = 0;
2130  03e8 5f            	clrw	x
2131  03e9 1f02          	ldw	(OFST-9,sp),x
2132                     ; 464 	 short resultat = 0;
2134  03eb 5f            	clrw	x
2135  03ec 1f07          	ldw	(OFST-4,sp),x
2136                     ; 465 	 short resultat_precedent = 0;
2138  03ee 5f            	clrw	x
2139  03ef 1f05          	ldw	(OFST-6,sp),x
2140                     ; 466 	 char masque_bit = 1;
2142  03f1 a601          	ld	a,#1
2143  03f3 6b09          	ld	(OFST-2,sp),a
2144                     ; 470 	 val=valeur;
2146                     ; 472 	 for ( numero_bit = 0; numero_bit < 8; numero_bit++)
2148  03f5 0f04          	clr	(OFST-7,sp)
2149  03f7               L147:
2150                     ; 474 		 if ( (valeur & masque_bit) == masque_bit )
2152  03f7 7b0c          	ld	a,(OFST+1,sp)
2153  03f9 1409          	and	a,(OFST-2,sp)
2154  03fb 1109          	cp	a,(OFST-2,sp)
2155  03fd 2616          	jrne	L747
2156                     ; 476 			 resultat = resultat_precedent + reference_BCD;
2158  03ff 1e05          	ldw	x,(OFST-6,sp)
2159  0401 72fb0a        	addw	x,(OFST-1,sp)
2160  0404 1f07          	ldw	(OFST-4,sp),x
2161                     ; 477 			 resultat = Ajustement_BCD(resultat,resultat_precedent);
2163  0406 1e05          	ldw	x,(OFST-6,sp)
2164  0408 89            	pushw	x
2165  0409 1e09          	ldw	x,(OFST-2,sp)
2166  040b ad8a          	call	_Ajustement_BCD
2168  040d 5b02          	addw	sp,#2
2169  040f 1f07          	ldw	(OFST-4,sp),x
2170                     ; 478 			 resultat_precedent = resultat;
2172  0411 1e07          	ldw	x,(OFST-4,sp)
2173  0413 1f05          	ldw	(OFST-6,sp),x
2174  0415               L747:
2175                     ; 480 		 reference_BCD = reference_BCD + reference_BCD;
2177  0415 080b          	sll	(OFST+0,sp)
2178  0417 090a          	rlc	(OFST-1,sp)
2179                     ; 481 		 reference_BCD = Ajustement_BCD(reference_BCD,reference_BCD_precedent);
2181  0419 1e02          	ldw	x,(OFST-9,sp)
2182  041b 89            	pushw	x
2183  041c 1e0c          	ldw	x,(OFST+1,sp)
2184  041e cd0397        	call	_Ajustement_BCD
2186  0421 5b02          	addw	sp,#2
2187  0423 1f0a          	ldw	(OFST-1,sp),x
2188                     ; 482 		 reference_BCD_precedent = reference_BCD;
2190  0425 1e0a          	ldw	x,(OFST-1,sp)
2191  0427 1f02          	ldw	(OFST-9,sp),x
2192                     ; 483 		 masque_bit = masque_bit + masque_bit;// decalage gauche 
2194  0429 0809          	sll	(OFST-2,sp)
2195                     ; 472 	 for ( numero_bit = 0; numero_bit < 8; numero_bit++)
2197  042b 0c04          	inc	(OFST-7,sp)
2200  042d 7b04          	ld	a,(OFST-7,sp)
2201  042f a108          	cp	a,#8
2202  0431 25c4          	jrult	L147
2203                     ; 485 	 return (resultat);
2205  0433 1e07          	ldw	x,(OFST-4,sp)
2208  0435 5b0c          	addw	sp,#12
2209  0437 81            	ret
2222                     	xdef	_lire_Etat_BP1
2223                     	xdef	_Bin_BCD
2224                     	xdef	_Ajustement_BCD
2225                     	xdef	_conv_Bin_ASCII
2226                     	xdef	_conv1_BCD_ASCII
2227                     	xdef	_conv_BCD_ASCII
2228                     	xdef	_piloter_Clignotement_HDLX2
2229                     	xdef	_piloter_Clignotement_HDLX1
2230                     	xdef	_afficher_Modules_HDLX
2231                     	xdef	_afficher_Module_HDLX2
2232                     	xdef	_afficher_Module_HDLX1
2233                     	xdef	_ecrire_Registre_Controle_Digit_HDLX2
2234                     	xdef	_ecrire_Registre_Controle_Digit_HDLX1
2235                     	xdef	_afficher_Digit_HDLX2
2236                     	xdef	_afficher_Digit_HDLX1
2237                     	xdef	_afficher_TIL321
2238                     	xdef	_lire_Etat_BP2
2239                     	xdef	_init_Timer2_PWM_canal2_6ms
2240                     	xdef	_init_Timer2_PWM_canal2_10ms
2241                     	xdef	_init_Timer2_PWM_canal2_1s
2242                     	xdef	_init_Timer2_PWM_canal1
2243                     	xdef	_init_Timer3_PWM_canal2
2244                     	xdef	_init_Ports
2263                     	end
