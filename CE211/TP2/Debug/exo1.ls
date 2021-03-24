   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.10.2 - 02 Nov 2011
   3                     ; Generator (Limited) V4.3.7 - 29 Nov 2011
  65                     ; 9 main()
  65                     ; 10 {
  67                     	switch	.text
  68  0000               _main:
  70  0000 89            	pushw	x
  71       00000002      OFST:	set	2
  74                     ; 14 	init_Ports();
  76  0001 cd0000        	call	_init_Ports
  78                     ; 15 	GPIOE->DDR =0x00;
  80  0004 725f5016      	clr	20502
  81                     ; 16 	GPIOE->CR1 =0x80;
  83  0008 35805017      	mov	20503,#128
  84                     ; 18 	GPIOB->DDR =0xFF;
  86  000c 35ff5007      	mov	20487,#255
  87                     ; 19 	GPIOB->CR1 =0xFF;
  89  0010 35ff5008      	mov	20488,#255
  90                     ; 21 	TIM3->ARRL =0x9;
  92  0014 3509532c      	mov	21292,#9
  93                     ; 22 	TIM3->ARRH =0xF;
  95  0018 350f532b      	mov	21291,#15
  96                     ; 23 	TIM3->PSCR =0x05;
  98  001c 3505532a      	mov	21290,#5
  99                     ; 25 	seconde = 0;
 101  0020 0f02          	clr	(OFST+0,sp)
 102                     ; 26 	TIM3->CR1 = TIM3->CR1 & !TIM3_CR1_CEN;
 104  0022 725f5320      	clr	21280
 106  0026               L73:
 107                     ; 28 	while ((GPIOE->IDR & GPIO_PIN_7) == GPIO_PIN_7); 					// attente appui sur BP2 ext
 109  0026 c65015        	ld	a,20501
 110  0029 a480          	and	a,#128
 111  002b a180          	cp	a,#128
 112  002d 27f7          	jreq	L73
 113  002f               L34:
 114                     ; 32 				TIM3->CR1 = TIM3->CR1 | TIM3_CR1_CEN;								//on met CEN à 1 pour démarrer le timer
 116  002f 72105320      	bset	21280,#0
 117  0033               L74:
 118                     ; 36 				UIF = TIM3->SR1 & TIM3_SR1_UIF;											//recupérer UIF
 120  0033 c65322        	ld	a,21282
 121  0036 a401          	and	a,#1
 122  0038 6b01          	ld	(OFST-1,sp),a
 123                     ; 38 			  while (UIF==0);
 125  003a 0d01          	tnz	(OFST-1,sp)
 126  003c 27f5          	jreq	L74
 127                     ; 41 						seconde++;																			//on ajoute 1 à la variable seconde
 129  003e 0c02          	inc	(OFST+0,sp)
 130                     ; 42 						seconde = seconde %10;
 132  0040 7b02          	ld	a,(OFST+0,sp)
 133  0042 ae000a        	ldw	x,#10
 134  0045 51            	exgw	x,y
 135  0046 5f            	clrw	x
 136  0047 97            	ld	xl,a
 137  0048 65            	divw	x,y
 138  0049 909f          	ld	a,yl
 139  004b 6b02          	ld	(OFST+0,sp),a
 140                     ; 43 						afficher_TIL321(seconde);										
 142  004d 7b02          	ld	a,(OFST+0,sp)
 143  004f cd0000        	call	_afficher_TIL321
 145                     ; 44 						TIM3->SR1 = TIM3->SR1 & !TIM3_SR1_UIF;					//on met UIF à 0
 147  0052 725f5322      	clr	21282
 149  0056 20d7          	jra	L34
 162                     	xdef	_main
 163                     	xref	_afficher_TIL321
 164                     	xref	_init_Ports
 183                     	end
