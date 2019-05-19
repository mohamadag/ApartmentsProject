#ifndef __HISTORY_DATABASE_H
#define __HISTORY_DATABASE_H
#include "History.h"

void addCommandsToFile(char* file_name,char* short_term_history[7],
	History_List* long_term_history);

void fillCommandsFromFile(char* file_name, char* short_term_history[7],
	History_List* long_term_history);

#endif

