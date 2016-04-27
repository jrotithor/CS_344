//Program:smallsh.c
//Author: Jaydeep Rotithor
//Date: 2/29/2016
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <signal.h>

#include <sys/wait.h>
//handles signals passed from the child process.
void sighandler(int artificial_argc){
	//fills up the sigaction struct with a set of signals and the takes an action
	//based on them.

	printf("%d", artificial_argc);
struct sigaction act;
act.sa_flags = 0;
sigfillset(&(act.sa_mask));
sigaction(SIGINT, &act, NULL);
	
}
int main(int argc, char* argv[]){

	int sig = 0;
	int x = 0;
	int i = 0;
	int r = 0;
	int status = 0;
	int exec_status = 0;
	int artificial_argc = 0;
	char * a;
	pid_t new_pid = -10;
	pid_t pid_arr [15];
	int pid_arr_idx = 0;
	char line [256];
	FILE * fread;
	FILE * fread2;
	int term_proc = 0;
	int exit_status = 0;
	while(1){

			int bg = 0;
		artificial_argc = 0;
		//checks to see if a backround process has completed before prompting the user
 waitpid(-1, &status, WNOHANG) ;
 //if the background process was terminated by a signal, a message is printed saying
 //the proces ID and which signal terminated the process.
	if(WIFSIGNALED(status)){
			printf("process id was: %d     ", pid_arr[term_proc]);
			term_proc++;
        sig = WTERMSIG(status);
		printf("Terminated by signal %d    ", sig);
		}
		//prompts the user
		printf(": ");
		fflush(stdout);
		//gets user input
		fgets(line, "%s", stdin);
		//deletes the newline character automatically appended by fgets
		size_t length = strlen(line);
		if(line[length - 1] == '\n')
			line[length - 1] = '\0';
		//allocates memory for an artificially created command line argument container.
		char * artificial_argv[256];
		for(i = 0; i < 256; i++){
			artificial_argv[i] = malloc(sizeof(char)* 50);
		
		}
		//stores the first argument from the user into the command line argument container.
		a = strtok(line, " ");

			artificial_argv[0] = a;
	
			

		i = 0;
		int count1 = 0;
		//loops through the rest of the arguments and adds each one to the command line argument container.
		while(a != NULL){
			a = strtok(NULL, " ");
	
			artificial_argv[i + 1] = a;

			
			artificial_argc++;
			i++;
	
		}




//if the user passed nothing, prompt again
if(artificial_argv[0] == NULL)
	continue;
//if the user said to exit, terminate the program gracefully
else if(strcmp(artificial_argv[0], "exit") == 0){
		return 0;

		}
	//if the user requests the status, print out the exit status of the last command
else if(strcmp(artificial_argv[0], "status") == 0){


	printf("Exit status: %d   ", exit_status);
		exit_status = 0;
		}
//if the user requests a directory change and specifies a directory, change to that directory.		
else if(strcmp(artificial_argv[0], "cd") == 0 && artificial_argv[1] != NULL){
	chdir(artificial_argv[1]);
	exit_status = 0;
}
//if the user specifies  a change in directory without any arguments, go to the home directory.
else if(strcmp(artificial_argv[0], "cd") == 0){
		chdir(getenv("HOME"));
		exit_status = 0;
		}

	//if the user gives a command other than these 3, fork off a chold process.
	else{
		
		new_pid = fork();

//if the user wants to run the process in the background, set the background variable to 1/
if(strcmp(artificial_argv[artificial_argc - 1], "&") == 0){
	bg = 1;
	//redirect from /dev/null, print the process ID and exit status, and store the process ID of the child in and Array. 
	  printf("%d      ", new_pid);
				    dup2("/dev/null", 0);
					printf("Exit status: %d   ", exit_status);
					pid_arr[pid_arr_idx] = new_pid;
					pid_arr_idx++;
}
	//if the fork failed, print a message alerting the user.
		if(new_pid < 0){
			printf("Fatal error forking");
		}
		//enter the child process.

		if(new_pid == 0){
			//Loops through looking for the redirection command. if the user requests redirection from a file, open up the file requested by the user, and print an error if this cannot be done.
				for(i = 0; i < artificial_argc; i++){
	if(artificial_argv[i][0] == '<')  {
		r = 1;
		
		fflush(stdout);
		fread = open(artificial_argv[i + 1], O_RDONLY, 0777);
		if(fread == -1){
			perror("open");
			status = 1;
			exit(1);

		}
		
//redirects input from the file specified by the user to stdin.
		dup2(fread,0);
	//executes the arguments before the redirection, and prints and error if this cannot be done.
		exec_status = execlp(artificial_argv[0], artificial_argv[0], NULL);
	perror("exec");
		exit(1);
	}
	}
	//Loops through looking for the redirection command. If the user requests redirection to a file, open op the file requested and print an error if this cannot be done.
for(i = 0; i < artificial_argc; i++){
	if(artificial_argv[i][0] == '>')  {
			
		r = 1;
		printf(artificial_argv[i + 1]);
		fread2 = open(artificial_argv[i + 1],O_RDWR|O_CREAT|O_TRUNC, 0777);
		if(fread2 == -1){
			perror("open");
			exit(1);
		}
		//redirects output from the user(stdout) to the file.
		dup2(fread2,1);
//executes the arguments before the redirection, and prints and error if this cannot be done.
		exec_status = execlp(artificial_argv[0], artificial_argv[0], NULL);
		perror("exec");
		exit(1);
		
	}
}
//if the process is to be run in the background, execute it using all of the arguments before the background command &.
	if(strcmp(artificial_argv[artificial_argc - 1], "&") == 0){
		
					 
					
			
				r = 1;
			
					execlp(artificial_argv[0], artificial_argv[0], artificial_argv[1], NULL);
		
				}	

		
			
	//if the user did not request redirection or bacground processes, execute the process and print an error if something went wrong.
					
		exec_status = execvp(artificial_argv[0], artificial_argv);

	
		perror("exec");
		exit(1);
		
	
		}
		
		
		//wait for the child only if the child is not in the background.
		if(bg == 0)
		waitpid(new_pid, &status, 0);
		//get the exit status of the last command.
		exit_status = WEXITSTATUS(status);
		//if the foreground child process was terminated by a signal, a message saying the process ID of the child and the signal terminating it is printed to the user.
		if(WIFSIGNALED(status)){
			printf("process id was: %d     ", new_pid);
        sig = WTERMSIG(status);
		printf("Terminated by signal %d    ", sig);
		}
	;
		
	}
		
	}
}