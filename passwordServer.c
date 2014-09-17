#include "passwordBreaker.h"

int main(int argc, char *argv[])
{
    int sock;                        /* Socket */
    struct sockaddr_in servAddr; 	 /* Local address */
    struct sockaddr_in clntAddr; 	 /* Client address */
    unsigned int cliAddrLen;         /* Length of incoming message */
    char buffer[PASSMAX];        /* Buffer for echo string */
    unsigned short servPort;     	 /* Server port */
    int recvMsgSize;                 /* Size of received message */
    char *passString;
    int passStringLen;				 /* Length of password (N) */

    if (argc < 3)         /* Test for correct number of parameters */
    {
        fprintf(stderr,"Usage:  %s <UDP SERVER PORT> <N> [initialPassword]\n", argv[0]);
        exit(1);
    }

    servPort = atoi(argv[1]);  		/* First arg:  local port */
    passStringLen = atoi(argv[2]);	/* Second arg: password length */

    // Assign optional initialPassword or generate random pass
    if (argc == 4)
    	passString = argv[3];
    // else 
    // 	genPass(passString);

    /* Create socket for sending/receiving datagrams */
    if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
        dieWithError("socket() failed");

    /* Construct local address structure */
    memset(&servAddr, 0, sizeof(servAddr));   	  /* Zero out structure */
    servAddr.sin_family = AF_INET;                /* Internet address family */
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY); /* Any incoming interface */
    servAddr.sin_port = htons(servPort);      	  /* Local port */

    /* Bind to the local address */
    printf("passwordServer: About to bind to port %d\n", servPort);    
    if (bind(sock, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0)
        dieWithError("bind() failed");
  
    for (;;) /* Run forever */
    {
        /* Set the size of the in-out parameter */
        cliAddrLen = sizeof(clntAddr);

        /* Block until receive message from a client */
        if ((recvMsgSize = recvfrom(sock, buffer, PASSMAX, 0,
            (struct sockaddr *) &clntAddr, &cliAddrLen)) < 0)
            dieWithError("recvfrom() failed");

        printf("Handling client %s\n", inet_ntoa(clntAddr.sin_addr));

        /* Send received datagram back to the client */
        if (sendto(sock, buffer, recvMsgSize, 0, 
             (struct sockaddr *) &clntAddr, sizeof(clntAddr)) != recvMsgSize)
            dieWithError("sendto() sent a different number of bytes than expected");
    }
    /* NOT REACHED */
}

void genPass(char *pass) {

}