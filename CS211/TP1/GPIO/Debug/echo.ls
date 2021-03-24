   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.10.2 - 02 Nov 2011
   3                     ; Generator (Limited) V4.3.7 - 29 Nov 2011
  54                     ; 11 main()
  54                     ; 12 	{
  56                     	switch	.text
  57  0000               _main:
  59  0000 88            	push	a
  60       00000001      OFST:	set	1
  63                     ; 14 	GPIOB->DDR = 0xFF;
  65  0001 35ff5007      	mov	20487,#255
  66                     ; 15 	GPIOC->DDR = 0x0;
  68  0005 725f500c      	clr	20492
  69                     ; 16 	GPIOB->CR1 = 0xFF;
  71  0009 35ff5008      	mov	20488,#255
  72                     ; 17 	GPIOC->CR1 = 0x0;
  74  000d 725f500d      	clr	20493
  75  0011               L72:
  76                     ; 21 		var = GPIOC->IDR;
  78  0011 c6500b        	ld	a,20491
  79  0014 6b01          	ld	(OFST+0,sp),a
  80                     ; 22 		GPIOB->ODR = var;
  82  0016 7b01          	ld	a,(OFST+0,sp)
  83  0018 c75005        	ld	20485,a
  85  001b 20f4          	jra	L72
  98                     	xdef	_main
 117                     	end
