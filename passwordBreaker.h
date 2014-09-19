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

char availChars[62] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
					'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B',
					'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
					'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '0', '1', '2', '3', 
					'4', '5', '6', '7', '8', '9'};

// Resolve domain name to IP address and store in addr
void resolveName(char* name, struct sockaddr_in* addr);

// Randomly generate password\
void genPass(char* pass, int passLen);


/* Global utilities	*/
void clientCNTCCode();

void dieWithError(char *errorMessage);

#endif
