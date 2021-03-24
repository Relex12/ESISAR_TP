   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.10.2 - 02 Nov 2011
   3                     ; Generator (Limited) V4.3.7 - 29 Nov 2011
  15                     .const:	section	.text
  16  0000               L3_tableau:
  17  0000 20            	dc.b	32
  18  0001 20            	dc.b	32
  19  0002 20            	dc.b	32
  20  0003 20            	dc.b	32
  21  0004 20            	dc.b	32
  22  0005 20            	dc.b	32
  23  0006 20            	dc.b	32
  24  0007 20            	dc.b	32
 105                     ; 5 main()
 105                     ; 6 {
 107                     	switch	.text
 108  0000               _main:
 110  0000 520d          	subw	sp,#13
 111       0000000d      OFST:	set	13
 114                     ; 10 	u8 tableau[8]={' ',' ',' ',' ',' ',' ',' ',' '};
 116  0002 96            	ldw	x,sp
 117  0003 1c0005        	addw	x,#OFST-8
 118  0006 90ae0000      	ldw	y,#L3_tableau
 119  000a a608          	ld	a,#8
 120  000c cd0000        	call	c_xymvx
 122                     ; 13 	init_Ports();
 124  000f cd0000        	call	_init_Ports
 126                     ; 15 	TIM3->ARRL =0xc3;
 128  0012 35c3532c      	mov	21292,#195
 129                     ; 16 	TIM3->ARRH =0x50;
 131  0016 3550532b      	mov	21291,#80
 132                     ; 17 	TIM3->PSCR =0x02;
 134  001a 3502532a      	mov	21290,#2
 135                     ; 19 	mili_seconde = 0;
 137  001e 0f0d          	clr	(OFST+0,sp)
 138                     ; 20 	TIM3->CR1 = TIM3->CR1 & !TIM3_CR1_CEN;
 140  0020 725f5320      	clr	21280
 141  0024               L15:
 142                     ; 25 	afficher_Modules_HDLX(tableau);
 144  0024 96            	ldw	x,sp
 145  0025 1c0005        	addw	x,#OFST-8
 146  0028 cd0000        	call	_afficher_Modules_HDLX
 149  002b 2023          	jra	L75
 150  002d               L55:
 151                     ; 29 		if ((GPIOC->IDR & GPIO_PIN_2) != GPIO_PIN_2)						//Pour remettre le chrono à 0
 153  002d c6500b        	ld	a,20491
 154  0030 a404          	and	a,#4
 155  0032 a104          	cp	a,#4
 156  0034 271a          	jreq	L75
 157                     ; 31 			mili_seconde=0;
 159  0036 0f0d          	clr	(OFST+0,sp)
 160                     ; 32 			valeur_BCD = Bin_BCD(mili_seconde);
 162  0038 4f            	clr	a
 163  0039 cd0000        	call	_Bin_BCD
 165  003c 1f03          	ldw	(OFST-10,sp),x
 166                     ; 33 			conv1_BCD_ASCII(valeur_BCD, tableau);
 168  003e 96            	ldw	x,sp
 169  003f 1c0005        	addw	x,#OFST-8
 170  0042 89            	pushw	x
 171  0043 1e05          	ldw	x,(OFST-8,sp)
 172  0045 cd0000        	call	_conv1_BCD_ASCII
 174  0048 85            	popw	x
 175                     ; 34 			afficher_Modules_HDLX(tableau);
 177  0049 96            	ldw	x,sp
 178  004a 1c0005        	addw	x,#OFST-8
 179  004d cd0000        	call	_afficher_Modules_HDLX
 181  0050               L75:
 182                     ; 27 	while ((GPIOC->IDR & GPIO_PIN_4) == GPIO_PIN_4)
 184  0050 c6500b        	ld	a,20491
 185  0053 a410          	and	a,#16
 186  0055 a110          	cp	a,#16
 187  0057 27d4          	jreq	L55
 188                     ; 38 	TIM3->CR1 = TIM3->CR1 & ~TIM3_CR1_CEN; 
 190  0059 72115320      	bres	21280,#0
 191  005d               L56:
 192                     ; 42 			TIM3->CR1 = TIM3->CR1 | TIM3_CR1_CEN;	
 194  005d 72105320      	bset	21280,#0
 195                     ; 43 			var = (GPIOC->IDR & GPIO_PIN_1);
 197  0061 c6500b        	ld	a,20491
 198  0064 a402          	and	a,#2
 199  0066 6b02          	ld	(OFST-11,sp),a
 200                     ; 44 			bit_uif = TIM3->SR1 & TIM3_SR1_UIF;
 202  0068 c65322        	ld	a,21282
 203  006b a401          	and	a,#1
 204  006d 6b01          	ld	(OFST-12,sp),a
 205                     ; 45 			if (bit_uif == 1)
 207  006f 7b01          	ld	a,(OFST-12,sp)
 208  0071 a101          	cp	a,#1
 209  0073 2613          	jrne	L37
 210                     ; 47 				mili_seconde++;																			//on ajoute 1 à la variable mili_seconde
 212  0075 0c0d          	inc	(OFST+0,sp)
 213                     ; 48 				mili_seconde = mili_seconde %255;
 215  0077 7b0d          	ld	a,(OFST+0,sp)
 216  0079 ae00ff        	ldw	x,#255
 217  007c 51            	exgw	x,y
 218  007d 5f            	clrw	x
 219  007e 97            	ld	xl,a
 220  007f 65            	divw	x,y
 221  0080 909f          	ld	a,yl
 222  0082 6b0d          	ld	(OFST+0,sp),a
 223                     ; 49 				TIM3->SR1 = TIM3->SR1 & ~TIM3_SR1_UIF;
 225  0084 72115322      	bres	21282,#0
 226  0088               L37:
 227                     ; 52 			valeur_BCD = Bin_BCD(mili_seconde);
 229  0088 7b0d          	ld	a,(OFST+0,sp)
 230  008a cd0000        	call	_Bin_BCD
 232  008d 1f03          	ldw	(OFST-10,sp),x
 233                     ; 53 			conv1_BCD_ASCII(valeur_BCD, tableau);
 235  008f 96            	ldw	x,sp
 236  0090 1c0005        	addw	x,#OFST-8
 237  0093 89            	pushw	x
 238  0094 1e05          	ldw	x,(OFST-8,sp)
 239  0096 cd0000        	call	_conv1_BCD_ASCII
 241  0099 85            	popw	x
 242                     ; 55 			afficher_Modules_HDLX(tableau);
 244  009a 96            	ldw	x,sp
 245  009b 1c0005        	addw	x,#OFST-8
 246  009e cd0000        	call	_afficher_Modules_HDLX
 248                     ; 58 	while (var == GPIO_PIN_1);
 250  00a1 7b02          	ld	a,(OFST-11,sp)
 251  00a3 a102          	cp	a,#2
 252  00a5 27b6          	jreq	L56
 254  00a7 cc0024        	jra	L15
 267                     	xdef	_main
 268                     	xref	_Bin_BCD
 269                     	xref	_conv1_BCD_ASCII
 270                     	xref	_afficher_Modules_HDLX
 271                     	xref	_init_Ports
 272                     	xref.b	c_x
 291                     	xref	c_xymvx
 292                     	end
