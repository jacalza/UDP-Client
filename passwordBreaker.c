#include "passwordBreaker.h"

int main(int argc, char *argv[]) {
    int sock;                        /* Socket descriptor */
    struct sockaddr_in servAddr; 	 /* Password server address */
    struct sockaddr_in fromAddr;     /* Source address of passwordBreaker */
    struct hostent *thehost;         /* Hostent from gethostbyname() */
    unsigned short servPort;     	 /* Password server port */
    unsigned int fromSize;           /* In-out of address size for recvfrom() */
    char *servName;                  /* IP address of server */
    char *passString = "";                /* String to send to password server */
    //char passBuffer[ECHOMAX+1];    /* Buffer for receiving password string */
    int passStringLen;               /* Length of password string to send */
    int respStringLen;               /* Length of received response */
	
    if (argc != 4)    /* Test for correct number of arguments */
        dieWithError("Usage: passwordBreaker <serverName> <serverPort> <N>");

    signal(SIGINT, clientCNTCCode);

    servName = argv[1];       /* First arg: server name/IP address (dotted quad) */
    servPort = atoi(argv[2]); /* Second arg: server port */

    if ((passStringLen = strlen(passString)) > PASSMAX)  /* Check input length */
        dieWithError("Password too long");

    /* Create a datagram/UDP socket */
    if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
        dieWithError("socket() failed");

    // /* Construct the server address structure */
    memset(&servAddr, 0, sizeof(servAddr));			/* Zero out structure */
    servAddr.sin_family = AF_INET;					/* Internet addr family */
    servAddr.sin_addr.s_addr = inet_aton(servName);	/* Server IP address */
    servAddr.sin_port = htons(servPort);			/* Server port */

    // /* If user gave a dotted decimal address, we need to resolve it  */
    if (servAddr.sin_addr.s_addr == -1) {
		printf("hi\n");
    	thehost = gethostbyname(servName);
        	servAddr.sin_addr.s_addr = *((unsigned long *) thehost->h_addr_list[0]);
    }
    //
    // /* Send the string to the server */
    // printf("UDPEchoClient: Send the string: %s to the server: %s \n", echoString,servIP);
    // if (sendto(sock, echoString, echoStringLen, 0, (struct sockaddr *)
    //            &echoServAddr, sizeof(echoServAddr)) != echoStringLen)
    //   DieWithError("sendto() sent a different number of bytes than expected");
    //
    // /* Recv a response */
    // printf("UDPEchoClient: And now wait for a response... \n");
    // fromSize = sizeof(fromAddr);
    // if ((respStringLen = recvfrom(sock, echoBuffer, ECHOMAX, 0,
    //      (struct sockaddr *) &fromAddr, &fromSize)) != echoStringLen)
    //     DieWithError("recvfrom() failed");
    //
    // if (echoServAddr.sin_addr.s_addr != fromAddr.sin_addr.s_addr)
    // {
    //     fprintf(stderr,"Error: received a packet from unknown source \n");
    // }
    // /* null-terminate the received data */
    // echoBuffer[respStringLen] = '\0';
    // printf("UDPEchoClient:  Received the following (%d bytes) data: %s\n",respStringLen,echoBuffer);
    close(sock);
    exit(0);
}

void clientCNTCCode() {
	printf("\nUDPEchoClient:  CNT-C Interrupt,  exiting....\n");
	exit(1);
}

void dieWithError(char *errorMessage) {
	printf("%s\n", errorMessage);
    //perror(errorMessage);
    exit(1);
}
