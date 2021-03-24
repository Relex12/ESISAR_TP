#include <stm8s.h>
#include <carte_accueil_tp.h>
#include <fonctions_tp_utiles.h>

main()
{
	u8 bit_uif;
	u8 mili_seconde;
	u16 valeur_BCD;
	u8 tableau[8]={' ',' ',' ',' ',' ',' ',' ',' '};
	u8 var;
	
	init_Ports();
	
	TIM3->ARRL =0xc3;
	TIM3->ARRH =0x50;
	TIM3->PSCR =0x02;
	
	mili_seconde = 0;
	TIM3->CR1 = TIM3->CR1 & !TIM3_CR1_CEN;


	while (1) 
{
	afficher_Modules_HDLX(tableau);
	
	while ((GPIOC->IDR & GPIO_PIN_4) == GPIO_PIN_4)
	{
		if ((GPIOC->IDR & GPIO_PIN_2) != GPIO_PIN_2)						//Pour remettre le chrono à 0
			{
			mili_seconde=0;
			valeur_BCD = Bin_BCD(mili_seconde);
			conv1_BCD_ASCII(valeur_BCD, tableau);
			afficher_Modules_HDLX(tableau);
			}
	}
	
	TIM3->CR1 = TIM3->CR1 & ~TIM3_CR1_CEN; 

	do
		{	
			TIM3->CR1 = TIM3->CR1 | TIM3_CR1_CEN;	
			var = (GPIOC->IDR & GPIO_PIN_1);
			bit_uif = TIM3->SR1 & TIM3_SR1_UIF;
			if (bit_uif == 1)
				{
				mili_seconde++;																			//on ajoute 1 à la variable mili_seconde
				mili_seconde = mili_seconde %255;
				TIM3->SR1 = TIM3->SR1 & ~TIM3_SR1_UIF;
				}
			
			valeur_BCD = Bin_BCD(mili_seconde);
			conv1_BCD_ASCII(valeur_BCD, tableau);
			
			afficher_Modules_HDLX(tableau);
		}
		
	while (var == GPIO_PIN_1);
}
}
