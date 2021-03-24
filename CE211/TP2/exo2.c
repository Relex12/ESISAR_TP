#include <stm8s.h>
#include <carte_accueil_tp.h>
#include <fonctions_tp_utiles.h>

main()
{
	u8 UIF;
	u8 seconde;
	u8 var;
	u8 arret;
	
	init_Ports();
	
	TIM3->ARRL =0x9;
	TIM3->ARRH =0xF;
	TIM3->PSCR =0x05;
	
	seconde = 0;
	TIM3->CR1 = TIM3->CR1 & !TIM3_CR1_CEN;


	while (1) 

{
	
	afficher_Modules_HDLX("WAIT    ");
	GPIOB->ODR = GPIO_PIN_0 << seconde;					
	
	while ((GPIOC->IDR & GPIO_PIN_2) == GPIO_PIN_2);						// attente appui sur BP3 ext
	
	TIM3->CR1 = TIM3->CR1 & ~TIM3_CR1_CEN;
	arret = 0;
	afficher_Modules_HDLX("CHENIL  "); 
	GPIOB->ODR = GPIO_PIN_0 << seconde;
	TIM3->CR1 = TIM3->CR1 | TIM3_CR1_CEN;											//on met CEN à 1 pour démarrer le timer
	
	do
		{	
			var = (GPIOC->IDR & GPIO_PIN_3);
	
			UIF = TIM3->SR1 & TIM3_SR1_UIF;	
			if (UIF == 1)
			{
			seconde++;																						//on ajoute 1 à la variable seconde
			seconde = seconde %8;
			GPIOB->ODR = GPIO_PIN_0 << seconde;
			TIM3->SR1 = TIM3->SR1 & ~TIM3_SR1_UIF;  							// UIF à 0
			}

		}
		
	while (var == GPIO_PIN_3);
	
	afficher_Modules_HDLX("ARRET   ");
	
	while (arret != 2)
	{
		TIM3->CR1 = TIM3->CR1 | TIM3_CR1_CEN;										//on met CEN à 1 pour démarrer le timer
		UIF = TIM3->SR1 & TIM3_SR1_UIF;
		GPIOB->ODR = GPIO_PIN_0 << seconde;
		if (UIF == 1)
		{arret++;
		TIM3->SR1 = TIM3->SR1 & ~TIM3_SR1_UIF;}
	}
		
}
	var = 0;
}