   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.10.2 - 02 Nov 2011
   3                     ; Generator (Limited) V4.3.7 - 29 Nov 2011
  83                     ; 5 main()
  83                     ; 6 {
  85                     	switch	.text
  86  0000               _main:
  88  0000 5204          	subw	sp,#4
  89       00000004      OFST:	set	4
  92                     ; 12 	init_Ports();
  94  0002 cd0000        	call	_init_Ports
  96                     ; 14 	TIM3->ARRL =0x9;
  98  0005 3509532c      	mov	21292,#9
  99                     ; 15 	TIM3->ARRH =0xF;
 101  0009 350f532b      	mov	21291,#15
 102                     ; 16 	TIM3->PSCR =0x05;
 104  000d 3505532a      	mov	21290,#5
 105                     ; 18 	seconde = 0;
 107  0011 0f04          	clr	(OFST+0,sp)
 108                     ; 19 	TIM3->CR1 = TIM3->CR1 & !TIM3_CR1_CEN;
 110  0013 725f5320      	clr	21280
 111  0017               L34:
 112                     ; 26 	afficher_Modules_HDLX("WAIT    ");
 114  0017 ae0012        	ldw	x,#L74
 115  001a cd0000        	call	_afficher_Modules_HDLX
 117                     ; 27 	GPIOB->ODR = GPIO_PIN_0 << seconde;					
 119  001d 7b04          	ld	a,(OFST+0,sp)
 120  001f 5f            	clrw	x
 121  0020 97            	ld	xl,a
 122  0021 a601          	ld	a,#1
 123  0023 5d            	tnzw	x
 124  0024 2704          	jreq	L6
 125  0026               L01:
 126  0026 48            	sll	a
 127  0027 5a            	decw	x
 128  0028 26fc          	jrne	L01
 129  002a               L6:
 130  002a c75005        	ld	20485,a
 132  002d               L55:
 133                     ; 29 	while ((GPIOC->IDR & GPIO_PIN_2) == GPIO_PIN_2);						// attente appui sur BP3 ext
 135  002d c6500b        	ld	a,20491
 136  0030 a404          	and	a,#4
 137  0032 a104          	cp	a,#4
 138  0034 27f7          	jreq	L55
 139                     ; 31 	TIM3->CR1 = TIM3->CR1 & ~TIM3_CR1_CEN;
 141  0036 72115320      	bres	21280,#0
 142                     ; 32 	arret = 0;
 144  003a 0f02          	clr	(OFST-2,sp)
 145                     ; 33 	afficher_Modules_HDLX("CHENIL  "); 
 147  003c ae0009        	ldw	x,#L16
 148  003f cd0000        	call	_afficher_Modules_HDLX
 150                     ; 34 	GPIOB->ODR = GPIO_PIN_0 << seconde;
 152  0042 7b04          	ld	a,(OFST+0,sp)
 153  0044 5f            	clrw	x
 154  0045 97            	ld	xl,a
 155  0046 a601          	ld	a,#1
 156  0048 5d            	tnzw	x
 157  0049 2704          	jreq	L21
 158  004b               L41:
 159  004b 48            	sll	a
 160  004c 5a            	decw	x
 161  004d 26fc          	jrne	L41
 162  004f               L21:
 163  004f c75005        	ld	20485,a
 164                     ; 35 	TIM3->CR1 = TIM3->CR1 | TIM3_CR1_CEN;											//on met CEN à 1 pour démarrer le timer
 166  0052 72105320      	bset	21280,#0
 167  0056               L36:
 168                     ; 39 			var = (GPIOC->IDR & GPIO_PIN_3);
 170  0056 c6500b        	ld	a,20491
 171  0059 a408          	and	a,#8
 172  005b 6b01          	ld	(OFST-3,sp),a
 173                     ; 41 			UIF = TIM3->SR1 & TIM3_SR1_UIF;	
 175  005d c65322        	ld	a,21282
 176  0060 a401          	and	a,#1
 177  0062 6b03          	ld	(OFST-1,sp),a
 178                     ; 42 			if (UIF == 1)
 180  0064 7b03          	ld	a,(OFST-1,sp)
 181  0066 a101          	cp	a,#1
 182  0068 261c          	jrne	L56
 183                     ; 44 			seconde++;																						//on ajoute 1 à la variable seconde
 185  006a 0c04          	inc	(OFST+0,sp)
 186                     ; 45 			seconde = seconde %8;
 188  006c 7b04          	ld	a,(OFST+0,sp)
 189  006e a407          	and	a,#7
 190  0070 6b04          	ld	(OFST+0,sp),a
 191                     ; 46 			GPIOB->ODR = GPIO_PIN_0 << seconde;
 193  0072 7b04          	ld	a,(OFST+0,sp)
 194  0074 5f            	clrw	x
 195  0075 97            	ld	xl,a
 196  0076 a601          	ld	a,#1
 197  0078 5d            	tnzw	x
 198  0079 2704          	jreq	L61
 199  007b               L02:
 200  007b 48            	sll	a
 201  007c 5a            	decw	x
 202  007d 26fc          	jrne	L02
 203  007f               L61:
 204  007f c75005        	ld	20485,a
 205                     ; 47 			TIM3->SR1 = TIM3->SR1 & ~TIM3_SR1_UIF;  							// UIF à 0
 207  0082 72115322      	bres	21282,#0
 208  0086               L56:
 209                     ; 52 	while (var == GPIO_PIN_3);
 211  0086 7b01          	ld	a,(OFST-3,sp)
 212  0088 a108          	cp	a,#8
 213  008a 27ca          	jreq	L36
 214                     ; 54 	afficher_Modules_HDLX("ARRET   ");
 216  008c ae0000        	ldw	x,#L37
 217  008f cd0000        	call	_afficher_Modules_HDLX
 220  0092 2027          	jra	L77
 221  0094               L57:
 222                     ; 58 		TIM3->CR1 = TIM3->CR1 | TIM3_CR1_CEN;										//on met CEN à 1 pour démarrer le timer
 224  0094 72105320      	bset	21280,#0
 225                     ; 59 		UIF = TIM3->SR1 & TIM3_SR1_UIF;
 227  0098 c65322        	ld	a,21282
 228  009b a401          	and	a,#1
 229  009d 6b03          	ld	(OFST-1,sp),a
 230                     ; 60 		GPIOB->ODR = GPIO_PIN_0 << seconde;
 232  009f 7b04          	ld	a,(OFST+0,sp)
 233  00a1 5f            	clrw	x
 234  00a2 97            	ld	xl,a
 235  00a3 a601          	ld	a,#1
 236  00a5 5d            	tnzw	x
 237  00a6 2704          	jreq	L22
 238  00a8               L42:
 239  00a8 48            	sll	a
 240  00a9 5a            	decw	x
 241  00aa 26fc          	jrne	L42
 242  00ac               L22:
 243  00ac c75005        	ld	20485,a
 244                     ; 61 		if (UIF == 1)
 246  00af 7b03          	ld	a,(OFST-1,sp)
 247  00b1 a101          	cp	a,#1
 248  00b3 2606          	jrne	L77
 249                     ; 62 		{arret++;
 251  00b5 0c02          	inc	(OFST-2,sp)
 252                     ; 63 		TIM3->SR1 = TIM3->SR1 & ~TIM3_SR1_UIF;}
 254  00b7 72115322      	bres	21282,#0
 255  00bb               L77:
 256                     ; 56 	while (arret != 2)
 258  00bb 7b02          	ld	a,(OFST-2,sp)
 259  00bd a102          	cp	a,#2
 260  00bf 26d3          	jrne	L57
 262  00c1 ac170017      	jpf	L34
 275                     	xdef	_main
 276                     	xref	_afficher_Modules_HDLX
 277                     	xref	_init_Ports
 278                     .const:	section	.text
 279  0000               L37:
 280  0000 415252455420  	dc.b	"ARRET   ",0
 281  0009               L16:
 282  0009 4348454e494c  	dc.b	"CHENIL  ",0
 283  0012               L74:
 284  0012 574149542020  	dc.b	"WAIT    ",0
 304                     	end
