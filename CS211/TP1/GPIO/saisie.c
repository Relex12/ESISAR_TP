#include <stm8s.h>

main()
{
	u8 var1;
	u8 var2;
	u8 var=1;
	u8 var_principale;
	u8 tab [10];
	u8 led=0;
	u8 var_led;
	u8 place_tab = 0;
	
	GPIOB->DDR = 0xFF;
	GPIOC->DDR = 0x00;
	GPIOB->CR1 = 0xFF;
	GPIOC->CR1 = 0x00;
	GPIOA->DDR = 0x78;
	GPIOA->CR1 = 0x00;
	GPIOE->DDR = 0x00;
	GPIOE->CR1 = 0x80;
	
	GPIOA->ODR = 0xff;
	do {
		
		while ((GPIOE->IDR & GPIO_PIN_7) == GPIO_PIN_7);    
			
				var2 = (GPIOA->IDR & GPIO_PIN_1);
				var2 = var2 / 2;
				var1 = GPIOC->IDR & ~GPIO_PIN_0;
				var = var1 | var2;
				GPIOB->ODR = var;
		
				tab [place_tab] = var;
				place_tab ++;
				led ++;
				var_led = led << 3;
				GPIOA->ODR = ~(var_led);
		
		while ((GPIOE->IDR & GPIO_PIN_7) != GPIO_PIN_7);	
	
	}
	
	while ((place_tab < 10) && (var != 0 ));
			
		GPIOB->ODR= 0xCE;
}

	
	
	
	
	
	
	
	
	
	
	
	
	
