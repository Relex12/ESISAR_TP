   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.10.2 - 02 Nov 2011
   3                     ; Generator (Limited) V4.3.7 - 29 Nov 2011
  81                     ; 6 main()
  81                     ; 7 	{
  83                     	switch	.text
  84  0000               _main:
  86  0000 89            	pushw	x
  87       00000002      OFST:	set	2
  90                     ; 12 	GPIOB->DDR = 0xFF;
  92  0001 35ff5007      	mov	20487,#255
  93                     ; 13 	GPIOC->DDR = 0x00;
  95  0005 725f500c      	clr	20492
  96                     ; 14 	GPIOB->CR1 = 0xFF;
  98  0009 35ff5008      	mov	20488,#255
  99                     ; 15 	GPIOC->CR1 = 0x00;
 101  000d 725f500d      	clr	20493
 102                     ; 16 	GPIOA->DDR = 0x00;
 104  0011 725f5002      	clr	20482
 105                     ; 17 	GPIOA->CR1 = 0x00;
 107  0015 725f5003      	clr	20483
 108                     ; 18 	GPIOE->DDR = 0x00;
 110  0019 725f5016      	clr	20502
 111                     ; 19 	GPIOE->CR1 = 0x01;
 113  001d 35015017      	mov	20503,#1
 114  0021               L34:
 115                     ; 23 		btn = (GPIOE->IDR & GPIO_PIN_0);
 117  0021 c65015        	ld	a,20501
 118  0024 a401          	and	a,#1
 119  0026 6b01          	ld	(OFST-1,sp),a
 120                     ; 24 		if (btn != GPIO_PIN_0){
 122  0028 7b01          	ld	a,(OFST-1,sp)
 123  002a a101          	cp	a,#1
 124  002c 2724          	jreq	L74
 125                     ; 25 			var2 = (GPIOA->IDR & GPIO_PIN_1);
 127  002e c65001        	ld	a,20481
 128  0031 a402          	and	a,#2
 129  0033 6b02          	ld	(OFST+0,sp),a
 130                     ; 26 			var2 = var2 / 2;
 132  0035 7b02          	ld	a,(OFST+0,sp)
 133  0037 5f            	clrw	x
 134  0038 97            	ld	xl,a
 135  0039 57            	sraw	x
 136  003a 01            	rrwa	x,a
 137  003b 6b02          	ld	(OFST+0,sp),a
 138  003d 02            	rlwa	x,a
 139                     ; 27 			var1 = GPIOC->IDR & ~GPIO_PIN_0;
 141  003e c6500b        	ld	a,20491
 142  0041 a4fe          	and	a,#254
 143  0043 6b01          	ld	(OFST-1,sp),a
 144                     ; 28 			var = var1 | var2;
 146  0045 7b01          	ld	a,(OFST-1,sp)
 147  0047 1a02          	or	a,(OFST+0,sp)
 148  0049 6b02          	ld	(OFST+0,sp),a
 149                     ; 29 			GPIOB->ODR = var;
 151  004b 7b02          	ld	a,(OFST+0,sp)
 152  004d c75005        	ld	20485,a
 154  0050 20cf          	jra	L34
 155  0052               L74:
 156                     ; 32 			var2 = (GPIOA->IDR & GPIO_PIN_1);
 158  0052 c65001        	ld	a,20481
 159  0055 a402          	and	a,#2
 160  0057 6b02          	ld	(OFST+0,sp),a
 161                     ; 33 			var2 = var2 / 2;
 163  0059 7b02          	ld	a,(OFST+0,sp)
 164  005b 5f            	clrw	x
 165  005c 97            	ld	xl,a
 166  005d 57            	sraw	x
 167  005e 01            	rrwa	x,a
 168  005f 6b02          	ld	(OFST+0,sp),a
 169  0061 02            	rlwa	x,a
 170                     ; 34 			var1 = GPIOC->IDR & ~GPIO_PIN_0;
 172  0062 c6500b        	ld	a,20491
 173  0065 a4fe          	and	a,#254
 174  0067 6b01          	ld	(OFST-1,sp),a
 175                     ; 35 			var = var1 | var2;
 177  0069 7b01          	ld	a,(OFST-1,sp)
 178  006b 1a02          	or	a,(OFST+0,sp)
 179  006d 6b02          	ld	(OFST+0,sp),a
 180                     ; 36 			GPIOB->ODR = ~var;
 182  006f 7b02          	ld	a,(OFST+0,sp)
 183  0071 43            	cpl	a
 184  0072 c75005        	ld	20485,a
 185  0075 20aa          	jra	L34
 198                     	xdef	_main
 217                     	end
