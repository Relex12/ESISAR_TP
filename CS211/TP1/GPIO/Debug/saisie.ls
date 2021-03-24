   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.10.2 - 02 Nov 2011
   3                     ; Generator (Limited) V4.3.7 - 29 Nov 2011
 109                     ; 3 main()
 109                     ; 4 {
 111                     	switch	.text
 112  0000               _main:
 114  0000 520e          	subw	sp,#14
 115       0000000e      OFST:	set	14
 118                     ; 7 	u8 var=1;
 120                     ; 10 	u8 led=0;
 122  0002 0f0b          	clr	(OFST-3,sp)
 123                     ; 12 	u8 place_tab = 0;
 125  0004 0f0c          	clr	(OFST-2,sp)
 126                     ; 14 	GPIOB->DDR = 0xFF;
 128  0006 35ff5007      	mov	20487,#255
 129                     ; 15 	GPIOC->DDR = 0x00;
 131  000a 725f500c      	clr	20492
 132                     ; 16 	GPIOB->CR1 = 0xFF;
 134  000e 35ff5008      	mov	20488,#255
 135                     ; 17 	GPIOC->CR1 = 0x00;
 137  0012 725f500d      	clr	20493
 138                     ; 18 	GPIOA->DDR = 0x78;
 140  0016 35785002      	mov	20482,#120
 141                     ; 19 	GPIOA->CR1 = 0x00;
 143  001a 725f5003      	clr	20483
 144                     ; 20 	GPIOE->DDR = 0x00;
 146  001e 725f5016      	clr	20502
 147                     ; 21 	GPIOE->CR1 = 0x80;
 149  0022 35805017      	mov	20503,#128
 150                     ; 23 	GPIOA->ODR = 0xff;
 152  0026 35ff5000      	mov	20480,#255
 153  002a               L76:
 154                     ; 26 		while ((GPIOE->IDR & GPIO_PIN_7) == GPIO_PIN_7);    
 156  002a c65015        	ld	a,20501
 157  002d a480          	and	a,#128
 158  002f a180          	cp	a,#128
 159  0031 27f7          	jreq	L76
 160                     ; 28 				var2 = (GPIOA->IDR & GPIO_PIN_1);
 162  0033 c65001        	ld	a,20481
 163  0036 a402          	and	a,#2
 164  0038 6b0e          	ld	(OFST+0,sp),a
 165                     ; 29 				var2 = var2 / 2;
 167  003a 7b0e          	ld	a,(OFST+0,sp)
 168  003c 5f            	clrw	x
 169  003d 97            	ld	xl,a
 170  003e 57            	sraw	x
 171  003f 01            	rrwa	x,a
 172  0040 6b0e          	ld	(OFST+0,sp),a
 173  0042 02            	rlwa	x,a
 174                     ; 30 				var1 = GPIOC->IDR & ~GPIO_PIN_0;
 176  0043 c6500b        	ld	a,20491
 177  0046 a4fe          	and	a,#254
 178  0048 6b0d          	ld	(OFST-1,sp),a
 179                     ; 31 				var = var1 | var2;
 181  004a 7b0d          	ld	a,(OFST-1,sp)
 182  004c 1a0e          	or	a,(OFST+0,sp)
 183  004e 6b0e          	ld	(OFST+0,sp),a
 184                     ; 32 				GPIOB->ODR = var;
 186  0050 7b0e          	ld	a,(OFST+0,sp)
 187  0052 c75005        	ld	20485,a
 188                     ; 34 				tab [place_tab] = var;
 190  0055 96            	ldw	x,sp
 191  0056 1c0001        	addw	x,#OFST-13
 192  0059 9f            	ld	a,xl
 193  005a 5e            	swapw	x
 194  005b 1b0c          	add	a,(OFST-2,sp)
 195  005d 2401          	jrnc	L6
 196  005f 5c            	incw	x
 197  0060               L6:
 198  0060 02            	rlwa	x,a
 199  0061 7b0e          	ld	a,(OFST+0,sp)
 200  0063 f7            	ld	(x),a
 201                     ; 35 				place_tab ++;
 203  0064 0c0c          	inc	(OFST-2,sp)
 204                     ; 36 				led ++;
 206  0066 0c0b          	inc	(OFST-3,sp)
 207                     ; 37 				var_led = led << 3;
 209  0068 7b0b          	ld	a,(OFST-3,sp)
 210  006a 48            	sll	a
 211  006b 48            	sll	a
 212  006c 48            	sll	a
 213  006d 6b0d          	ld	(OFST-1,sp),a
 214                     ; 38 				GPIOA->ODR = ~(var_led);
 216  006f 7b0d          	ld	a,(OFST-1,sp)
 217  0071 43            	cpl	a
 218  0072 c75000        	ld	20480,a
 220  0075               L77:
 221                     ; 40 		while ((GPIOE->IDR & GPIO_PIN_7) != GPIO_PIN_7);	
 223  0075 c65015        	ld	a,20501
 224  0078 a480          	and	a,#128
 225  007a a180          	cp	a,#128
 226  007c 26f7          	jrne	L77
 227                     ; 44 	while ((place_tab < 10) && (var != 0 ));
 229  007e 7b0c          	ld	a,(OFST-2,sp)
 230  0080 a10a          	cp	a,#10
 231  0082 2404          	jruge	L301
 233  0084 0d0e          	tnz	(OFST+0,sp)
 234  0086 26a2          	jrne	L76
 235  0088               L301:
 236                     ; 46 		GPIOB->ODR= 0xCE;
 238  0088 35ce5005      	mov	20485,#206
 239                     ; 47 }
 242  008c 5b0e          	addw	sp,#14
 243  008e 81            	ret
 256                     	xdef	_main
 275                     	end
