#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char * argv[]){
	//makes sure that the process is in the background
if(argc > 2){
	if(strcmp(argv[2], "&")){
		printf("This needs to be a background process");
		exit(1);
	}
}
	pid_t new_pid;
	int x = 0;
	int i = 0;
	int j = 0;
	int cipher_size = 0;
	int a = 0;
	int b = 0;
	int c = 0;
int sockfd, newsockfd, portno;
     socklen_t clilen;
     //initializes the buffer and key and the cipher
	 char buffer[1000000];
	 char key[1000000];
	 char cipher[1000000];
     struct sockaddr_in serv_addr, cli_addr;
     int n;
	 //makes sure that the user provided a port
     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
	 //creates a socket
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
	 //stores the port passed in the command line
     portno = atoi(argv[1]);
	 //initializes the server struct
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
	 //binds the socket to a port
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
			  //listens for connections
     listen(sockfd,5);
     clilen = sizeof(cli_addr);
	 while(1){
		 //accepts a connection from the client once one is recieved
     newsockfd = accept(sockfd, 
                 (struct sockaddr *) &cli_addr, 
                 &clilen);
     if (newsockfd < 0) 
          error("ERROR on accept");
	  //forks off a child to do the decryption
	  new_pid = fork();
	  if(new_pid == 0){
     bzero(buffer,1000000);
	 //reads the message from the client
     n = read(newsockfd,buffer,1000000);
	 //sets the size of the cipher text
	 for(i = 0; i < 1000000; i++)
		 if(buffer[i] != '\n')
			 ;
		 else
			 break;
		 cipher_size = i;
	//sets up the cipher string with the encoded message
	 for(i = 0; i < cipher_size; i++)
		 if(buffer[i] != '\n')
			 cipher[i] = buffer[i];
		 else
			 break;
	
j = 0;
i++;
//puts the key into a string 
    for(i; i < 1000000; i++)
		if(buffer[i] != '\n'){
			key[j] = buffer[i];
			j++;
		}
		else
			break;

	 char decoded_message [cipher_size];
//sets up the space character so its ascii value is 1 greater than 'Z' to make subtraction easier
	 	for(i = 0; i < cipher_size; i++){
		if(cipher[i] == ' '){
		   cipher[i] = '[';

		}
		if(key[i] == ' '){
		   key[i] = '[';

		}
			//Subtracts the value of the key from the cipher, and if it is less than 0, 27 is added to it to make it an integer corresponding to a letter
		a = (int)cipher[i];
		b = (int)key[i];
		a -= 64;
		b -= 64;
		c = a - b;

		if(c < 0)
			c += 27;
		c = c % 27;
		//adds 64 to make the number an ascii value
		c += 64;
	
		//puts the letter into the decoded message array, and if its value is below 'A', make it a space
		decoded_message[i] = (char)c;
		if(decoded_message[i] == '@')
			decoded_message[i] = ' ';
	}
	
//write rhe message to the client
    n = write(newsockfd,decoded_message,cipher_size);
  //close the connection
	  
    
     close(sockfd);
	  }
	   close(newsockfd);
	 }
	

		
	
	return 0;
}