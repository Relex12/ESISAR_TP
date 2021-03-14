# include <stdio.h>
# include <stdlib.h>
# include <security/pam_appl.h>
# include <security/pam_misc.h>

const struct pam_conv conv = {
	misc_conv,
	NULL
};

int main(int argc, char *argv[]) {

	pam_handle_t* pamh = NULL;

	if(argc != 2) {
		printf("Missing username\n");
		exit(1);
	}

	// initialisation de la session PAM
	if (pam_start("module", argv[1], &conv, &pamh) == PAM_SUCCESS){
		printf("Username accepted\n");
	} else {
		printf("Error: Cannot start session\n");
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
		printf("Error: Failed to close PAM session\n");
		exit(1);
	}

	return 0;
}
