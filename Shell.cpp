//=========================================================
//CS 433 Assignment 2
//Your names: Jasmine Meyer and Birhane Diarra
//File type: Shell Class File
//Purpose: Creates Shell, reads input commands and executes child processes to run commands. Includes history feature.
//===========================================================
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sys/wait.h>
#include <unistd.h>
#include "Shell.h"
using namespace std;


// Default constructor for Shell program with two variables. 
Shell::Shell()
{
	isRunning = true;//boolean if process is running or not
	ampersand = false;//boolean to see if parent process needs to wait()
}


// PURPOSE: Executes a shell command. After readin guser input, will fork child using fork(), the child will invoke execvp(), and will check for & (ampersand) to see if it is necessary to wait for child.
// PARAMETER: char args[] = the arguments in the command.
void Shell::executeShellCommand(char * args[])
{
	pid_t pid = fork();			// fork a child process using fork()

	if (pid == 0) { // child process base case
		execvp(args[0], args);	// Child invokes execvp
		cout << "execvp: command not found" << endl;//not found
		exit(1); 	//quits process	
	}

	// if is a parent process
	else if (pid > 0) {
		if (ampersand == false) { //if command not included & (ampersand), parent will invoke wait()
			wait(NULL);			
		}
	}

	// fork failed if pid < 0
	else {
		cout << "Fork Failed" << endl;
		exit(1);
	}
}



// PURPOSE: Executes a user command.
// PARAMETER: char arg[] = arguments of the command.
void Shell::executeUserCommand(char* arg[])
{
	string command(arg[0]);


  // if command is history, display history
	if (command == "history") {
		displayHistory();
	}
	// if command is exit, process is no longer running and terminates in program
	else if (command == "exit") {
		isRunning = false;
	}


	// When command is "!", will have to choose to select a command from the command history
	else if (command[0] == '!') {
		char buffer[MAX];
		char * args[MAX / 2 + 1];
		int num;	

		// When command is "!!", most recent command is run again
		if (command == "!!") {

			// If the history is empty, tell user
			if (history.empty()) {
				cout << "No commands in history." << endl;
				return;
			}

			num = history.size();
		}

		// else command is "!N" and selects the Nth command
		else {

			// separates ! and N to be used
			string temp = command.substr(1, command.length());			
			num = atoi(temp.c_str());	// num = N

			// min = minumum command for history
			int min = (history.size() < 10) ? 0 : history.size() - 10;

			// if command is not in history, either too big or too small N
			if (num > history.size() || num < min + 1) {
				cout << "Command not valid in history." << endl;
				return;
			}
		}
		// command selection to be sent to user
		cout << history[num - 1] << endl; 

		strcpy(buffer, history[num - 1].c_str());//copy command
		saveCommand(buffer);//save command
		parseline(buffer, args);//parse command
		executeShellCommand(args);//execute command
	}
}

// PURPOSE: Checks if the command is a user command or execShellCommand command.
// PARAMETER: char arg[] = the arguments in the command
// RETURN: true if user command or false if shell command.
bool Shell::isUserCommand(char * arg[])
{
	string command(arg[0]);//starts at beginning

	// If the command is a user command, return true
	if (command == "exit" || command == "history" || command[0] == '!') {
		return true;
	}

	// Otherwise command is a shell command, and returns false
	return false;
}


// PURPOSE: The buffer is parsed into arguments
// PARAMETERS: char buffer[] = the command, char args[] is the arguments in the command.
void Shell::parseline(char buffer[], char * args[])
{
	int i = 0;//start at 0

	char * p = strtok(buffer, " ");//separate whitespace from buffer
	while (p != NULL) { //while next char is not NULL, add to args[]
		args[i] = p;
		p = strtok(NULL, " ");
		i++;
	}

	// if & is at end of argument (args[]), remove it and set ampersand to TRUE
	if (strcmp(args[i - 1], "&") == 0) {
		args[i - 1] = NULL;
		ampersand = true;
	}

	else {
		// no ampersand, make end of argument NULL and set ampersand to FALSE
		args[i] = NULL;
		ampersand = false;
	}
}


// PURPOSE: Saves commands into history
// PARAMETER: char command[] is a command to be saved.
void Shell::saveCommand(char command[])
{
	string save(command);
	history.push_back(save);
}

// PURPOSE: To display the history of the commands issued to the Shell
void Shell::displayHistory()
{
	// if the history is empty, tell user
	if (history.empty()) {
		cout << "command history is empty" << endl;
	}

	// if the history is not empty
	else {//initialize starting place
		int startingPlace = (history.size() < 10) ? 0 : history.size() - 10;

		// display history
		for (int i = startingPlace; i < history.size(); i++) {
			cout << "  " << i + 1 << "  " << history[i] << endl;
		}
	}
}