# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <string.h>
# include <security/pam_appl.h>
# include <security/pam_modules.h>

# define VALMIN 1
# define VALMAX 20
# define DELAY 3000000 	// 3 s

int converse( pam_handle_t *pamh, int nargs, struct pam_message **message, struct pam_response **response ) {
	int retval ;
	struct pam_conv *conv ;

	retval = pam_get_item( pamh, PAM_CONV, (const void **) &conv ) ;
	if( retval==PAM_SUCCESS ) {
		retval = conv->conv( nargs, (const struct pam_message **) message, response, conv->appdata_ptr ) ;
	}

	return retval ;
}

/*Ecrire et commenter un ou plusieurs module(s) permettant l’authentification
(auth) et l’autorisation (account) d’un utilisateur suivant les règles
suivantes :
- Si le nom de l’utilisateur demandant l’authentification commence par un «b»
	lui donner l’accès sans demander d’authentification.
- Sinon demander à l’utilisateur le résultat d’une multiplication entre deux
	nombres ( modulo 20 ) aléatoires.
- Si le résultat est bon, accorder l’authentification.
- Si le résultat est faux laisser un délai de plusieurs secondes avant de
	rendre la main à l’application.
- Si le RHOST est différent de localhost ne pas autoriser.*/

// réponse aux demandes d'authentification
PAM_EXTERN int pam_sm_authenticate( pam_handle_t *pamh, int flags,int argc, const char **argv ) {
	const char *user;
	int success;
	success = pam_get_user(pamh, &user, "Username: ");

	// si on n'a pas pu avoir le nom d'utilisateur, on n'authentifie pas
	if (success != PAM_SUCCESS) {
		return success;
	}

	// si le nom d'utilisateur commence par un b, on authentifie
	if (strncmp(user, "b", 1) == 0) {
		return PAM_SUCCESS;
	}

	// réalisation du calcul pour l'utilisateur
	srand(time(NULL));
	int a = rand()% (VALMAX-VALMIN) + VALMIN ;
	int b = rand()% (VALMAX-VALMIN) + VALMIN ;
	int	expected = a * b;

	// initialisation des données nécessaires pour la conversation avec le client
	char* input;
	struct pam_message msg[1],*pmsg[1];
	struct pam_response *resp;
	pmsg[0] = &msg[0];
	msg[0].msg_style = PAM_PROMPT_ECHO_ON ;
	char msg_send[40];
	sprintf( msg_send, "Donner le résultat de %d x %d: \t", a, b);
	msg[0].msg = msg_send;

	// initiation de la conversation
	resp = NULL ;
	int retval;
	if( (retval = converse(pamh, 1 , pmsg, &resp))!=PAM_SUCCESS ) {
		return retval ;
	}

	// récupération de la réponse du client
	if( resp ) {
		if( (flags & PAM_DISALLOW_NULL_AUTHTOK) && resp[0].resp == NULL ) {
					free( resp );
					return PAM_AUTH_ERR;
		}
		input = resp[ 0 ].resp;
		resp[ 0 ].resp = NULL;
			} else {
		return PAM_CONV_ERR;
	}


	// si le résultat est correct, on authentifie
	if (atoi(input) == expected) {
		return PAM_SUCCESS;
	}

	// si rien n'a marché, on attend 3 secondes et on n'authentifie pas
	#ifdef HAVE_PAM_FAIL_DELAY
	pam_fail_delay(pamh, DELAY);
	#endif /* HAVE_PAM_FAIL_DELAY */
	return PAM_AUTH_ERR;
}


// réponse aux demandes d'autorisation
PAM_EXTERN int pam_sm_acct_mgmt(pam_handle_t *pamh, int flags, int argc, const char **argv) {
	const void **item;
	int success;
	success = pam_get_item (pamh, PAM_RHOST, item);

	// si on n'a pas pu avoir RHOST, on n'authentifie pas
	if (success != PAM_SUCCESS) {
		return success;
	}

	// si RHOST != localhost, on refuse
	if (*item != NULL && strcmp(*item, "localhost") == 0){
		return PAM_SUCCESS;
	} else {
		return PAM_AUTH_ERR;
	}
}


PAM_EXTERN int pam_sm_setcred( pam_handle_t *pamh, int flags, int argc, const char **argv ) {
	return PAM_SUCCESS;
}
