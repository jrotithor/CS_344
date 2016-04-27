#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char * argv[]){
	//makes sure that the process runs in the background
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
	int text_size = 0;
	int a = 0;
	int b = 0;
	int c = 0;
int sockfd, newsockfd, portno;
     socklen_t clilen;
	 //initializes arrays for the buffer, key, and plaintext
     char buffer[1000000];
	 char key[1000000];
	 char text[1000000];
     struct sockaddr_in serv_addr, cli_addr;
     int n;
	 //makes sure the user provided a port
     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
	 //opens up a socket
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
	 //stores the port supplied by the user in the command line
     portno = atoi(argv[1]);
	 //initializes the server
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
	 //accepts the connections from a client
	 while(1){
     newsockfd = accept(sockfd, 
                 (struct sockaddr *) &cli_addr, 
                 &clilen);
     if (newsockfd < 0) 
          error("ERROR on accept");
	  //forks off a child to do the decryption
	  new_pid = fork();
	  if(new_pid == 0){
     bzero(buffer,1000000);
	 //reads from the client
     n = read(newsockfd,buffer,1000000);
	 //sets up the size of the text file
	 for(i = 0; i < 1000000; i++)
		 if(buffer[i] != '\n')
			 ;
		 else
			 break;
		 text_size = i;

//copies the plaintext from the buffer into a string called text
	 for(i = 0; i < text_size; i++)
		 if(buffer[i] != '\n')
			 text[i] = buffer[i];
		 else
			 break;
j = 0;
i++;
//copies the key from the buffer into a string called key
    for(i; i < 1000000; i++)
		if(buffer[i] != '\n'){
			key[j] = buffer[i];
			j++;
		}
		else
			break;
//sets up an array for the ciphered message
	 char coded_message [text_size];
	//if the character is a space, it temporarily gets an ascii value below 'A' to make addition easier.
	 	for(i = 0; i < text_size; i++){
		if(text[i] == ' '){
		   text[i] = '@';

		}
		if(key[i] == ' '){
		   key[i] = '@';

		}
			//performs the ciphering. Turns the ascii values into corresponding integer values and adds them together.
		a = (int)text[i];
		b = (int)key[i];
		a -= 64;
		b -= 64;
		c = a + b;
	//if the sum is too high, make it between 0 and 26.
		c = c % 27;
		c += 64;

		//puts the character into the coded message. If the character has an ascii value below 'A', it becomes a space.
		coded_message[i] = (char)c;
		if(coded_message[i] == '@')
			coded_message[i] = ' ';
	}
		

//writes the message to the client
   n = write(newsockfd,coded_message,text_size);

	  //closes the connection
    
     close(sockfd);
	  }
	   close(newsockfd);
}
	
	

		
	
	return 0;
}