#include "passwordBreaker.h"

int main(int argc, char *argv[]) {
    int sock;                        /* Socket descriptor */
    struct sockaddr_in servAddr; 	 /* Password server address */
    struct sockaddr_in fromAddr;     /* Source address of passwordBreaker */
    struct hostent *thehost;         /* Hostent from gethostbyname() */
    char *servPort;     	         /* Password server port */
    unsigned int fromSize;           /* In-out of address size for recvfrom() */
    char *servName;                  /* IP address/domain name of server */
    char *servIP;
    char buffer[PASSMAX+1];          /* Buffer for receiving password string */
    int passStringLen;               /* Length of password string to send */
    int respStringLen;               /* Length of received response */
	
    // Initialize signals
    signal(SIGINT, clientCNTCCode);

    if (argc != 4)    /* Test for correct number of arguments */
        dieWithError("Usage: passwordBreaker <serverName> <serverPort> <N>");

    servName = argv[1];       /* First arg: server name/IP address (dotted quad) */
    servPort = argv[2];       /* Second arg: server port */

    // Get length of password and initialize passString
    if ((passStringLen = atoi(argv[3])) > PASSMAX)  /* Check input length */
        dieWithError("Password exceeds max length");
    else if (passStringLen < 0)
        dieWithError("Password length must not be negative");
    char passString[passStringLen];

    /* Create a datagram/UDP socket */
    if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
        dieWithError("socket() failed");

    /* Construct the server address structure */
    memset(&servAddr, 0, sizeof(servAddr));    /* Zero out structure */
    servAddr.sin_port = htons(atoi(servPort));     /* Server port */
    int ptonRtn = inet_pton(AF_INET, servName, &(servAddr.sin_addr));
    
    // Resolve domain name to IP address
    if(ptonRtn == 0) 
    {
        resolveName(servName, &servAddr);
        servIP = inet_ntoa(servAddr.sin_addr);
        printf("%s\n", servIP);
    }

    for(;;) 
    {
        // Generate password
        genPass(passString, passStringLen);

        /* Send the string to the server */
        printf("passwordBreaker (client): Send the string: %s to the server: %s \n", passString, servIP);
        if (sendto(sock, passString, passStringLen, 0, (struct sockaddr *)
                   &servAddr, sizeof(servAddr)) != passStringLen)
          dieWithError("sendto() sent a different number of bytes than expected");
        
        /* Recv a response */
        printf("passwordBreaker (client): And now wait for a response... \n");
        fromSize = sizeof(fromAddr);
        if ((respStringLen = recvfrom(sock, buffer, PASSMAX, 0,
             (struct sockaddr *) &fromAddr, &fromSize)) != passStringLen)
            dieWithError("recvfrom() failed");
        
        if (servAddr.sin_addr.s_addr != fromAddr.sin_addr.s_addr)
        {
            fprintf(stderr,"Error: received a packet from unknown source \n");
        }
        /* null-terminate the received data */
        buffer[respStringLen] = '\0';
        printf("passwordBreaker Client:  Received the following (%d bytes) data: %s\n",respStringLen,buffer);
    }

    close(sock);
    exit(0);
}

void resolveName(char* name, struct sockaddr_in *addr) {
    struct addrinfo hints, *servInfo, *p;
    struct sockaddr_in *h;
    int rv;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;

    // Store address information in servInfo
    if ((rv = getaddrinfo(name, "http", &hints, &servInfo)) != 0) 
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        dieWithError("getaddrinfo() failed");
    }

    // MIGHT NOT BE A NECESSARY CHECK
    if (servInfo->ai_addr == NULL)
        dieWithError("No valid IP addresses for given domain name");

    // Point to sockaddr_in to assign sin_addr to addr->sin_addr
    h = (struct sockaddr_in *) servInfo->ai_addr;
    addr->sin_addr = h->sin_addr;

    // Free temporary servInfo
    freeaddrinfo(servInfo);
}
