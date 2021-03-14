# include <stdio.h>
# include <stdlib.h>
# include <security/pam_appl.h>
# include <security/pam_misc.h>

const struct pam_conv conv = {
	misc_conv,
	NULL
};

/* Cette application devra:
- pouvoir passer en argument le nom de l’utilisateur demandé (comme su)
- forcer le RUSER à «test» et le RHOST à «localhost» pour que le module
	pam_warn.so puisse logger ces informations. (RUSER =username demandant le
	module)  ( RHOST = la  station  depuis laquelle le RUSER demande le module)
- pouvoir authentifier l’utilisateur avec n’importe quel module PAM (par ex:
	pam_unix.so)
- pouvoir autoriser l’utilisateur avec n’importe quel module PAM
- une fois l’authenfication et l’autorisation effectuée afficher une ligne de
	texte, par exemple: «welcome!» */


int main(int argc, char *argv[]) {

	pam_handle_t* pamh = NULL;

	if(argc != 2) {
		printf("Missing username\n");
		exit(1);
	}

	// initialisation de la session PAM
	if (pam_start("nomodule", argv[1], &conv, &pamh) == PAM_SUCCESS){
		printf("Username accepted\n");
	} else {
		printf("Error: Cannot start session\n");
		exit(1);
	}

	// mise de RUSER à "test"
	if (pam_set_item (pamh, PAM_RUSER, "test") == PAM_SUCCESS){
		printf("RUSER set to 'test'\n");
	} else {
		printf("Error: Failed to set RUSER\n");
		exit(1);
	}

	// mise de RHOST à '"localhost"'
	if (pam_set_item (pamh, PAM_RHOST, "localhost") == PAM_SUCCESS){
		printf("RHOST set to 'localhost'\n");
	} else {
		printf("Error: Failed to set RHOST\n");
		exit(1);
	}

	// authentification (demande de mot de passe si besoin)
	if (pam_authenticate(pamh, 0) == PAM_SUCCESS){
		printf("Authentication accepted\n");
	} else {
		printf("Error: Authentication failed\n");
		exit(1);
	}

	// autorisation
	if (pam_acct_mgmt(pamh, 0) == PAM_SUCCESS) {
		printf("Bienvenue dans notre application PAM-aware !\n");
	} else {
		printf("Error: Not allowed\n");
		exit(1);
	}

	// fermeture de la session PAM
	if (pam_end(pamh, 0) != PAM_SUCCESS) {
		pamh = NULL;
		printf("Error: Failed to close PAM session properly\n");
		exit(1);
	}

	return 0;
}
