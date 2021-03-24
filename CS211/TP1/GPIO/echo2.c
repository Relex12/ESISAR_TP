

#include "stm8s.h"
main()
	{
	u8 var1;
	u8 var2;
	u8 var;
	u8 btn;
	GPIOB->DDR = 0xFF;
	GPIOC->DDR = 0x00;
	GPIOB->CR1 = 0xFF;
	GPIOC->CR1 = 0x00;
	GPIOA->DDR = 0x00;
	GPIOA->CR1 = 0x00;
	GPIOE->DDR = 0x00;
	GPIOE->CR1 = 0x01;
	
		
	while (1){
		btn = (GPIOE->IDR & GPIO_PIN_0);
		if (btn != GPIO_PIN_0){
			var2 = (GPIOA->IDR & GPIO_PIN_1);
			var2 = var2 / 2;
			var1 = GPIOC->IDR & ~GPIO_PIN_0;
			var = var1 | var2;
			GPIOB->ODR = var;
		}
		else {
			var2 = (GPIOA->IDR & GPIO_PIN_1);
			var2 = var2 / 2;
			var1 = GPIOC->IDR & ~GPIO_PIN_0;
			var = var1 | var2;
			GPIOB->ODR = ~var;
}
}
}