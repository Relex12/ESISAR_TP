/* question de preparation

pour la condition d'arret de la recursivite de minimax,
nous avons pense a  initialiser une variable d'action
qui serait a  1 lorsque l'intelligence programmee a joue
son tour. Tant que cette variable est a  zero, la fonction
s'appelle de maniere recursive afin de determiner l'empla-
cement ideal.
*/

#include <stdio.h>
#include <stdlib.h>

#define NB 3

typedef int ttt[NB][NB];



/* si	t = {{0x01,0x01,0x01},{0x02,0x02,0x02},{0x00,0x00,0x00}} alors affiche ecrit ceci :

| x | x | x |
| o | o | o |
|   |   |   |

ce commentaire nous a servi a connaitre les indices du damier
*/


#define INFINITY 10000
#define WIN 1000

#define P1 0x01 	// x
#define P2 0x02		// o


int nb_coups = 0;		// la declaration en externe provoque un warning mais nous est necessaire


// evaluate for player 1 P1 (x)
// si player 1 gagne, score = WIN
// si player 1 perd, score = -WIN
// si nul, score = 0


int evaluate(ttt t)
	// evaluate renvoie WIN si le joueur P1 gagne, -WIN si l'IA P2 gagne, 0 sinon
{
/*dans ce paragraphe nous testons chaque possibilite permettant au joueur 1 de gagner */
if ((t[0][0] ==0x01) && (t[0][1]==0x01) && (t[0][2]==0x01))           // 1ere ligne
	return WIN;
else if ((t[1][0] ==0x01) && (t[1][1]==0x01) && (t[1][2]==0x01))      // 2eme ligne
	return WIN;
else if ((t[2][0] ==0x01) && (t[2][1]==0x01) && (t[2][2]==0x01))      // 3eme ligne
	return WIN;
else if ((t[0][0] ==0x01) && (t[1][0]==0x01) && (t[2][0]==0x01))      // 1ere colonne
	return WIN;
else if ((t[0][1] ==0x01) && (t[1][1]==0x01) && (t[2][1]==0x01))      // 2eme colonne
	return WIN;
else if ((t[0][2] ==0x01) && (t[1][2]==0x01) && (t[2][2]==0x01))      // 3eme colonne
	return WIN;
else if ((t[0][0] ==0x01) && (t[1][1]==0x01) && (t[2][2]==0x01))      // diagonale de gauche a droite
	return WIN;
else if ((t[0][2] ==0x01) && (t[1][1]==0x01) && (t[2][0]==0x01))      // diagonale de droite a gauche
	return WIN;

/*dans ce paragraphe nous testons chaque possibilite permettant au joueur 1 de perdre */

if ((t[0][0] ==0x02) && (t[0][1]==0x02) && (t[0][2]==0x02))           // 1ere ligne
	return (-WIN);
else if ((t[1][0] ==0x02) && (t[1][1]==0x02) && (t[1][2]==0x02))      // 2eme ligne
	return (-WIN);
else if ((t[2][0] ==0x02) && (t[2][1]==0x02) && (t[2][2]==0x02))      // 3eme ligne
	return (-WIN);
else if ((t[0][0] ==0x02) && (t[1][0]==0x02) && (t[2][0]==0x02))      // 1ere colonne
	return (-WIN);
else if ((t[0][1] ==0x02) && (t[1][1]==0x02) && (t[2][1]==0x02))      // 2eme colonne
	return (-WIN);
else if ((t[0][2] ==0x02) && (t[1][2]==0x02) && (t[2][2]==0x02))      // 3eme colonne
	return (-WIN);
else if ((t[0][0] ==0x02) && (t[1][1]==0x02) && (t[2][2]==0x02))      // diagonale de gauche a droite
	return (-WIN);
else if ((t[0][2] ==0x02) && (t[1][1]==0x02) && (t[2][0]==0x02))      // diagonale de droite a gauche
	return (-WIN);
else
	return 0;
}


void affiche(ttt t) 				// ne pas toucher a  cette fonction
{
	int l,c;
	for (l=0;l<NB;l++) {
		for (c=0;c<NB;c++) {
			switch (t[l][c]) {
				case 0x00: printf("|   "); break;
				case 0x01: printf("| x "); break;
				case 0x02: printf("| o "); break;
			}
		}
		printf("|\n");
	}
	printf("score=%d\n",evaluate(t));
}


int fini(ttt t, int bavard)					// fonction a modifier
{
	int score = evaluate (t);
	printf ("nombre de tours : %d\n", nb_coups);

	if (score == 0) 	{
		if (nb_coups < 9) {
			nb_coups++;
			return 0;
			}
		else  {
			if (bavard == 1) printf ("Personne n'a gagne la partie\n");
			return 1;
			}
		}
	else  {
		if (score == WIN) {
			if (bavard == 1) {printf ("Tu as gagne la partie\n");}}
		else if (score == -WIN) {
			if (bavard == 1) {printf ("Tu as perdu la partie\n");}}
		else
			if (bavard == 1) {printf ("score différent de 0, de WIN et de -WIN\n erreur\n");}
		return 1;
		}
	}



int test ()
{
	printf ("~~~~~~~~~~~~~~~debut de section de test~~~~~~~~~~~~~~~\n");
	ttt t1={{0x01,0x00,0x02},{0x00,0x02,0x00},{0x02,0x00,0x01}};
	printf ("si le damier est :\n");
	affiche (t1);
	fini (t1, 1);
	ttt t2={{0x02,0x02,0x02},{0x01,0x02,0x01},{0x01,0x01,0x00}};
	printf ("\nsi le damier est :\n");
	affiche (t2);
	fini (t2, 1);
	ttt t3={{0x01,0x01,0x01},{0x00,0x02,0x00},{0x00,0x00,0x02}};
	printf ("\nsi le damier est :\n");
	affiche (t3);
	fini (t3, 1);
	printf ("~~~~~~~~~~~~~~~~fin de section de test~~~~~~~~~~~~~~~~\n\n\n");
	return 1;
}

int minimax (ttt t,int *position,int joueur)
{
	int i =0;
	int j = 0;
	int var =0;
	int meilleur_pos = 0;

	while (i < 9)
    {
        if ((t[meilleur_pos/3][meilleur_pos%3] == 0x02) | (t[meilleur_pos/3][meilleur_pos%3] == 0x01))
            {
                meilleur_pos++;
                i++;
            }
        else
        {
            t[meilleur_pos/3][meilleur_pos%3] = 0x01;
            var = evaluate(t);
            if (var == (WIN))
            {
                i=10;
                t[meilleur_pos/3][meilleur_pos%3] = 0x02;

                return meilleur_pos;
            }
            else
                {
                t[meilleur_pos/3][meilleur_pos%3] = 0x00;
                meilleur_pos++;
                i++;
                }
        }
    }
    i =0;
	while (i < 9)
    {
        if ((t[meilleur_pos/3][meilleur_pos%3] == 0x02) | (t[meilleur_pos/3][meilleur_pos%3] == 0x01))
            {
                meilleur_pos++;
                i++;
            }
        else
        {
            t[meilleur_pos/3][meilleur_pos%3] = 0x02;
            var = evaluate(t);
            if (var == (-WIN))
                {
                i=10;

                return meilleur_pos;
                }
            else
                {
                t[meilleur_pos/3][meilleur_pos%3] = 0x00;
                meilleur_pos++;
                i++;
                }
        }
    }


    meilleur_pos = 0;
    i =0;
    while (i < 9)
    {

        if ((t[meilleur_pos/3][meilleur_pos%3] == 0x02) | (t[meilleur_pos/3][meilleur_pos%3] == 0x01))
            {
                meilleur_pos++;
                i++;
            }
        else
        {
            for (j=0; j<10; j++)
            {
                if ((t[j/3][j%3] == 0x02) | (t[j/3][j%3] == 0x01));
                else
                    {
                    t[j/3][j%3] = 0x01;
                    var = evaluate(t);
                        if (var == (WIN))
                            {
                            t[j/3][j%3] = 0x00;
                            meilleur_pos++;
                            i++;
                            }
                        else
                            {
                            t[j/3][j%3] = 0x00;
                            i=10;
                            }
            }
        }
    }
    }

	return meilleur_pos;
}

										// version recursive non fonctionnelle


/*{
	int i = 0;
	int score1 = 0;
	int score2 = 0;
		

	if (joueur == P2) {		//le J2 veut minimiser le score
		for (i = 0; i < 10; i++) {
			if (i == 9)
				return *position;
			if (t[i/3][i%3] == 0x00) {
				score1 = evaluate(t);
				t[i/3][i%3] = P2;			
				score2 = evaluate(t);
				if (score1 <= score2)
					*position = minimax (t, position, P1);
				}
			}
		return *position;
		}
	if (joueur == P1) {		//le J1 veut maximiser le score
		for (i = 0; i < 10; i++) {
			if (i == 9)
				return *position;
			if (t[i/3][i%3] == 0x00) {
				score1 = evaluate(t);
				t[i/3][i%3] = P1;			
				score2 = evaluate(t);
				if (score1 >= score2)
					*position = minimax (t, position, P2);
				}
			}
		return *position;
		}
	return 0;
}

*/
										// fin de la version recursice





int main() 								// ne pas toucher a  cette fonction
{
	test ();
	int val,move,joueur=P2;

	char reponse;
	ttt t={{0x00,0x00,0x00},{0x00,0x00,0x00},{0x00,0x00,0x00}};

	int P1_action = 0;
	printf ("Bonjour nouveau challenger, et bienvenue au jeu du morpion\n");
	printf ("pour vous aider, voici les indices des cases du damier\n | 0 | 1 | 2 | \n | 3 | 4 | 5 | \n | 6 | 7 | 8 | \n");
	printf ("etes-vous d'accord pour laisser le bot commencer ? (y / n)  : \t");
	while (reponse != 'y' && reponse != 'n')
		scanf ("%c", &reponse);
	if (reponse == 'n')
		val = move = joueur=P1;

	printf ("le damier est vide\n");
	while (!fini(t, 1)) {
		affiche(t);
		printf("c'est au tour du joueur %d \n",joueur);		//ligne modifiee
		if ( joueur == P1 ) {
			while  (!(P1_action)) {				// demande un emplace valide en boucle
				printf("entrez votre coup\n");
				scanf("%d",&move);
				if (t[move/3][move%3]  == 0x00) {
					t[move/3][move%3]=P1;
					P1_action = 1;
					}
				else  {
					printf ("emplacement deja utilise \nveuillez reessayer\n");
					affiche(t);
					}
				}					// fin du while
			P1_action = 0; 				// réinitialisation de la variable de condition
			joueur=P2;
			}
		else {
			move=-1;
			ttt temp={{t[0][0],t[0][1],t[0][2]},{t[1][0],t[1][1],t[1][2]},{t[2][0],t[2][1],t[2][2]}};
         		val=minimax(temp,&move,P2);
	      		move=val;
			printf("le meilleur coup est %d (val=%d)\n",move,val);
			if ( move != -1 ) {
				t[move/3][move%3]=P2;
			}
			joueur=P1;

		}
	}
	affiche(t);
	return EXIT_SUCCESS;
}
