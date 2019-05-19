#ifndef __COMMANDS_H
#define __COMMANDS_H
#include"History.h"

void instructionsMessage();
char* getCommand();
void executeCommand(char* command, Apartment_List* apartments, char*short_term_history[7],
	History_List* long_term_history);

#endif

