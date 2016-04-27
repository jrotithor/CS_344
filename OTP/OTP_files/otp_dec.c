#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
//prints out an error as necessary
void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char * argv[]){
	//makes sure the user gave the right number of arguments
	if(argc < 4 || argc == 5){
		printf("Error: Too few arguments");
		exit(1);
	}
	FILE * f1;
	FILE * f2;
	int x = 0;
	int y = 0;
	int i = 0;
	char input [1000000];
	char input2 [1000000];
	f1 = fopen(argv[1], "r");
	f2 = fopen(argv[2], "r");
	fgets(input, 1000000, f1);
	fgets(input2, 1000000, f2);
	char decoded_message[1000000];
	x = strlen(input2);
	y = strlen(input);

//prints an error of the key is too short and exits
		if(x < y){
		printf("Error: %s is too short", argv[2]);
		exit(1);
		}
		//makes sure that the key has either uppercase letters or spaces.
	for(i = 0; i < x; i++)
		if((input2[i] < 'A' || input2[i] > 'Z') && input2[i] != ' '  && input2[i] != '\n'){
			printf("Error: bad input in keygen");
			printf("%d", i);
			exit(1);
		}
		//makes sure that the ciphertext has either uppercase letters or spaces.
		for(i = 0; i < y; i++)
		if((input[i] < 'A' || input[i] > 'Z') && input[i] != ' ' && input[i] != '\n'){
			printf("Error: bad input in text file");
			printf("%d", i);
			exit(1);
		}
	 int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[1000000];
	//prints the ciphertext and key to the buffer
    sprintf(buffer, "%s%sd", input, input2);
	int buflen = strlen(buffer);

//makes sure that the user passed in the right information and the right number of arguments.	
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
	//stores the port number
    portno = atoi(argv[3]);
	//creates a socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
	//gets infomation about the server
    server = gethostbyname("localhost");
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
	//initializes the server struct
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);

	//connects to the server
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
 //writes the buffer to the server
	n = write(sockfd,buffer,strlen(buffer));
    if (n < 0) 
         error("ERROR writing to socket");
 
    //fgets(buffer,255,stdin);


//reads the decrypred message from the server
	   n = read(sockfd,decoded_message,1000000);
    if (n < 0) 
         error("ERROR reading from socket");
	 //prints the decrypted message
    printf("%s\n",decoded_message);
 //closes the connection
    close(sockfd);
	
		
	return 0;
}