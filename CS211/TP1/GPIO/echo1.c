

#include <stm8s.h>
 


main()
	{
	u8 var1;
	u8 var2;
	u8 var;
	GPIOB->DDR = 0xFF;
	GPIOC->DDR = 0x00;
	GPIOB->CR1 = 0xFF;
	GPIOC->CR1 = 0x00;
	GPIOA->DDR = 0x00;
	GPIOA->CR1 = 0x00;
	
		
	while (1){
		var2 = (GPIOA->IDR & GPIO_PIN_1);
		var2 = var2 / 2;
		var1 = GPIOC->IDR & ~GPIO_PIN_0;
		var = var1 | var2;
		GPIOB->ODR = var;
}
}


