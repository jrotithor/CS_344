#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
int main(int argc, char * argv[]){
	//sets up the randomization of characters
	srand(time(NULL));
	FILE * fptr;
	
	int i = 0;
	int val = 0;
	int key_val = 0;
	//stores the size of the key passed by the user
    val	= atoi(argv[1]);
	char key [val + 1];
	//creates a random character for each iteration until a string the size of the number passed by the user is created
	for(i = 0; i < val; i++){
		
		key_val = rand()% 27 + 65;
		//accounts for space characters
	    if(key_val == 91)
			key[i] = ' ';
		else{
		//stores the character into the string
		key[i] = (char)key_val;
		
		}
	}
	
//prints out the string of random characters
for(i = 0; i < val; i++){
		printf("%c", key[i]);
		
	}


	printf("\n");
	return 0;
}