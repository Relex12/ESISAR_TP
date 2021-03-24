/**
  ******************************************************************************
  * @file fonctions_TP_utiles.h
  * @brief This file contains 
  * @author Bernard Glossi
  * @version V1.1.1
  * 22 juillet 2016
 
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FONCTIONS_TP_UTILES_H
#define __FONCTIONS_TP_UTILES_H

// prototype des fonctions du fichier mes_fonctions_juillet_2016.c

void init_Ports(void); // inséré le 31 aout 2017

void init_Timer1(void); // 1 sec
void init_Timer3(void); // 1 sec
void init_Timer3_PWM_canal2(void); // led verte et résistance de réchauffement
void init_Timer2_PWM_canal1(void); // buzzer
void init_Timer2_PWM_canal2_1s(void); //signal Blanking des 2 modules HDLX
void init_Timer2_PWM_canal2_10ms(void); //signal Blanking des 2 modules HDLX
void init_Timer2_PWM_canal2_6ms(void); //signal Blanking des 2 modules HDLX

u8 lire_Etat_BP2(void);
u8 lire_Etat_BP(u8 numero_BP);
u8 lire_Valeur_Binaire_BP(void);
u8 lire_Etat_INT(void);

u8 afficher_TIL321(u8 valeur);

void afficher_Digit_HDLX1(u8 numero, u8 caractere);
void afficher_Digit_HDLX2(u8 numero, u8 caractere);
void ecrire_Registre_Controle_Digit_HDLX1(u8 numero, u8 valeur);
void ecrire_Registre_Controle_Digit_HDLX2(u8 numero, u8 valeur);
void afficher_Module_HDLX1(u8* chaine);
void afficher_Module_HDLX2(u8* chaine);
void afficher_Modules_HDLX(u8 *adresse);
void piloter_Clignotement_HDLX1(u8 digit3, u8 digit2, u8 digit1, u8 digit0);
void piloter_Clignotement_HDLX2(u8 digit3, u8 digit2, u8 digit1, u8 digit0);
  
void conv_BCD_ASCII(u8 valeur_BCD, u8 *adresse);
void conv1_BCD_ASCII(u16 valeur_BCD, u8 *adresse);
void conv_Bin_ASCII(u8 valeur_binaire, u8 *adresse);  // revoir les termes et U16
u16 Ajustement_BCD(u16 valeur, u16 valeur_pre);
u16 Bin_BCD (u8 valeur); // modif 28/11/16


#endif __FONCTIONS_TP_UTILES_H