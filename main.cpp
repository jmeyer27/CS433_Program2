//
//todo history feature with command !!
//input and output
//




#include <iostream> //project is page 204 of textbook
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "Shell.h"

int main(){
cout << "CS 433 Programming assignment 1\n"
	"Author: Birhane Diarra and Jasmine Meyer\n"
	"Date: 10/9/2021\n"
	"Course: CS433 (Operating Systems)\n"
	"Description : Program to implement a priority ready queue of processes\n"
	"=================================" << endl;

  Shell osh;


// while(osh.isRunning){
//   char buffer[MAX];					// command buffer
// 	char buffer_save[MAX];				// used to save the command
// 	char * args[MAX / 2 + 1];			// arguments of the command.




//   printf("osh>");
//   fflush(stdout);

//   std::cin.getline(buffer, MAX);//read user input
//   void execShellCommand(char * args[]);// this step  forks child using fork()



//   //child invokes execvp(args[0]. args), check for & here
//   //parent invokes wait unless command included &






  while (osh.isRunning) {
		char buffer[MAX];					// command buffer
		char buffer_save[MAX];				// used to save the command
		char * args[MAX / 2 + 1];			// arguments of the command.

		std::cout << "osh> ";
		std::cout.flush();

		std::cin.getline(buffer, MAX);		// reads command from input.		
		strcpy(buffer_save, buffer);			// copy the buffer

		osh.parseline(buffer, args);			// buffer parses into arguments.

		if (osh.isUserCommand(args)) {
			osh.execUserCommand(args);			// command is user command.
		}

		else {
			osh.saveCommand(buffer_save);		// save command if shell command.
			osh.execShellCommand(args);			// command is shell command.
		}
}//end while

return 0;


}