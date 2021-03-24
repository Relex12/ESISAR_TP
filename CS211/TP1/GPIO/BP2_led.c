

#include <stm8s.h>


main()
{
	GPIOB->CR1 = 0xFF;
	GPIOB->DDR = 0xFF;
	GPIOD->DDR = 0x01;
	GPIOE->DDR = 0x00;
	GPIOD->CR1 = 0x00;
	GPIOE->CR1 = 0x80;
	
	while(1){
		GPIOB->ODR = 0x00;
		if ((GPIOE->IDR & GPIO_PIN_7) == GPIO_PIN_7) {
			GPIOD->ODR = GPIOD->ODR | 0x01;
			GPIOB->ODR = GPIOB->ODR | 0x60;
		}
		else {
			GPIOD->ODR = GPIOD->ODR & 0xFE;
			GPIOB->ODR = GPIOB->ODR | 0xDA;
		}
}

}