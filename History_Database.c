#include"History_Database.h"

void fillCommandsFromFile(char* file_name, char* short_term_history[7],
	History_List* long_term_history);
void addCommandsToFile(char* file_name, char* short_term_history[7],
	History_List* long_term_history);
int getHowManyCommandsInFile(char* file_name);
void fillShortHistory(FILE* history_file, char* short_term_history[7]);
void fillLongHistory(FILE* history_file, History_List* long_term_history,int number_of_long);
void addShortCommandsToFile(FILE* history_file, char* short_term_history[7]);
void addLongCommandsToFile(FILE* history_file, History_List* long_term_history);

/* fill the commands to the stores from the file */
void fillCommandsFromFile(char* file_name, char* short_term_history[7],
	History_List* long_term_history) {

	int long_term_history_number = 0;
	int command_count = getHowManyCommandsInFile(file_name);
	if (_access(file_name, 0) == 0) // _access(filename,0), checks if a file is exists in my program file, if it exist the function returns 0. 
	{
		FILE* history_file = fopen(file_name, "r");
		fillShortHistory(history_file, short_term_history);
		long_term_history_number = command_count - getShortHistoryNumber(short_term_history);
		fillLongHistory(history_file, long_term_history, long_term_history_number);
		fclose(history_file);
	}
}

/* adds the commands to the text file */
void addCommandsToFile(char* file_name, char* short_term_history[7],
	History_List* long_term_history) {

	FILE* history_file = fopen(file_name, "w");
	addShortCommandsToFile(history_file, short_term_history);
	addLongCommandsToFile(history_file, long_term_history);
	fclose(history_file);
}

/* returns how many commands in file ( short history commands and long history commands ) */
int getHowManyCommandsInFile(char* file_name) {
	char buffer[255];
	int count = 0;
	if (_access(file_name, 0) == 0)
	{
		FILE* history_file = fopen(file_name, "r");
		while (!feof(history_file))
		{
			fgets(buffer, 255, history_file);
			count++;
		}
	}
	return count;
}

/* fills the short history array from text file */
void fillShortHistory(FILE* history_file, char* short_term_history[7]) {

	int number_of_commands = 1;
	char command[255];
	while (!feof(history_file) && number_of_commands <= 7) 
	{
		fgets(command, 255, history_file);
		if (command[strlen(command) - 1] == '\n')
			command[strlen(command) - 1] = '\0';
		short_term_history[number_of_commands - 1] = _strdup(command);
		number_of_commands++;
	}
}

/* fill long history list from the text file */
void fillLongHistory(FILE* history_file, History_List* long_term_history, int number_of_long) {

	char command[255];
	while (!feof(history_file)) {
		fgets(command, 255, history_file);
		if (command[strlen(command) - 1] == '\n')
			command[strlen(command) - 1] = '\0';
		append_LH_Head(long_term_history, command, number_of_long--);
	}
}

/* adds the short history commands to the text file */
void addShortCommandsToFile(FILE* history_file, char* short_term_history[7]) {

	int short_History_number = getShortHistoryNumber(short_term_history);
	for (int i = 0; i < 7; i++)
	{
		if (short_term_history[i])
		{
			fputs(short_term_history[i], history_file);
			if (i + 1 != short_History_number)
				fputs("\n", history_file);
		}
		else
			break;
	}
}

/* adds the long history commands to the text file */
void addLongCommandsToFile(FILE* history_file, History_List* long_term_history) {

	History_ListNode* current_node = long_term_history->tail;
	if (getLongHistoryNumber(*long_term_history))
		fputs("\n", history_file);

	while (current_node)
	{
		fputs(current_node->data, history_file);
		if (current_node->previous)
			fputs("\n", history_file);
		current_node = current_node->previous;
	}
}