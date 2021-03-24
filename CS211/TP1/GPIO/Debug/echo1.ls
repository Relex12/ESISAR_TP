   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.10.2 - 02 Nov 2011
   3                     ; Generator (Limited) V4.3.7 - 29 Nov 2011
  72                     ; 9 main()
  72                     ; 10 	{
  74                     	switch	.text
  75  0000               _main:
  77  0000 89            	pushw	x
  78       00000002      OFST:	set	2
  81                     ; 14 	GPIOB->DDR = 0xFF;
  83  0001 35ff5007      	mov	20487,#255
  84                     ; 15 	GPIOC->DDR = 0x00;
  86  0005 725f500c      	clr	20492
  87                     ; 16 	GPIOB->CR1 = 0xFF;
  89  0009 35ff5008      	mov	20488,#255
  90                     ; 17 	GPIOC->CR1 = 0x00;
  92  000d 725f500d      	clr	20493
  93                     ; 18 	GPIOA->DDR = 0x00;
  95  0011 725f5002      	clr	20482
  96                     ; 19 	GPIOA->CR1 = 0x00;
  98  0015 725f5003      	clr	20483
  99  0019               L73:
 100                     ; 23 		var2 = (GPIOA->IDR & GPIO_PIN_1);
 102  0019 c65001        	ld	a,20481
 103  001c a402          	and	a,#2
 104  001e 6b02          	ld	(OFST+0,sp),a
 105                     ; 24 		var2 = var2 / 2;
 107  0020 7b02          	ld	a,(OFST+0,sp)
 108  0022 5f            	clrw	x
 109  0023 97            	ld	xl,a
 110  0024 57            	sraw	x
 111  0025 01            	rrwa	x,a
 112  0026 6b02          	ld	(OFST+0,sp),a
 113  0028 02            	rlwa	x,a
 114                     ; 25 		var1 = GPIOC->IDR & ~GPIO_PIN_0;
 116  0029 c6500b        	ld	a,20491
 117  002c a4fe          	and	a,#254
 118  002e 6b01          	ld	(OFST-1,sp),a
 119                     ; 26 		var = var1 | var2;
 121  0030 7b01          	ld	a,(OFST-1,sp)
 122  0032 1a02          	or	a,(OFST+0,sp)
 123  0034 6b02          	ld	(OFST+0,sp),a
 124                     ; 27 		GPIOB->ODR = var;
 126  0036 7b02          	ld	a,(OFST+0,sp)
 127  0038 c75005        	ld	20485,a
 129  003b 20dc          	jra	L73
 142                     	xdef	_main
 161                     	end
