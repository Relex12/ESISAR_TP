   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.10.2 - 02 Nov 2011
   3                     ; Generator (Limited) V4.3.7 - 29 Nov 2011
  43                     ; 14 main()
  43                     ; 15 {
  45                     	switch	.text
  46  0000               _main:
  50                     ; 16 	GPIOB->CR1 = 0xFF;
  52  0000 35ff5008      	mov	20488,#255
  53                     ; 17 	GPIOB->DDR = 0xFF;
  55  0004 35ff5007      	mov	20487,#255
  56                     ; 18 	GPIOD->DDR = 0x01;
  58  0008 35015011      	mov	20497,#1
  59                     ; 19 	GPIOE->DDR = 0x00;
  61  000c 725f5016      	clr	20502
  62                     ; 20 	GPIOD->CR1 = 0x00;
  64  0010 725f5012      	clr	20498
  65                     ; 21 	GPIOE->CR1 = 0x80;
  67  0014 35805017      	mov	20503,#128
  68  0018               L12:
  69                     ; 24 		GPIOB->ODR = 0x00;
  71  0018 725f5005      	clr	20485
  72                     ; 25 		if ((GPIOE->IDR & GPIO_PIN_7) == GPIO_PIN_7) {
  74  001c c65015        	ld	a,20501
  75  001f a480          	and	a,#128
  76  0021 a180          	cp	a,#128
  77  0023 260e          	jrne	L52
  78                     ; 26 			GPIOD->ODR = GPIOD->ODR | 0x01;
  80  0025 7210500f      	bset	20495,#0
  81                     ; 27 			GPIOB->ODR = GPIOB->ODR | 0x60;
  83  0029 c65005        	ld	a,20485
  84  002c aa60          	or	a,#96
  85  002e c75005        	ld	20485,a
  87  0031 20e5          	jra	L12
  88  0033               L52:
  89                     ; 30 			GPIOD->ODR = GPIOD->ODR & 0xFE;
  91  0033 7211500f      	bres	20495,#0
  92                     ; 31 			GPIOB->ODR = GPIOB->ODR | 0xDA;
  94  0037 c65005        	ld	a,20485
  95  003a aada          	or	a,#218
  96  003c c75005        	ld	20485,a
  97  003f 20d7          	jra	L12
 110                     	xdef	_main
 129                     	end
