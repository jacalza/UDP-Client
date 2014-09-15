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

// SIGINT execution method
void clientCNTCCode();

// Print errorMessage and exit
void dieWithError(char *errorMessage);

#endif
