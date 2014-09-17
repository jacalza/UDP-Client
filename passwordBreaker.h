#ifndef PASSWORDBREAKER_H
#define PASSWORDBREAKER_H

#define PASSMAX 8

/*
	Code used from donahoo/UDPEcho/UDPEcho.h
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>
#include <string.h>     /* for memset() */
#include <netinet/in.h> /* for in_addr */
#include <sys/socket.h> /* for socket(), connect(), sendto(), and recvfrom() */
#include <arpa/inet.h>  /* for sockaddr_in and inet_addr() */
#include <netdb.h>      /* for getHostByName() */
#include <stdlib.h>     /* for atoi() and exit() */
#include <unistd.h>     /* for close() */

#include "passUtilities.c"


// Resolve domain name to IP address and store in addr
void resolveName(char* name, struct sockaddr_in* addr);

// Randomly generate password\
void genPass(char* pass) {
	char *c;
	for(c = &pass; *c != NULL; c++) {
		printf("%s", c);
	}
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

#endif
