//=========================================================
//CS 433 Assignment 2
//Your names: Jasmine Meyer and Birhane Diarra
//File type: Shell Header File
//===========================================================
#pragma once
#include <vector>
using namespace std;

const int MAX = 50;									// max length of a command



class Shell {
public:
	bool isRunning;										// if program is running
	void parseline(char buffer[], char * args[]);		// parses the command line into arguments to be executed as shell command or user command
	void executeShellCommand(char * args[]);				// executes shell commands
	void executeUserCommand(char * arg[]);					// executes user commands
	void saveCommand(char command[]);					// saves commands into history feature
	bool isUserCommand(char * arg[]);					// Checks if command is a shell command or a user one
	Shell();											// default constructor with no arguments

private:
	 vector<string> history;					// list of command history
	bool ampersand;										// true if "&" was present in command
	void displayHistory();								// displays commands from history feature
};