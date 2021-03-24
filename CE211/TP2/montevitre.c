#include <stm8s.h>
#include <carte_accueil_tp.h>
#include <fonctions_tp_utiles.h>

main()
{
	u8 bit_uif3;
	u8 bit_uif2;
	u8 temps;
	u8 capteur_haut;
	u8 capteur_bas;
	u8 affichage;
	
	init_Ports();
	
	//Initialisation du timer 3
	TIM3->ARRL =0x9;
	TIM3->ARRH =0xF;
	TIM3->PSCR =0x04;
	
	//Initialisation du timer 4
	TIM2->ARRL =0x9;
	TIM2->ARRH =0xF;
	TIM2->PSCR =0x05;
	
	
	temps = 0;
	GPIOB->ODR = GPIO_PIN_0 << temps;			//emplacement de la fenêtre
	
while (1)
{
	afficher_Modules_HDLX("ARRET :)");
	GPIOB->ODR= 0;

	if ((((GPIOC->IDR & GPIO_PIN_2) != GPIO_PIN_2)&(GPIOC->IDR & GPIO_PIN_7) == GPIO_PIN_7)) 	//BT3 appuyé on rentre dans la if
		{
			afficher_Modules_HDLX("MONTEE  ");
			temps = (8 - temps) %8;
			TIM3->CR1 = TIM3->CR1 | TIM3_CR1_CEN;	
			TIM2->CR1 = TIM2->CR1 | TIM2_CR1_CEN;	
			bit_uif2 = TIM2->SR1 & TIM2_SR1_UIF;
			bit_uif3 = TIM3->SR1 & TIM3_SR1_UIF;
			
			while ((bit_uif2==0) & ((GPIOC->IDR & GPIO_PIN_7) == GPIO_PIN_7)) //attendre 1 seconde et si fin de course alors on sort du if
				{
					bit_uif2 = TIM2->SR1 & TIM2_SR1_UIF;
					bit_uif3 = TIM3->SR1 & TIM3_SR1_UIF;	
					if (bit_uif3 == 1)
					{
					temps++;																						//on ajoute 1 à la variable seconde
					temps = temps %8;
					GPIOB->ODR = GPIO_PIN_0 << temps;
					affichage = GPIOB->ODR;
					TIM3->SR1 = TIM3->SR1 & ~TIM3_SR1_UIF;  							// UIF à 0
					}
				}
			TIM2->SR1 = TIM2->SR1 & ~TIM2_SR1_UIF;
			TIM2->CR1 = TIM2->CR1 & ~TIM2_CR1_CEN;	
			
			if (((GPIOC->IDR & GPIO_PIN_2) != GPIO_PIN_2) & ((GPIOC->IDR & GPIO_PIN_7) == GPIO_PIN_7))
				{
				while (((GPIOC->IDR & GPIO_PIN_2) != GPIO_PIN_2)&((GPIOC->IDR & GPIO_PIN_7) == GPIO_PIN_7))
					{
						bit_uif3 = TIM3->SR1 & TIM3_SR1_UIF;	
						if (bit_uif3 == 1)
						{
						temps++;																						//on ajoute 1 à la variable seconde
						temps = temps %8;
						GPIOB->ODR = GPIO_PIN_0 << temps;
						affichage = GPIOB->ODR;
						TIM3->SR1 = TIM3->SR1 & ~TIM3_SR1_UIF;  							// UIF à 0
						}
					}
				}
			else
				{
				while ((GPIOC->IDR & GPIO_PIN_7) == GPIO_PIN_7)
					{
						bit_uif3 = TIM3->SR1 & TIM3_SR1_UIF;	
						if (bit_uif3 == 1)
						{
						temps++;																						//on ajoute 1 à la variable seconde
						temps = temps %8;
						GPIOB->ODR = GPIO_PIN_0 << temps;
						affichage = GPIOB->ODR;
						TIM3->SR1 = TIM3->SR1 & ~TIM3_SR1_UIF;  							// UIF à 0
						}
					}
				}	
		}
	



	if ((((GPIOC->IDR & GPIO_PIN_3) != GPIO_PIN_3)&(GPIOC->IDR & GPIO_PIN_4) == GPIO_PIN_4)) 	//BT3 appuyé on rentre dans la if
		{
			afficher_Modules_HDLX("DESCENTE");
			temps = (8 - temps) %8;
			TIM3->CR1 = TIM3->CR1 | TIM3_CR1_CEN;	
			TIM2->CR1 = TIM2->CR1 | TIM2_CR1_CEN;	
			bit_uif2 = TIM2->SR1 & TIM2_SR1_UIF;
			bit_uif3 = TIM3->SR1 & TIM3_SR1_UIF;
			
			while ((bit_uif2==0) & ((GPIOC->IDR & GPIO_PIN_4) == GPIO_PIN_4)) //attendre 1 seconde et si fin de course alors on sort du if
				{
					bit_uif2 = TIM2->SR1 & TIM2_SR1_UIF;
					bit_uif3 = TIM3->SR1 & TIM3_SR1_UIF;	
					if (bit_uif3 == 1)
					{
					temps++;																						//on ajoute 1 à la variable seconde
					temps = temps %8;
					GPIOB->ODR = GPIO_PIN_7 >> temps;
					affichage = GPIOB->ODR;
					TIM3->SR1 = TIM3->SR1 & ~TIM3_SR1_UIF;  							// UIF à 0
					}
				}
			TIM2->SR1 = TIM2->SR1 & ~TIM2_SR1_UIF;
			TIM2->CR1 = TIM2->CR1 & ~TIM2_CR1_CEN;	
			
			if (((GPIOC->IDR & GPIO_PIN_3) != GPIO_PIN_3) & ((GPIOC->IDR & GPIO_PIN_4) == GPIO_PIN_4))
				{
				while (((GPIOC->IDR & GPIO_PIN_3) != GPIO_PIN_3)&((GPIOC->IDR & GPIO_PIN_4) == GPIO_PIN_4))
					{
						bit_uif3 = TIM3->SR1 & TIM3_SR1_UIF;	
						if (bit_uif3 == 1)
						{
						temps++;																						//on ajoute 1 à la variable seconde
						temps = temps %8;
						GPIOB->ODR = GPIO_PIN_7 >> temps;
						affichage = GPIOB->ODR;
						TIM3->SR1 = TIM3->SR1 & ~TIM3_SR1_UIF;  							// UIF à 0
						}
					}
				}
			else
				{
				while ((GPIOC->IDR & GPIO_PIN_4) == GPIO_PIN_4)
					{
						bit_uif3 = TIM3->SR1 & TIM3_SR1_UIF;	
						if (bit_uif3 == 1)
						{
						temps++;																						//on ajoute 1 à la variable seconde
						temps = temps %8;
						GPIOB->ODR = GPIO_PIN_7 >> temps;
						affichage = GPIOB->ODR;
						TIM3->SR1 = TIM3->SR1 & ~TIM3_SR1_UIF;  							// UIF à 0
						}
					}
				}	
		}
	}
}	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
