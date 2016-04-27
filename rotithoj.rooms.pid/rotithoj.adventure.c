#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//contains the characteristics of a room to be put into each file.
struct room{
	char * name;
	int num_connections;
	char * connections [6];
	char * room_type;
	
};
//a simple swap function.
void swap(char * a, char * b){
	char * temp = a;
	a = b;
	b = temp;
	
}
//takes in a file pointer and a room struct and writes all of the informaton from the
// room struct onto the file specified by the pointer
void write_to_file(struct room r1, FILE * c){
	int n = 1;
	fprintf(c, "ROOM NAME: %s\n", r1.name);
	for(n = 1; n < r1.num_connections + 1; n++){
		fprintf(c, "\nCONNECTION %d:" , n);
	    fprintf(c, r1.connections[n - 1]);
	}
		fprintf(c, "\nROOM TYPE: %s", r1.room_type);
	
		
}
//tests to see of the specified string is one of the connections of the specified
//room struct
int contains(char * c, struct room r1){
	int i = 0;
	for(i=0; i < r1.num_connections;i++)
		if(strcmp(c, r1.connections[i]) == 0)
			return 1;
	return 0;
}
int main(){
	//sets a random seed so rand() returns different values with each run
    srand(time(NULL));
	//opens up 7 files for rooms. Each file is a room.
		FILE * f = fopen("room1", "w+");
	FILE * f2 = fopen("room2", "w+");
	FILE * f3 = fopen("room3", "w+");
	FILE * f4 = fopen("room4", "w+");
	FILE * f5 = fopen("room5", "w+");
	FILE * f6 = fopen("room6", "w+");
	FILE * f7 = fopen("room7", "w+");
	//allocates memory for 7 rooms.
	struct room * r  = malloc(sizeof(struct room) * 7);
	int i = 0;
	int j = 0;
	int start_index = 0;
	int end_index = 0;
	int name_idx;
//hardcoded array of 10 room names that can be chosen from.
	char * names [10] = {"bedroom", "garage", "bathroom", "kitchen", "pantry", "attic", "basement", "weightroom", "lounge", "patio"};	
	//array to hold the selected names by the algorithm
	char * names2 [7];
	int i_minusone = 0;
	//randomly picks an index to be the start index, which will set the START_ROOM
	start_index = rand() % 7;
	//randomly picks an index to be the end index, which will set the END_ROOM
	end_index = rand() % 7;
	//makes sure the 2 indices are different
	if(start_index == end_index)
		end_index = (end_index + 5)%7;
	//pseudorandom algorithm to guarantee a different name for each room`
	for(i = 0; i < 7; i++){
		name_idx = (i*i*i) % 10;
		//puts the room name into the room struct
		r[i].name = names[name_idx];
		//accounts for the name for ruture reference
		names2[i] = names[name_idx];
		
	}
	
	
	
	for(i = 0; i < 7; i++){
//randomly generates 3-6 connections for each room	
	int connections = rand() % 4 + 3;
		r[i].num_connections = connections;
	   

//randomly generates connections for each room
	for(j = 0; j < 7; j++){
		int idx = rand() % 7;
//makes sure that the room does not connect to itself
		if(names2[idx] == r[i].name)
			idx = (idx + 2) % 7;
		r[i].connections[j] = malloc(sizeof(char *)*20);
		 strcpy(r[i].connections[j],names2[idx]);
	}
	//if the counter is at the start index, it is called START_ROOM		
		if(i == start_index)
			r[i].room_type = "START_ROOM";
		//if the counter is at the end index, it is called END_ROOM		
		else if(i == end_index)
			r[i].room_type = "END_ROOM";
		//otherwise it is a MID_ROOM
		else
			r[i].room_type = "MID_ROOM";
				}
	int x = 0;
//iteratively writes each struct to a file
	for(x = 0; x < 7; x++){
		if(x == 0) 
				write_to_file(r[x], f);
		else if(x == 1)
				write_to_file(r[x], f2);
		else if(x == 2)
				write_to_file(r[x], f3);
		else if(x == 3)
				write_to_file(r[x], f4);
		else if(x == 4)
				write_to_file(r[x], f5);
		else if(x == 5)
				write_to_file(r[x], f6);
		else if(x == 6)
				write_to_file(r[x], f7);
}
//since we are done writing, the files are closed
fclose(f);
fclose(f2);
fclose(f3);
fclose(f4);
fclose(f5);
fclose(f6);
fclose(f7);
	int k = 0;		
	int l = 0;
	int m = start_index;
	int n = 0;	
	char * travel_path [100];
	int p_iter = 0;
FILE * curFile;
	char input1 [256];
	struct room cur = r[start_index];
		char * token;
		//makes sure we are not at the END_ROOM
	while(strcmp(cur.room_type, "END_ROOM")){
	//opens the appropriate file for reading
		if(m == 0)
			curFile =  fopen("room1", "r");
		else if(m == 1)
			curFile =  fopen("room2", "r");
			else if(m == 2)
			curFile =  fopen("room3", "r");
			else if(m == 3)
			curFile =  fopen("room4", "r");
			else if(m == 4)
			curFile =  fopen("room5", "r");
			else if(m == 5)
			curFile =  fopen("room6", "r");
			else if(m == 6)
			curFile =  fopen("room7", "r");
	//parses the name of the room and prints it out to the user
		int ct = 0;
			fgets(input1, 256, curFile);
		token = strtok(input1, " ");
		for(n = 0; n < 2; n++)
			token = strtok(NULL, " ");
		travel_path[p_iter] = cur.name;
		p_iter++;
		printf("\nCURRENT LOCATION: ");
		printf(token);
		//displays all possible connections, each separated by a comma
		printf("\nPOSSIBLE CONNECTIONS: ");
		fgets(input1, 256, curFile);
		/*for(l = 0; l < cur.num_connections; l++){
			fgets(input1, 256, curFile);
			token = strtok(input1, " ");
					for(n = 0; n < 2; n++)
			token = strtok(NULL, " ");
		printf(token);
		printf(" ,");
		
		}*/
		for(l = 0; l < cur.num_connections; l++){
			printf(cur.connections[l]);
			printf(", ");
		}


			//asks the users where they want to go next
		printf("\nWHERE TO?>");
		scanf("%s", &input1);
		//makes sure that the room that the user specified exists and can be accessed
		//from the current room.
		for(m = 0; m < 7; m++)
			if(strcmp(input1,r[m].name) == 0 && contains(input1,cur)){
				cur = r[m];
				ct++;
				break;
			}
			//if the room is invalid, the user gets an error message
			if(ct == 0){
			printf("HUH? I DON'T UNDERSTAND THAT ROOM. TRY AGAIN.");
		    
		}
		k++;
        
	}
	//adds the user's room choice to an array for future use, if it is valid
	travel_path[p_iter] = input1;
	p_iter++;
	int p_tempcount = 0;
	p_tempcount = p_iter;
	p_iter = 0;
	//once the user has exited the game loop, a congratulatory message is printed.
	//the number of steps and the path history is printed for the user.
	printf("YOU HAVE FOUND THE END ROOM. COMGRATULATIONS!\n");
	printf("YOU TOOK");
	printf(" %d", k);
	printf(" STEPS. ");
	printf("YOUR PATH TO VICTORY WAS: \n");
	for(p_iter = 0; p_iter < p_tempcount; p_iter++){
		printf(travel_path[p_iter]);
		printf("\n");
	}
    //closes the file
		fclose(curFile);
		//frees allocated memory
for(i = 0; i < 7; i++)
	for(j = 0; j < r[i].num_connections; j++)
	free(r[i].connections[j]);
free(r);
return 0;
}
				//write these to files with the message.
				//also write room type. create coutner variable. at end, display value of 
				//counter variable.
				//pick a number between 1 and 10, make it the start, do same for end. for all others, 
				//assign mid.
				