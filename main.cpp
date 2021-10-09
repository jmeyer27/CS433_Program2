//=========================================================
//CS 433 Assignment 3
//Your names: Jasmine Meyer and Birhane Diarra
//File type: main.cpp
//Purpose: Creates Shell 
//===========================================================
#include <iostream> //project is page 204 of textbook
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "Shell.h"

int main(){
cout << "CS 433 Programming assignment 2\n"
	"Author: Birhane Diarra and Jasmine Meyer\n"
	"Date: 10/9/2021\n"
	"Course: CS433 (Operating Systems)\n"
	"Description : Program to serve as a shell interface that accepts user commands and executes each one in a separate process.\n"
	"=================================" << endl;

  Shell osh;

  //while shell is running, keep asking for commands to run processes
  while (osh.isRunning) {
		char buffer[MAX];					// array to hold chars from command line to be interpreted
		char history_buffer[MAX];				// used to save the command for history feature
		char * args[MAX / 2 + 1];			// arguments of the command

		std::cout << "osh> ";
		std::cout.flush();//keeps line clear for user input

		std::cin.getline(buffer, MAX);		// reads command from input.		r, buffer);			// copy the buffer

    //shell parses buffer for arguments
		osh.parseline(buffer, args);


    //checks if command is user command or shell command and executes
		if (osh.isUserCommand(args)) {
			osh.executeUserCommand(args);			
		}

		else {
      // saves command to history before executing
			osh.saveCommand(history_buffer);		
			osh.executeShellCommand(args);			
		}
}//end while

return 0;


}