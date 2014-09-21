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
    int passStringLen;				 /* Length of password (N) */
    char *passString;
    char outcome[8];
    int numCorrect = 0;
    int numWrong = 0;

    // Initialize random seed
    srand(time(NULL));

    // Initialize signals
    signal(SIGINT, clientCNTCCode);

    if (argc < 3)         /* Test for correct number of parameters */
    {
        fprintf(stderr,"Usage:  %s <UDP SERVER PORT> <N> [initialPasswo[ rd]\n", argv[0]);
        exit(1);
    }

    servPort = atoi(argv[1]);  		/* First arg:  local port */
    passStringLen = atoi(argv[2]);	/* Second arg: password length */

    if(passStringLen > PASSMAX)
    	dieWithError("Password exceeds max length");
    else if(passStringLen < 0)
    	dieWithError("Password length must not be negative");

    // Assign optional initialPassword or generate random pass
    if (argc == 4)
    	passString = argv[3];
    else {
    	passString = malloc(passStringLen);
     	genRandPass(passString, passStringLen);
    }

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

        if (checkPass(buffer, passString)) {
        	printf("SUCCESS\n");
        	numCorrect++;
        	genRandPass(passString, passStringLen);
        } else {
        	printf("FAILURE\n");
        	numWrong++;
        }

        /* Send received datagram back to the client */
        if (sendto(sock, buffer, recvMsgSize, 0, 
             (struct sockaddr *) &clntAddr, sizeof(clntAddr)) != recvMsgSize)
            dieWithError("sendto() sent a different number of bytes than expected");
    }

    printf("Correct guesses: %d\nIncorrect guesses: %d\n", numCorrect, numWrong);
    exit(1);

}

void genRandPass(char *pass, int passStringLen) {
	int i, rIndex;
	char *c = pass;

	for(i=0; i<passStringLen; i++, c++) {
		rIndex = rand() % 62;
		*c = availChars[rIndex];
	}

	printf("%s\n", pass);
}

int checkPass(char *guess, char *pass) {
	if(strcmp(guess, pass) == 0) return 1;
	else return 0;
}