#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <security/pam_appl.h>
#include <security/pam_modules.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

/* expected hook */
PAM_EXTERN int pam_sm_setcred( pam_handle_t *pamh, int flags, int argc, const char **argv ) {
	return PAM_SUCCESS;
}

PAM_EXTERN int pam_sm_acct_mgmt(pam_handle_t *pamh, int flags, int argc, const char **argv) {
/*	printf("Acct mgmt\n"); */
	return PAM_SUCCESS;
}

/* expected hook, this is where custom stuff happens */
PAM_EXTERN int pam_sm_authenticate( pam_handle_t *pamh, int flags,int argc, const char **argv ) {
	int retval;
        pid_t pid;
	const char* pUsername;
        char *const parmList[] = {"/bin/ls", "-l", "/u/userid/dirname", NULL};
        char *const envParms[2] = {"STEPLIB=SASC.V6.LINKLIB", NULL};	
	int i = 1; int waitstatus;


	fprintf(stderr,"Reached step 1");
	chdir("/usr/local/bin/python-validity");
	pid = fork();
if(pid < 0) {
        fprintf(stderr, "Fork failed");
        return 1;
}
else if(pid == 0) {
        printf("Child pid is %d\n", pid);   
	i = execv("/usr/local/bin/python-validity/pam_validity.sh", NULL);
}
else {
        wait(&waitstatus);
        i = WEXITSTATUS(waitstatus);
}

	retval = pam_get_user(pamh, &pUsername, "Username: ");
	printf("Welcome %s\n", pUsername);
	printf("ExitCode %i", i);    

	if(i == 0) {
	return PAM_SUCCESS;
	fprintf(stderr,"Success");
	}
	else {
	return PAM_AUTH_ERR;
	fprintf(stderr,"No success");
	}
}
