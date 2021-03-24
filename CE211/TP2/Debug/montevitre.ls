   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.10.2 - 02 Nov 2011
   3                     ; Generator (Limited) V4.3.7 - 29 Nov 2011
  83                     ; 5 main()
  83                     ; 6 {
  85                     	switch	.text
  86  0000               _main:
  88  0000 5206          	subw	sp,#6
  89       00000006      OFST:	set	6
  92                     ; 14 	init_Ports();
  94  0002 cd0000        	call	_init_Ports
  96                     ; 17 	TIM3->ARRL =0x9;
  98  0005 3509532c      	mov	21292,#9
  99                     ; 18 	TIM3->ARRH =0xF;
 101  0009 350f532b      	mov	21291,#15
 102                     ; 19 	TIM3->PSCR =0x04;
 104  000d 3504532a      	mov	21290,#4
 105                     ; 22 	TIM2->ARRL =0x9;
 107  0011 3509530e      	mov	21262,#9
 108                     ; 23 	TIM2->ARRH =0xF;
 110  0015 350f530d      	mov	21261,#15
 111                     ; 24 	TIM2->PSCR =0x05;
 113  0019 3505530c      	mov	21260,#5
 114                     ; 27 	temps = 0;
 116  001d 0f06          	clr	(OFST+0,sp)
 117                     ; 28 	GPIOB->ODR = GPIO_PIN_0 << temps;			//emplacement de la fenêtre
 119  001f 35015005      	mov	20485,#1
 120  0023               L34:
 121                     ; 32 	afficher_Modules_HDLX("ARRET :)");
 123  0023 ae0012        	ldw	x,#L74
 124  0026 cd0000        	call	_afficher_Modules_HDLX
 126                     ; 33 	GPIOB->ODR= 0;
 128  0029 725f5005      	clr	20485
 129                     ; 35 	if ((((GPIOC->IDR & GPIO_PIN_2) != GPIO_PIN_2)&(GPIOC->IDR & GPIO_PIN_7) == GPIO_PIN_7)) 	//BT3 appuyé on rentre dans la if
 131  002d c6500b        	ld	a,20491
 132  0030 a480          	and	a,#128
 133  0032 a180          	cp	a,#128
 134  0034 2605          	jrne	L6
 135  0036 ae0001        	ldw	x,#1
 136  0039 2001          	jra	L01
 137  003b               L6:
 138  003b 5f            	clrw	x
 139  003c               L01:
 140  003c 1f01          	ldw	(OFST-5,sp),x
 141  003e c6500b        	ld	a,20491
 142  0041 a404          	and	a,#4
 143  0043 a104          	cp	a,#4
 144  0045 2705          	jreq	L21
 145  0047 ae0001        	ldw	x,#1
 146  004a 2001          	jra	L41
 147  004c               L21:
 148  004c 5f            	clrw	x
 149  004d               L41:
 150  004d 01            	rrwa	x,a
 151  004e 1402          	and	a,(OFST-4,sp)
 152  0050 01            	rrwa	x,a
 153  0051 1401          	and	a,(OFST-5,sp)
 154  0053 01            	rrwa	x,a
 155  0054 a30000        	cpw	x,#0
 156  0057 2603          	jrne	L241
 157  0059 cc01ae        	jp	L15
 158  005c               L241:
 159                     ; 37 			afficher_Modules_HDLX("MONTEE  ");
 161  005c ae0009        	ldw	x,#L35
 162  005f cd0000        	call	_afficher_Modules_HDLX
 164                     ; 38 			temps = (8 - temps) %8;
 166  0062 a600          	ld	a,#0
 167  0064 97            	ld	xl,a
 168  0065 a608          	ld	a,#8
 169  0067 1006          	sub	a,(OFST+0,sp)
 170  0069 2401          	jrnc	L61
 171  006b 5a            	decw	x
 172  006c               L61:
 173  006c 02            	rlwa	x,a
 174  006d a608          	ld	a,#8
 175  006f cd0000        	call	c_smodx
 177  0072 01            	rrwa	x,a
 178  0073 6b06          	ld	(OFST+0,sp),a
 179  0075 02            	rlwa	x,a
 180                     ; 39 			TIM3->CR1 = TIM3->CR1 | TIM3_CR1_CEN;	
 182  0076 72105320      	bset	21280,#0
 183                     ; 40 			TIM2->CR1 = TIM2->CR1 | TIM2_CR1_CEN;	
 185  007a 72105300      	bset	21248,#0
 186                     ; 41 			bit_uif2 = TIM2->SR1 & TIM2_SR1_UIF;
 188  007e c65302        	ld	a,21250
 189  0081 a401          	and	a,#1
 190  0083 6b03          	ld	(OFST-3,sp),a
 191                     ; 42 			bit_uif3 = TIM3->SR1 & TIM3_SR1_UIF;
 193  0085 c65322        	ld	a,21282
 194  0088 a401          	and	a,#1
 196  008a 2033          	jra	L75
 197  008c               L55:
 198                     ; 46 					bit_uif2 = TIM2->SR1 & TIM2_SR1_UIF;
 200  008c c65302        	ld	a,21250
 201  008f a401          	and	a,#1
 202  0091 6b03          	ld	(OFST-3,sp),a
 203                     ; 47 					bit_uif3 = TIM3->SR1 & TIM3_SR1_UIF;	
 205  0093 c65322        	ld	a,21282
 206  0096 a401          	and	a,#1
 207  0098 6b05          	ld	(OFST-1,sp),a
 208                     ; 48 					if (bit_uif3 == 1)
 210  009a 7b05          	ld	a,(OFST-1,sp)
 211  009c a101          	cp	a,#1
 212  009e 261f          	jrne	L75
 213                     ; 50 					temps++;																						//on ajoute 1 à la variable seconde
 215  00a0 0c06          	inc	(OFST+0,sp)
 216                     ; 51 					temps = temps %8;
 218  00a2 7b06          	ld	a,(OFST+0,sp)
 219  00a4 a407          	and	a,#7
 220  00a6 6b06          	ld	(OFST+0,sp),a
 221                     ; 52 					GPIOB->ODR = GPIO_PIN_0 << temps;
 223  00a8 7b06          	ld	a,(OFST+0,sp)
 224  00aa 5f            	clrw	x
 225  00ab 97            	ld	xl,a
 226  00ac a601          	ld	a,#1
 227  00ae 5d            	tnzw	x
 228  00af 2704          	jreq	L02
 229  00b1               L22:
 230  00b1 48            	sll	a
 231  00b2 5a            	decw	x
 232  00b3 26fc          	jrne	L22
 233  00b5               L02:
 234  00b5 c75005        	ld	20485,a
 235                     ; 53 					affichage = GPIOB->ODR;
 237  00b8 c65005        	ld	a,20485
 238                     ; 54 					TIM3->SR1 = TIM3->SR1 & ~TIM3_SR1_UIF;  							// UIF à 0
 240  00bb 72115322      	bres	21282,#0
 241  00bf               L75:
 242                     ; 44 			while ((bit_uif2==0) & ((GPIOC->IDR & GPIO_PIN_7) == GPIO_PIN_7)) //attendre 1 seconde et si fin de course alors on sort du if
 244  00bf c6500b        	ld	a,20491
 245  00c2 a480          	and	a,#128
 246  00c4 a180          	cp	a,#128
 247  00c6 2605          	jrne	L42
 248  00c8 ae0001        	ldw	x,#1
 249  00cb 2001          	jra	L62
 250  00cd               L42:
 251  00cd 5f            	clrw	x
 252  00ce               L62:
 253  00ce 1f01          	ldw	(OFST-5,sp),x
 254  00d0 0d03          	tnz	(OFST-3,sp)
 255  00d2 2605          	jrne	L03
 256  00d4 ae0001        	ldw	x,#1
 257  00d7 2001          	jra	L23
 258  00d9               L03:
 259  00d9 5f            	clrw	x
 260  00da               L23:
 261  00da 01            	rrwa	x,a
 262  00db 1402          	and	a,(OFST-4,sp)
 263  00dd 01            	rrwa	x,a
 264  00de 1401          	and	a,(OFST-5,sp)
 265  00e0 01            	rrwa	x,a
 266  00e1 a30000        	cpw	x,#0
 267  00e4 26a6          	jrne	L55
 268                     ; 57 			TIM2->SR1 = TIM2->SR1 & ~TIM2_SR1_UIF;
 270  00e6 72115302      	bres	21250,#0
 271                     ; 58 			TIM2->CR1 = TIM2->CR1 & ~TIM2_CR1_CEN;	
 273  00ea 72115300      	bres	21248,#0
 274                     ; 60 			if (((GPIOC->IDR & GPIO_PIN_2) != GPIO_PIN_2) & ((GPIOC->IDR & GPIO_PIN_7) == GPIO_PIN_7))
 276  00ee c6500b        	ld	a,20491
 277  00f1 a480          	and	a,#128
 278  00f3 a180          	cp	a,#128
 279  00f5 2605          	jrne	L43
 280  00f7 ae0001        	ldw	x,#1
 281  00fa 2001          	jra	L63
 282  00fc               L43:
 283  00fc 5f            	clrw	x
 284  00fd               L63:
 285  00fd 1f01          	ldw	(OFST-5,sp),x
 286  00ff c6500b        	ld	a,20491
 287  0102 a404          	and	a,#4
 288  0104 a104          	cp	a,#4
 289  0106 2705          	jreq	L04
 290  0108 ae0001        	ldw	x,#1
 291  010b 2001          	jra	L24
 292  010d               L04:
 293  010d 5f            	clrw	x
 294  010e               L24:
 295  010e 01            	rrwa	x,a
 296  010f 1402          	and	a,(OFST-4,sp)
 297  0111 01            	rrwa	x,a
 298  0112 1401          	and	a,(OFST-5,sp)
 299  0114 01            	rrwa	x,a
 300  0115 a30000        	cpw	x,#0
 301  0118 2603          	jrne	L441
 302  011a cc01a5        	jp	L301
 303  011d               L441:
 305  011d 202c          	jra	L17
 306  011f               L76:
 307                     ; 64 						bit_uif3 = TIM3->SR1 & TIM3_SR1_UIF;	
 309  011f c65322        	ld	a,21282
 310  0122 a401          	and	a,#1
 311  0124 6b05          	ld	(OFST-1,sp),a
 312                     ; 65 						if (bit_uif3 == 1)
 314  0126 7b05          	ld	a,(OFST-1,sp)
 315  0128 a101          	cp	a,#1
 316  012a 261f          	jrne	L17
 317                     ; 67 						temps++;																						//on ajoute 1 à la variable seconde
 319  012c 0c06          	inc	(OFST+0,sp)
 320                     ; 68 						temps = temps %8;
 322  012e 7b06          	ld	a,(OFST+0,sp)
 323  0130 a407          	and	a,#7
 324  0132 6b06          	ld	(OFST+0,sp),a
 325                     ; 69 						GPIOB->ODR = GPIO_PIN_0 << temps;
 327  0134 7b06          	ld	a,(OFST+0,sp)
 328  0136 5f            	clrw	x
 329  0137 97            	ld	xl,a
 330  0138 a601          	ld	a,#1
 331  013a 5d            	tnzw	x
 332  013b 2704          	jreq	L44
 333  013d               L64:
 334  013d 48            	sll	a
 335  013e 5a            	decw	x
 336  013f 26fc          	jrne	L64
 337  0141               L44:
 338  0141 c75005        	ld	20485,a
 339                     ; 70 						affichage = GPIOB->ODR;
 341  0144 c65005        	ld	a,20485
 342                     ; 71 						TIM3->SR1 = TIM3->SR1 & ~TIM3_SR1_UIF;  							// UIF à 0
 344  0147 72115322      	bres	21282,#0
 345  014b               L17:
 346                     ; 62 				while (((GPIOC->IDR & GPIO_PIN_2) != GPIO_PIN_2)&((GPIOC->IDR & GPIO_PIN_7) == GPIO_PIN_7))
 348  014b c6500b        	ld	a,20491
 349  014e a480          	and	a,#128
 350  0150 a180          	cp	a,#128
 351  0152 2605          	jrne	L05
 352  0154 ae0001        	ldw	x,#1
 353  0157 2001          	jra	L25
 354  0159               L05:
 355  0159 5f            	clrw	x
 356  015a               L25:
 357  015a 1f01          	ldw	(OFST-5,sp),x
 358  015c c6500b        	ld	a,20491
 359  015f a404          	and	a,#4
 360  0161 a104          	cp	a,#4
 361  0163 2705          	jreq	L45
 362  0165 ae0001        	ldw	x,#1
 363  0168 2001          	jra	L65
 364  016a               L45:
 365  016a 5f            	clrw	x
 366  016b               L65:
 367  016b 01            	rrwa	x,a
 368  016c 1402          	and	a,(OFST-4,sp)
 369  016e 01            	rrwa	x,a
 370  016f 1401          	and	a,(OFST-5,sp)
 371  0171 01            	rrwa	x,a
 372  0172 a30000        	cpw	x,#0
 373  0175 26a8          	jrne	L76
 375  0177 2035          	jra	L15
 376  0179               L101:
 377                     ; 79 						bit_uif3 = TIM3->SR1 & TIM3_SR1_UIF;	
 379  0179 c65322        	ld	a,21282
 380  017c a401          	and	a,#1
 381  017e 6b05          	ld	(OFST-1,sp),a
 382                     ; 80 						if (bit_uif3 == 1)
 384  0180 7b05          	ld	a,(OFST-1,sp)
 385  0182 a101          	cp	a,#1
 386  0184 261f          	jrne	L301
 387                     ; 82 						temps++;																						//on ajoute 1 à la variable seconde
 389  0186 0c06          	inc	(OFST+0,sp)
 390                     ; 83 						temps = temps %8;
 392  0188 7b06          	ld	a,(OFST+0,sp)
 393  018a a407          	and	a,#7
 394  018c 6b06          	ld	(OFST+0,sp),a
 395                     ; 84 						GPIOB->ODR = GPIO_PIN_0 << temps;
 397  018e 7b06          	ld	a,(OFST+0,sp)
 398  0190 5f            	clrw	x
 399  0191 97            	ld	xl,a
 400  0192 a601          	ld	a,#1
 401  0194 5d            	tnzw	x
 402  0195 2704          	jreq	L06
 403  0197               L26:
 404  0197 48            	sll	a
 405  0198 5a            	decw	x
 406  0199 26fc          	jrne	L26
 407  019b               L06:
 408  019b c75005        	ld	20485,a
 409                     ; 85 						affichage = GPIOB->ODR;
 411  019e c65005        	ld	a,20485
 412                     ; 86 						TIM3->SR1 = TIM3->SR1 & ~TIM3_SR1_UIF;  							// UIF à 0
 414  01a1 72115322      	bres	21282,#0
 415  01a5               L301:
 416                     ; 77 				while ((GPIOC->IDR & GPIO_PIN_7) == GPIO_PIN_7)
 418  01a5 c6500b        	ld	a,20491
 419  01a8 a480          	and	a,#128
 420  01aa a180          	cp	a,#128
 421  01ac 27cb          	jreq	L101
 422  01ae               L15:
 423                     ; 95 	if ((((GPIOC->IDR & GPIO_PIN_3) != GPIO_PIN_3)&(GPIOC->IDR & GPIO_PIN_4) == GPIO_PIN_4)) 	//BT3 appuyé on rentre dans la if
 425  01ae c6500b        	ld	a,20491
 426  01b1 a410          	and	a,#16
 427  01b3 a110          	cp	a,#16
 428  01b5 2605          	jrne	L46
 429  01b7 ae0001        	ldw	x,#1
 430  01ba 2001          	jra	L66
 431  01bc               L46:
 432  01bc 5f            	clrw	x
 433  01bd               L66:
 434  01bd 1f01          	ldw	(OFST-5,sp),x
 435  01bf c6500b        	ld	a,20491
 436  01c2 a408          	and	a,#8
 437  01c4 a108          	cp	a,#8
 438  01c6 2705          	jreq	L07
 439  01c8 ae0001        	ldw	x,#1
 440  01cb 2001          	jra	L27
 441  01cd               L07:
 442  01cd 5f            	clrw	x
 443  01ce               L27:
 444  01ce 01            	rrwa	x,a
 445  01cf 1402          	and	a,(OFST-4,sp)
 446  01d1 01            	rrwa	x,a
 447  01d2 1401          	and	a,(OFST-5,sp)
 448  01d4 01            	rrwa	x,a
 449  01d5 a30000        	cpw	x,#0
 450  01d8 2603          	jrne	L641
 451  01da cc0023        	jp	L34
 452  01dd               L641:
 453                     ; 97 			afficher_Modules_HDLX("DESCENTE");
 455  01dd ae0000        	ldw	x,#L311
 456  01e0 cd0000        	call	_afficher_Modules_HDLX
 458                     ; 98 			temps = (8 - temps) %8;
 460  01e3 a600          	ld	a,#0
 461  01e5 97            	ld	xl,a
 462  01e6 a608          	ld	a,#8
 463  01e8 1006          	sub	a,(OFST+0,sp)
 464  01ea 2401          	jrnc	L47
 465  01ec 5a            	decw	x
 466  01ed               L47:
 467  01ed 02            	rlwa	x,a
 468  01ee a608          	ld	a,#8
 469  01f0 cd0000        	call	c_smodx
 471  01f3 01            	rrwa	x,a
 472  01f4 6b06          	ld	(OFST+0,sp),a
 473  01f6 02            	rlwa	x,a
 474                     ; 99 			TIM3->CR1 = TIM3->CR1 | TIM3_CR1_CEN;	
 476  01f7 72105320      	bset	21280,#0
 477                     ; 100 			TIM2->CR1 = TIM2->CR1 | TIM2_CR1_CEN;	
 479  01fb 72105300      	bset	21248,#0
 480                     ; 101 			bit_uif2 = TIM2->SR1 & TIM2_SR1_UIF;
 482  01ff c65302        	ld	a,21250
 483  0202 a401          	and	a,#1
 484  0204 6b03          	ld	(OFST-3,sp),a
 485                     ; 102 			bit_uif3 = TIM3->SR1 & TIM3_SR1_UIF;
 487  0206 c65322        	ld	a,21282
 488  0209 a401          	and	a,#1
 490  020b 2033          	jra	L711
 491  020d               L511:
 492                     ; 106 					bit_uif2 = TIM2->SR1 & TIM2_SR1_UIF;
 494  020d c65302        	ld	a,21250
 495  0210 a401          	and	a,#1
 496  0212 6b03          	ld	(OFST-3,sp),a
 497                     ; 107 					bit_uif3 = TIM3->SR1 & TIM3_SR1_UIF;	
 499  0214 c65322        	ld	a,21282
 500  0217 a401          	and	a,#1
 501  0219 6b05          	ld	(OFST-1,sp),a
 502                     ; 108 					if (bit_uif3 == 1)
 504  021b 7b05          	ld	a,(OFST-1,sp)
 505  021d a101          	cp	a,#1
 506  021f 261f          	jrne	L711
 507                     ; 110 					temps++;																						//on ajoute 1 à la variable seconde
 509  0221 0c06          	inc	(OFST+0,sp)
 510                     ; 111 					temps = temps %8;
 512  0223 7b06          	ld	a,(OFST+0,sp)
 513  0225 a407          	and	a,#7
 514  0227 6b06          	ld	(OFST+0,sp),a
 515                     ; 112 					GPIOB->ODR = GPIO_PIN_7 >> temps;
 517  0229 7b06          	ld	a,(OFST+0,sp)
 518  022b 5f            	clrw	x
 519  022c 97            	ld	xl,a
 520  022d a680          	ld	a,#128
 521  022f 5d            	tnzw	x
 522  0230 2704          	jreq	L67
 523  0232               L001:
 524  0232 44            	srl	a
 525  0233 5a            	decw	x
 526  0234 26fc          	jrne	L001
 527  0236               L67:
 528  0236 c75005        	ld	20485,a
 529                     ; 113 					affichage = GPIOB->ODR;
 531  0239 c65005        	ld	a,20485
 532                     ; 114 					TIM3->SR1 = TIM3->SR1 & ~TIM3_SR1_UIF;  							// UIF à 0
 534  023c 72115322      	bres	21282,#0
 535  0240               L711:
 536                     ; 104 			while ((bit_uif2==0) & ((GPIOC->IDR & GPIO_PIN_4) == GPIO_PIN_4)) //attendre 1 seconde et si fin de course alors on sort du if
 538  0240 c6500b        	ld	a,20491
 539  0243 a410          	and	a,#16
 540  0245 a110          	cp	a,#16
 541  0247 2605          	jrne	L201
 542  0249 ae0001        	ldw	x,#1
 543  024c 2001          	jra	L401
 544  024e               L201:
 545  024e 5f            	clrw	x
 546  024f               L401:
 547  024f 1f01          	ldw	(OFST-5,sp),x
 548  0251 0d03          	tnz	(OFST-3,sp)
 549  0253 2605          	jrne	L601
 550  0255 ae0001        	ldw	x,#1
 551  0258 2001          	jra	L011
 552  025a               L601:
 553  025a 5f            	clrw	x
 554  025b               L011:
 555  025b 01            	rrwa	x,a
 556  025c 1402          	and	a,(OFST-4,sp)
 557  025e 01            	rrwa	x,a
 558  025f 1401          	and	a,(OFST-5,sp)
 559  0261 01            	rrwa	x,a
 560  0262 a30000        	cpw	x,#0
 561  0265 26a6          	jrne	L511
 562                     ; 117 			TIM2->SR1 = TIM2->SR1 & ~TIM2_SR1_UIF;
 564  0267 72115302      	bres	21250,#0
 565                     ; 118 			TIM2->CR1 = TIM2->CR1 & ~TIM2_CR1_CEN;	
 567  026b 72115300      	bres	21248,#0
 568                     ; 120 			if (((GPIOC->IDR & GPIO_PIN_3) != GPIO_PIN_3) & ((GPIOC->IDR & GPIO_PIN_4) == GPIO_PIN_4))
 570  026f c6500b        	ld	a,20491
 571  0272 a410          	and	a,#16
 572  0274 a110          	cp	a,#16
 573  0276 2605          	jrne	L211
 574  0278 ae0001        	ldw	x,#1
 575  027b 2001          	jra	L411
 576  027d               L211:
 577  027d 5f            	clrw	x
 578  027e               L411:
 579  027e 1f01          	ldw	(OFST-5,sp),x
 580  0280 c6500b        	ld	a,20491
 581  0283 a408          	and	a,#8
 582  0285 a108          	cp	a,#8
 583  0287 2705          	jreq	L611
 584  0289 ae0001        	ldw	x,#1
 585  028c 2001          	jra	L021
 586  028e               L611:
 587  028e 5f            	clrw	x
 588  028f               L021:
 589  028f 01            	rrwa	x,a
 590  0290 1402          	and	a,(OFST-4,sp)
 591  0292 01            	rrwa	x,a
 592  0293 1401          	and	a,(OFST-5,sp)
 593  0295 01            	rrwa	x,a
 594  0296 a30000        	cpw	x,#0
 595  0299 2603          	jrne	L051
 596  029b cc0328        	jp	L341
 597  029e               L051:
 599  029e 202c          	jra	L131
 600  02a0               L721:
 601                     ; 124 						bit_uif3 = TIM3->SR1 & TIM3_SR1_UIF;	
 603  02a0 c65322        	ld	a,21282
 604  02a3 a401          	and	a,#1
 605  02a5 6b05          	ld	(OFST-1,sp),a
 606                     ; 125 						if (bit_uif3 == 1)
 608  02a7 7b05          	ld	a,(OFST-1,sp)
 609  02a9 a101          	cp	a,#1
 610  02ab 261f          	jrne	L131
 611                     ; 127 						temps++;																						//on ajoute 1 à la variable seconde
 613  02ad 0c06          	inc	(OFST+0,sp)
 614                     ; 128 						temps = temps %8;
 616  02af 7b06          	ld	a,(OFST+0,sp)
 617  02b1 a407          	and	a,#7
 618  02b3 6b06          	ld	(OFST+0,sp),a
 619                     ; 129 						GPIOB->ODR = GPIO_PIN_7 >> temps;
 621  02b5 7b06          	ld	a,(OFST+0,sp)
 622  02b7 5f            	clrw	x
 623  02b8 97            	ld	xl,a
 624  02b9 a680          	ld	a,#128
 625  02bb 5d            	tnzw	x
 626  02bc 2704          	jreq	L221
 627  02be               L421:
 628  02be 44            	srl	a
 629  02bf 5a            	decw	x
 630  02c0 26fc          	jrne	L421
 631  02c2               L221:
 632  02c2 c75005        	ld	20485,a
 633                     ; 130 						affichage = GPIOB->ODR;
 635  02c5 c65005        	ld	a,20485
 636                     ; 131 						TIM3->SR1 = TIM3->SR1 & ~TIM3_SR1_UIF;  							// UIF à 0
 638  02c8 72115322      	bres	21282,#0
 639  02cc               L131:
 640                     ; 122 				while (((GPIOC->IDR & GPIO_PIN_3) != GPIO_PIN_3)&((GPIOC->IDR & GPIO_PIN_4) == GPIO_PIN_4))
 642  02cc c6500b        	ld	a,20491
 643  02cf a410          	and	a,#16
 644  02d1 a110          	cp	a,#16
 645  02d3 2605          	jrne	L621
 646  02d5 ae0001        	ldw	x,#1
 647  02d8 2001          	jra	L031
 648  02da               L621:
 649  02da 5f            	clrw	x
 650  02db               L031:
 651  02db 1f01          	ldw	(OFST-5,sp),x
 652  02dd c6500b        	ld	a,20491
 653  02e0 a408          	and	a,#8
 654  02e2 a108          	cp	a,#8
 655  02e4 2705          	jreq	L231
 656  02e6 ae0001        	ldw	x,#1
 657  02e9 2001          	jra	L431
 658  02eb               L231:
 659  02eb 5f            	clrw	x
 660  02ec               L431:
 661  02ec 01            	rrwa	x,a
 662  02ed 1402          	and	a,(OFST-4,sp)
 663  02ef 01            	rrwa	x,a
 664  02f0 1401          	and	a,(OFST-5,sp)
 665  02f2 01            	rrwa	x,a
 666  02f3 a30000        	cpw	x,#0
 667  02f6 26a8          	jrne	L721
 669  02f8 ac230023      	jpf	L34
 670  02fc               L141:
 671                     ; 139 						bit_uif3 = TIM3->SR1 & TIM3_SR1_UIF;	
 673  02fc c65322        	ld	a,21282
 674  02ff a401          	and	a,#1
 675  0301 6b05          	ld	(OFST-1,sp),a
 676                     ; 140 						if (bit_uif3 == 1)
 678  0303 7b05          	ld	a,(OFST-1,sp)
 679  0305 a101          	cp	a,#1
 680  0307 261f          	jrne	L341
 681                     ; 142 						temps++;																						//on ajoute 1 à la variable seconde
 683  0309 0c06          	inc	(OFST+0,sp)
 684                     ; 143 						temps = temps %8;
 686  030b 7b06          	ld	a,(OFST+0,sp)
 687  030d a407          	and	a,#7
 688  030f 6b06          	ld	(OFST+0,sp),a
 689                     ; 144 						GPIOB->ODR = GPIO_PIN_7 >> temps;
 691  0311 7b06          	ld	a,(OFST+0,sp)
 692  0313 5f            	clrw	x
 693  0314 97            	ld	xl,a
 694  0315 a680          	ld	a,#128
 695  0317 5d            	tnzw	x
 696  0318 2704          	jreq	L631
 697  031a               L041:
 698  031a 44            	srl	a
 699  031b 5a            	decw	x
 700  031c 26fc          	jrne	L041
 701  031e               L631:
 702  031e c75005        	ld	20485,a
 703                     ; 145 						affichage = GPIOB->ODR;
 705  0321 c65005        	ld	a,20485
 706                     ; 146 						TIM3->SR1 = TIM3->SR1 & ~TIM3_SR1_UIF;  							// UIF à 0
 708  0324 72115322      	bres	21282,#0
 709  0328               L341:
 710                     ; 137 				while ((GPIOC->IDR & GPIO_PIN_4) == GPIO_PIN_4)
 712  0328 c6500b        	ld	a,20491
 713  032b a410          	and	a,#16
 714  032d a110          	cp	a,#16
 715  032f 27cb          	jreq	L141
 716  0331 ac230023      	jpf	L34
 729                     	xdef	_main
 730                     	xref	_afficher_Modules_HDLX
 731                     	xref	_init_Ports
 732                     .const:	section	.text
 733  0000               L311:
 734  0000 44455343454e  	dc.b	"DESCENTE",0
 735  0009               L35:
 736  0009 4d4f4e544545  	dc.b	"MONTEE  ",0
 737  0012               L74:
 738  0012 415252455420  	dc.b	"ARRET :)",0
 739                     	xref.b	c_x
 759                     	xref	c_smodx
 760                     	end
