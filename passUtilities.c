#include "passwordBreaker.h"

void genPass(char *pass, int passLen) {
	char *c = pass;
	int i;

	for (i=0; i<passLen; i++, c++) {
		*c = 'a';
	}

	printf("%s\n", pass);
}

void genRandomPass(char *pass, int passLen) {

}

/* Global utilities	*/
void clientCNTCCode() {
	printf("\nUDPEchoClient:  CNT-C Interrupt,  exiting....\n");
	exit(1);
}

void dieWithError(char *errorMessage) {
	printf("%s\n", errorMessage);
    //perror(errorMessage);
    exit(1);
}