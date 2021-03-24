/* fonctions_TP_utiles.c file
  *
  *  Developpement STM8
  *  Cible : Discovery STM8  - carte accueil pour TP
  *  
  *  Creation : 22 juillet 2016
  *  dernière réactualisation : 23 aout 2017
  *  rien à ce jour concernant les échanges série via UART2
  * décembre 2017 : version pour élèves 2A
  *
  *       fonction init_Ports(void) ajoutée le 31 aout 2017

  *       fonctions concernant les modules HDLX  (9)
 
  *       fonction u8 afficher_TIL321(u8 valeur)
  *
  *       fonction u8 lire_Etat_BP1(void)
  *       fonction u8 lire_Etat_BP2(void)
  *
  *       fonctions de conversion :  (4 + 1)
  *       void conv_Bin_ASCII(u8 valeur_binaire, u8 *adresse)
  *       u16 Ajustement_BCD(u8 valeur, u8 valeur_pre)
  *       u8 Bin_BCD (u8 valeur)
  */

#include "stm8s.h"
#include "carte_accueil_tp.h"
#include "fonctions_TP_utiles.h"


// initialisations nécessaires pour l'ensemble des 6 ports du STM8S105C6
// en fonction des éléments physques présents sur la carte d'accueil
// dernière actualisation: 12 décembre 2016

void init_Ports(void) // inséré le 31 aout 2017
 {
     GPIOA->DDR = PORT_A_DIRECTION; // lignes 3 à 6 en sortie
     GPIOA->CR1 = PORT_A_TECHNO_LIGNES; // open drain
     GPIOA->ODR = 0x78;  // extinction 4 leds	rouges

     GPIOB->DDR = PORT_B_DIRECTION; // 8 lignes en sortie
     GPIOB->CR1 = PORT_B_TECHNO_LIGNES; // 8 lignes en push pull
     GPIOB->ODR = 0x0; // extinction afficheur TIL321

     GPIOC->DDR = PORT_C_DIRECTION; // 7 lignes en entrée
     GPIOC->CR1 = PORT_C_TECHNO_LIGNES; // 7 lignes en pull up 

     GPIOD->DDR = PORT_D_DIRECTION;  // ligne 0 en sortie pour led verte
     GPIOD->CR1 = PORT_D_TECHNO_LIGNES; // ligne 7 en pull up pour BP1 extérieur
		                                   // ligne 0 en open dran pour led verte
     GPIOD->ODR = GPIO_PIN_0; // extinction led verte

     GPIOE->DDR = PORT_E_DIRECTION;  // 2 signaux WR pour HDLX
     GPIOE->CR1 = PORT_E_TECHNO_LIGNES;  // ligne 7 en pull up pour BP2 extérieur

     GPIOG->DDR = PORT_G_DIRECTION;  // sortie pour signaux A0 et A1
     GPIOG->CR1 = PORT_G_TECHNO_LIGNES; // push pull

     GPIOD->ODR = HDLX_NBL;  // pas Blanking
     GPIOE->ODR = HDLX_NWR1 + HDLX_NWR2; // 2 signaux /WR au repos
 }

// retourne la valeur ACTIF si le BP extérieur 2
// est appuyé.  Sinon il retourne NON_ACTIF
u8 lire_Etat_BP2(void)
{
	u8 valeur = NON_ACTIF;
		if ( GPIO_PIN_7 != (GPIOE->IDR & GPIO_PIN_7 ))
		/* test etat logique de ligne 7 Port E */
		valeur = ACTIF;
		return valeur;
}

// retourne la valeur ACTIF si le BP extérieur 1
// est appuyé. Sinon il retourne NON_ACTIF
u8 lire_Etat_BP1(void)
{
	u8 valeur = NON_ACTIF;
		if ( GPIO_PIN_7 != (GPIOD->IDR & GPIO_PIN_7 ))
		/* test etat logique de ligne 7 Port D */
		valeur = ACTIF;
		return valeur;
}


// affiche sur TIL321 le chiffre codé en BCD passé en paramètre.
// affiche E si valeur non BCD

u8 afficher_TIL321(u8 valeur)
{
	if( valeur < 0 || valeur > 9)
		{
			GPIOB->ODR = LETTRE_E;
			/*  valeur non BCD */
			return -1;
		}
	else
		{
		switch (valeur)
		{
			case 0 :
			GPIOB->ODR = ZERO;
			break;
			case 1 :
			GPIOB->ODR = UN;
			break;
			case 2 :
			GPIOB->ODR = DEUX;
			break;
			case 3 :
			GPIOB->ODR = TROIS;
			break;
			case 4 :
			GPIOB->ODR = QUATRE;
			break;
			case 5 :
			GPIOB->ODR = CINQ;
			break;
			case 6 :
			GPIOB->ODR = SIX;
			break;
			case 7 :
			GPIOB->ODR = SEPT;
			break;
			case 8 :
			GPIOB->ODR = HUIT;
			break;
			case 9 :
			GPIOB->ODR = NEUF;
			break;
		}
		return 1;
	}
}

// affiche le caractère dont le code ASCII est passé en paramètre
// sur le digit du module HDLH1 dont le numéro est passé en paramètre	
void afficher_Digit_HDLX1(u8 numero, u8 caractere)
{
GPIOB->ODR = caractere + DISPLAY_ASCII; // MSB = 1 pour ASCII
GPIOG->ODR = numero ; //  numero digit
GPIOE->ODR = GPIOE->ODR & ~HDLX_NWR1; // activation WR1
GPIOE->ODR = GPIOE->ODR | HDLX_NWR1; // deactivation WR1
}

// affiche le caractère dont le code ASCII est passé en paramètre
// sur le digit du module HDLH2 dont le numéro est passé en paramètre	
void afficher_Digit_HDLX2(u8 numero, u8 caractere)
{
GPIOB->ODR = caractere + DISPLAY_ASCII; // MSB = 1 pour ASCII
GPIOG->ODR = numero ; //  numero digit
GPIOE->ODR = GPIOE->ODR & ~HDLX_NWR2; // activation WR2
GPIOE->ODR = GPIOE->ODR | HDLX_NWR2; // deactivation WR2
}

// mettre dans le registre de contrôle du digit du module HDLX1 passé en paramètre
// la valeur  passée en paramètre
void ecrire_Registre_Controle_Digit_HDLX1(u8 numero, u8 valeur)
{
GPIOB->ODR = valeur ; // MSB = 0 pour controle
GPIOG->ODR = numero ; //  numero digit
GPIOE->ODR = GPIOE->ODR & ~HDLX_NWR1; // activation WR1
GPIOE->ODR = GPIOE->ODR | HDLX_NWR1; // deactivation WR1
}

// mettre dans le registre de contrôle du digit du module HDLX2 passé en paramètre
// la valeur  passée en paramètre
void ecrire_Registre_Controle_Digit_HDLX2(u8 numero, u8 valeur)
{
GPIOB->ODR = valeur ; // MSB = 0 pour controle
GPIOG->ODR = numero ; //  numero digit
GPIOE->ODR = GPIOE->ODR & ~HDLX_NWR2; // activation WR2
GPIOE->ODR = GPIOE->ODR | HDLX_NWR2; // deactivation WR2
}

// affiche sur le module HDLX2 les 4 caractères ASCII 
// d'une chaine dont l'adresse est passée en paramètre
// (du digit de gauche vers celui de droite)
void afficher_Module_HDLX2(u8* chaine) 
{
u8 *pointeur;
s8 numero; // digit
pointeur = chaine;
for ( numero = 3 ; numero > -1 ; numero -- )
	{
	afficher_Digit_HDLX2(numero, *pointeur);
	pointeur ++;
	}
}

// affiche sur le module HDLX1 les 4 caractères ASCII 
// d'une chaine dont l'adresse est passée en paramètre
// (du digit de gauche vers celui de droite)
void afficher_Module_HDLX1(u8* chaine)
{
u8 *pointeur;
s8 numero; // digit
pointeur = chaine;
for ( numero = 3 ; numero > -1 ; numero -- )
	{
	afficher_Digit_HDLX1(numero, *pointeur);
	pointeur ++;
	}
}

// affiche sur les 2 modules HDLX les 8 caractères ASCII
// d'une chaine dont l'adresse est passée en paramètre
void afficher_Modules_HDLX(u8 *adresse)
{
	u8 *pointeur = adresse;
	afficher_Module_HDLX2(pointeur);
	pointeur += 4;
	afficher_Module_HDLX1(pointeur);
}

// contrôle le clignotement des 4 digits du module HDLX1
// (les paramètres correspondent à la valeur du bit Digit Blank
//  1 =>             0=>  A remplacer par CLIGN ET NCLIGN)
void piloter_Clignotement_HDLX1(u8 digit3, u8 digit2, u8 digit1, u8 digit0)
{	
    ecrire_Registre_Controle_Digit_HDLX1(3, digit3);
    ecrire_Registre_Controle_Digit_HDLX1(2, digit2);
    ecrire_Registre_Controle_Digit_HDLX1(1, digit1);
    ecrire_Registre_Controle_Digit_HDLX1(0, digit0);
}

// contrôle le clignotement des 4 digits du module HDLX2
// (les paramètres correspondent à la valeur du bit Digit Blank
//  1 =>             0=>  A remplacer par CLIGN ET NCLIGN)
void piloter_Clignotement_HDLX2(u8 digit3, u8 digit2, u8 digit1, u8 digit0)
{	
    ecrire_Registre_Controle_Digit_HDLX2(3, digit3);
    ecrire_Registre_Controle_Digit_HDLX2(2, digit2);
    ecrire_Registre_Controle_Digit_HDLX2(1, digit1);
    ecrire_Registre_Controle_Digit_HDLX2(0, digit0);
}

// _____________  16 decembre 2016_______________

// configure le Timer 3 canal 2 en PWM : led verte et résistance de réchauffement
// période 10 ms - durée état haut 0,5 ms
// sans activation de CEN ( Fmaster de 2 MHz)
void init_Timer3_PWM_canal2(void)
{
  TIM3-> CR1 |= TIM3_CR1_URS; // pour empecher UIF lors de UG
 
	// prescaler = 3 => CLK_CNT = 4 µs
	TIM3-> PSCR = 3;
	TIM3-> ARRH = 0x09; // pour période ...
	TIM3-> ARRL = 0xC4; // ... 10 ms
	
	// configuration du canal 2 durée état haut
	TIM3-> CCR2H = 0x00; //
	TIM3-> CCR2L = 0x7D; // 1/20ème de T
  
	TIM3-> CCMR2 = 0x70; // PWM en mode 2 OC2 en sortie
	TIM3-> CCER1 = TIM3_CCER1_CC2P | TIM3_CCER1_CC2E ; // canal2 actif bas
	//TIM3-> CCER1 = TIM3_CCER1_CC2E ; //canal 2 actif haut
	
	TIM3-> EGR = TIM3_EGR_UG; // chargement des registres
}

// configure le Timer 2 canal 1 en PWM => buzzer
// période 2273 µs - rapport cyclique 1/2 => note la3
// sans activation de CEN ( Fmaster de 2 MHz)
void init_Timer2_PWM_canal1(void)
{
  TIM2-> CR1 |= TIM2_CR1_URS; // pour empecher UIF lors de UG
 
	TIM2-> PSCR = 0x02;    // diviseur par 4 pour periode CLK_CNT 2µs
  	/* donc le compteur doit compter 1136 impulsions de 2 µs
	soit 0x470  donc ARR doit contenir 0x46F*/
	TIM2-> ARRH = 0x04;    // constante pour une ...
	TIM2-> ARRL = 0x6F;    // ... duree de 2,273 ms
	
 	// configuration du canal 1 durée état haut
	TIM2-> CCR1H = 0x02; //
	TIM2-> CCR1L = 0x38; // 1,136 msec
  
	TIM2-> CCMR1 = 0x60; // PWM mode 1 - CC1 en sortie
	
	// la mise en activité du canal sera faite 
	// quand cela sera nécessaire par :
	// TIM2->CCER1 = TIM2_CCER1_CC1E ; // CC1 actif haut
	
	TIM2-> EGR = TIM2_EGR_UG; // chargement des registres
	//TIM2-> CR1 |= TIM2_CR1_CEN; // démarrage Timer 2
}

//configure le Timer 2 canal 2 en PWM => signal Blanking des modules HDLX
// période 10 ms - durée état haut 0,5 s
// avec démarrage du Timer
void init_Timer2_PWM_canal2_10ms(void)
{
  TIM2-> CR1 |= TIM2_CR1_URS; // pour empecher UIF lors de UG
 
	// prescaler = 3 => CLK_CNT = 4 µs
	TIM2-> PSCR = 3;
	TIM2-> ARRH = 0x09; // pour période ...
	TIM2-> ARRL = 0xC4; // ... 10 ms
	
	// configuration du canal 2 durée état haut
	TIM2-> CCR2H = 0x00; //
	TIM2-> CCR2L = 0x7D; // 1/20ème de T
  
	TIM2-> CCMR2 = 0x70; // PWM en mode 2 OC2 en sortie
	TIM2-> CCER1 = TIM2_CCER1_CC2P | TIM2_CCER1_CC2E ; // canal2 actif bas
	//TIM3-> CCER1 = TIM3_CCER1_CC2E ; //canal 2 actif haut
	
	TIM2-> EGR = TIM2_EGR_UG; // chargement des registres
	TIM2-> CR1 |= TIM2_CR1_CEN; // démarrage Timer 2
}

//configure le Timer 2 canal 2 en PWM => signal Blanking des modules HDLX
// période 6 ms - durée état haut 0,5 s
// avec démarrage du Timer
void init_Timer2_PWM_canal2_6ms(void)
{
  TIM2-> CR1 |= TIM2_CR1_URS; // pour empecher UIF lors de UG
 
	// prescaler = 3 => CLK_CNT = 4 µs
	TIM2-> PSCR = 3;
	TIM2-> ARRH = 0x05; // pour période ...
	TIM2-> ARRL = 0xDC; // ... 6 ms
	
	// configuration du canal 2 durée état haut
	TIM2-> CCR2H = 0x00; //
	TIM2-> CCR2L = 0x7D; // 1/20ème de T
  
	TIM2-> CCMR2 = 0x70; // PWM en mode 2 OC2 en sortie
	TIM2-> CCER1 = TIM2_CCER1_CC2P | TIM2_CCER1_CC2E ; // canal2 actif bas
	//TIM3-> CCER1 = TIM3_CCER1_CC2E ; //canal 2 actif haut
	
	TIM2-> EGR = TIM2_EGR_UG; // chargement des registres
	TIM2-> CR1 |= TIM2_CR1_CEN; // démarrage Timer 2
}

// -----------------
// configure le Timer 2 canal 2 en PWM => signal Blanking des modules HDLX
// période 1s - durée état haut 0,5 s
// avec démarrage du Timer
void init_Timer2_PWM_canal2_1s(void)
{
  TIM2-> CR1 |= TIM2_CR1_URS; // pour empecher UIF lors de UG
 
	TIM2-> PSCR = 0x05;    // diviseur par 32 pour periode CLK_CNT 16µs
  	/* donc le compteur doit compter 62 500 impulsions de 16 µs
	soit 0xF424  donc ARR doit contenir 0xF423 ( car le compteur doit deborder)*/
	TIM2-> ARRH = 0xF4;    // constante pour une ...
	TIM2-> ARRL = 0x23;    // ... duree de 1s
	
 	// configuration du canal 2 sortie état haut
	TIM2-> CCR2H = 0x7A; //
	TIM2-> CCR2L = 0x11; // 0,5 sec
  
	TIM2-> CCMR2 = 0x60; // PWM mode 1 CC2 en sortie
	// la mise en activité du canal sera faite 
	// quand cela sera nécessaire par :
	//TIM2->CCER1 = TIM2_CCER1_CC2E ; // CC2 actif haut
	
	TIM2-> EGR = TIM2_EGR_UG; // chargement des registres
	TIM2-> CR1 |= TIM2_CR1_CEN; // démarrage Timer 2
}


// conversion d'une valeur BCD de 2 digits en ASCII avec caractères placés en mémoire
// traitement par quartet fort d'abord. valeur max : 99
void conv_BCD_ASCII(u8 valeur_BCD, u8 *adresse)
{
	u8 valeur;
	u8 *pointeur = adresse;

	valeur = valeur_BCD; 
	valeur = valeur & GPIO_PIN_HNIB; // conserve quartet fort
	valeur = valeur >> 4; // decalage droite 4 positions
	valeur += CODE_ASCII_0; // conversion ASCII
	*pointeur = valeur; // mise en mémoire
	pointeur ++;

	valeur = valeur_BCD; 
	valeur = valeur & GPIO_PIN_LNIB; // conserve quartet faible
	valeur += CODE_ASCII_0; // conversion ASCII
	*pointeur = valeur; // mise en mémoire
	// à poursuivre pour traiter les 2 octets de la valeur 16 bits ( sept 2017) 
}

// conversion d'une valeur binaire de 2 quartets en ASCII avec caractères placés en mémoire
// traitement par quartet fort d'abord
void conv_Bin_ASCII(u8 valeur_binaire, u8 *adresse)
{
	u8 *pointeur = adresse;
	u8 valeur;
	valeur = valeur_binaire; 
	valeur = valeur & GPIO_PIN_HNIB; // conserve quartet fort
	valeur = valeur >> 4; // decalage droite 4 positions
	if (valeur > 9)
	{
		valeur += 7; // pour affichage de lettres
	}
	valeur += CODE_ASCII_0; // conversion ASCII
	*pointeur = valeur; // mise en mémoire
	pointeur ++;

	valeur = valeur_binaire; 
	valeur = valeur & GPIO_PIN_LNIB; // conserve quartet faible
	if (valeur > 9)
	{
		valeur += 7; // pour affichage de lettres
	}
	valeur += CODE_ASCII_0; // conversion ASCII
	*pointeur = valeur; // mise en mémoire
}

// 20 décembre 2017
// conversion d'une valeur BCD de 3 quartets en ASCII avec caractères placés en mémoire
// traitement par quartet fort d'abord
void conv1_BCD_ASCII(u16 valeur_BCD, u8 *adresse)
{
//  extension décembre 2017 pour 16 bits
// traitement à partir du digit des centaines
u16 valeur;
u8 *pointeur = adresse;

valeur = valeur_BCD;
valeur = valeur & 0x0F00;
valeur = valeur >> 8; // decalage pour traitement des 4 bits des centaines
	valeur += CODE_ASCII_0; // conversion ASCII
	*pointeur = valeur; // mise en mémoire
	pointeur ++;

valeur = valeur_BCD; 
valeur = valeur & GPIO_PIN_HNIB; // conserve quartet fort
valeur = valeur >> 4; // decalage droite 4 positions

	valeur += CODE_ASCII_0; // conversion ASCII
	*pointeur = valeur; // mise en mémoire
	pointeur ++;

valeur = valeur_BCD; 
valeur = valeur & GPIO_PIN_LNIB; // conserve quartet faible

	valeur += CODE_ASCII_0; // conversion ASCII
	*pointeur = valeur; // mise en mémoire
}

u16 Ajustement_BCD(u16 valeur, u16 valeur_pre)
 {
	 short val = valeur;
	 if (((valeur & 0x000F )> 9) || ((valeur & 0x000F )<(valeur_pre & 0x000F ) ))
	 {
	  valeur = valeur + 6;
	 }
	 if ((valeur & 0x00F0) > 0x90)
	 {
	  valeur = valeur + 0x60;
	 }
		return (valeur);
 }
 
u16 Bin_BCD(u8 valeur)
 {
	 short reference_BCD = 1;
	 short reference_BCD_precedent = 0;
	 short resultat = 0;
	 short resultat_precedent = 0;
	 char masque_bit = 1;
	 char numero_bit;
	 char val;
	 
	 val=valeur;
	 
	 for ( numero_bit = 0; numero_bit < 8; numero_bit++)
	 {
		 if ( (valeur & masque_bit) == masque_bit )
		 {
			 resultat = resultat_precedent + reference_BCD;
			 resultat = Ajustement_BCD(resultat,resultat_precedent);
			 resultat_precedent = resultat;
		 }
		 reference_BCD = reference_BCD + reference_BCD;
		 reference_BCD = Ajustement_BCD(reference_BCD,reference_BCD_precedent);
		 reference_BCD_precedent = reference_BCD;
		 masque_bit = masque_bit + masque_bit;// decalage gauche 
	 }
	 return (resultat);
 }

        // --------------------  Fin provisoire ----------------