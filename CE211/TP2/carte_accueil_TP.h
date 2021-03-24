/**
  ******************************************************************************
  * @file carte_accueil_TP.h
  * @brief This file contains 
  * @author Bernard Glossi
  * @version V1.1.1
  * @date 8/12/2014
  * dernière actualisation : 12 décembre 2016
 
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _carte_accueil_TP_H
#define _carte_accueil_TP_H


/* Valeurs destinées aux registres de configuration des ports */

// Port A pour pilotage des 4 leds rouges
#define PORT_A_DIRECTION 0x78  // 4 bits en sortie
#define PORT_A_TECHNO_LIGNES 0x78 // 4 sorties en open drain

// Port B pour pilotage des afficheurs
#define PORT_B_DIRECTION 0xFF  // 8 bits en sortie
#define PORT_B_TECHNO_LIGNES 0xFF // 8 sorties en push pull

// Port C pour les 4 boutons-poussoirs et SPI
#define PORT_C_DIRECTION 0x00  //  7 bits en entrée
#define PORT_C_TECHNO_LIGNES 0xFF // 7 lignes en pull up   

// Port D pour UART2, SWIM, led verte, TLI, channels/timers et /BL HDLX
#define PORT_D_DIRECTION 0x09  // lignes 0 et 3 en sortie
#define PORT_D_TECHNO_LIGNES 0x88  // ligne 7 en pull up pour BP1 estérieur,
                                   // ligne 3 en Push Pull, ligne 0 en open drain

// Port E pourI2C, entrées analogiques et 2 signaux /WR HDLX													 // bit 4 push pull
#define PORT_E_DIRECTION 0x28 // lignes 3 et 5 en sortie
#define PORT_E_TECHNO_LIGNES 0xA8  // ligne 7 pull up pour BP2 extérieur,
                             // lignes 3 et 5 en push pull, ligne 0 en pull up pour INT 1 

// Port G pour A0 et A1 HDLX  et verrouillage dans 74HC165
#define PORT_G_DIRECTION 0x03 // 2 lignes en sortie
#define PORT_G_TECHNO_LIGNES 0x03  // 2 lignes en Push Pull


/* Masques destines aux 2 modules d'affichage HDLX */

#define DISPLAY_ASCII 0x80
#define HDLX_NBL 0x08 // Blanking
#define HDLX_NWR1 0x08 // Impulsion /WR1
#define HDLX_NWR2 0x20 // Impulsion /WR2

/* autres définitions pour éléments de la carte d'accueil */

#define ALLUMEE 0 // pour led verte
#define ETEINTE 1

#define ACTIF 0  // pour les 2 BP extérieurs
#define NON_ACTIF 1

#define LETTRE_E 0x9E
#define CODE_ASCII_0 0x30

 enum Afficheur_TIL321
{
ZERO = 0xFC,
UN = 0x60,
DEUX = 0xDA,
TROIS = 0XF2,
QUATRE = 0X66,
CINQ = 0XB6,
SIX = 0XBE,
SEPT = 0xE0,
HUIT = 0xFE,
NEUF = 0xF6
};

#endif _carte_accueil_TP_H
