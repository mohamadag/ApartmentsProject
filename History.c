#include "Commands.h"

char* history_command[] = { "short_history","history","!!","!","^" };
History_List createLongTermHistory();
void addToStore(char*short_term_history[7], History_List* long_term_history,char* command);
void append_LH(History_List* list, char* command);
void append_LH_Head(History_List* list, char* command,int index);
void clean_LH(History_List list);
void print_LH(History_List list);
void print_SH(char*short_term_history[7], int long_history_number);
void printHistory(History_List list, char*short_term_history[7]);

void reOrder(char**short_term_history,short int short_history_num);
void updateStores(char*short_term_history[7], History_List* list);
short int getShortHistoryNumber(char*short_term_history[7]);
int getLongHistoryNumber(History_List list);
void executeHistoryCommand(char* command, Apartment_List* apartments,
	char*short_term_history[7], History_List* long_term_history);
char* getCommandNumber(char*short_term_history[7], History_List* long_term_history,
	int command_number);
void str_replace(char *target, const char *needle, const char *replacement);
void checkMemoryAllocation_H(void* ptr);

/* creates an empty list */
History_List createLongTermHistory() {

	History_List new_list;
	new_list.head = new_list.tail = NULL;
	return new_list;
}

/* creates a node */
History_ListNode* createNode_H(char* command) {

	static int command_index = 1;
	History_ListNode* newNode;
	newNode = (History_ListNode*)malloc(sizeof(History_ListNode));
	checkMemoryAllocation_H(newNode);
	newNode->index = command_index++;
	newNode->data = _strdup(command);
	newNode->previous = NULL;
	newNode->next = NULL;
	return newNode;
}

/* insert to the end of the list */
void append_LH(History_List* list, char* command) {

	History_ListNode* new_node = createNode_H(command);
	if (list->head == NULL)
		list->head = list->tail = new_node;
	else
	{
		new_node->previous = list->tail;
		list->tail->next = new_node;
		list->tail = new_node;
	}
}

/* insert to the start(head) of the list */
void append_LH_Head(History_List* list, char* command,int index) {

	History_ListNode* new_node = createNode_H(command);
	new_node->index = index;
	if (list->head == NULL)
		list->head = list->tail = new_node;
	else 
	{
		new_node->next = list->head;
		list->head->previous = new_node;
		list->head = new_node;
	}
}

/* frees the list */
void clean_LH(History_List list) {

	History_ListNode* current_node = list.head;
	History_ListNode* next_node;
	while (current_node) 
	{
		next_node = current_node->next;
		free(current_node->data);
		free(current_node);
		current_node = next_node;
	}
}

/* print the long history (print the long history list) */
void print_LH(History_List list) {

	History_ListNode* current_node = list.head;
	while (current_node) 
	{
		printf("%d: %s\n\n", current_node->index, current_node->data);
		current_node = current_node->next;
	}
}

/* print short history list */
void print_SH(char*short_term_history[7], int long_history_number) {

	int long_command_number = long_history_number;
	int shor_command_index = 1;
	if (long_command_number > 0)
	{
		for (int i = 6; i >= 0; i--)
		{
				printf("%d: %s\n\n", long_command_number + 7 - i, short_term_history[i]);
		}
	}
	else
	{
		for (int i = 6; i >= 0; i--) 
		{
			if (short_term_history[i])
				printf("%d: %s\n\n", shor_command_index++, short_term_history[i]);
		}
	}
}

//checks memory allocation
void checkMemoryAllocation_H(void* ptr) {

	if (ptr == NULL) 
	{
		puts("Memory allocaton Faild\n");
		exit(1);
	}
}

/* numbers the long history commands (puts number to the commands in order) */
int getLongHistoryNumber(History_List list) {

	int commands_number = 0;
	History_ListNode* current_command = list.head;
	while (current_command)
	{
		commands_number++;
		current_command = current_command->next;
	}
	return commands_number;
}

/* numbers the short history commands (puts number to the commands in order) */
short int getShortHistoryNumber(char*short_term_history[7]) {

	short commands_num = 0;
	for (int i = 0; i < 7; i++)
	{
		if (short_term_history[i])
			commands_num++;
		else
			break;
	}
	return commands_num;
}

/* if the array of short history is not full, reorder function adds the command to the first element of the array and moves the other commands by 1 to the right */
void reOrder(char**short_term_history, short int short_history_num){

	char* previous_command;
	char* next_command;
	previous_command = _strdup(short_term_history[0]);
		for (int i = 0; i < short_history_num; i++) 
		{
			next_command = _strdup(short_term_history[i + 1]);
			short_term_history[i + 1] = _strdup(previous_command);
			previous_command = _strdup(next_command);
	}
}


/* updates the stores, splits to the appropriate function, if the short history full as we call to reorder full... etc */
void updateStores(char*short_term_history[7], History_List* list) {

	short int short_history_num = getShortHistoryNumber(short_term_history);
	if (short_history_num < 7) 
		reOrder(short_term_history,short_history_num);
	 else 
	 {
		 append_LH(list, short_term_history[6]);
		 reOrder(short_term_history,6);
	 }
}

/* adds command to the appropriate store */
void addToStore(char*short_term_history[7], History_List* long_term_history,char* command) {

	if (!strstr(command, "history")&&!strstr(command,"!")) 
	{ 
		updateStores(short_term_history, long_term_history);
		short_term_history[0] = _strdup(command);
	}
}

/* print the short history and the long history */
void printHistory(History_List list, char*short_term_history[7]) {

	print_LH(list);
	int long_history_number = getLongHistoryNumber(list);
	print_SH(short_term_history, long_history_number);
}

/* returns the command with the number that in the input */
char* getCommandNumber(char*short_term_history[7], History_List* long_term_history,
	int command_number) {

	int long_command_number = getLongHistoryNumber(*long_term_history);
	if (command_number <= long_command_number) 
	{
		History_ListNode* current_command = long_term_history->head;
		while (current_command) 
		{
			if (current_command->index == command_number)
				return current_command->data;
			current_command = current_command->next;
		}
	}
	else 
	{
		if (long_command_number) 
		{
			for (int i = 0; i < 7; i++) 
			{
				if (long_command_number + 7 - i == command_number)
					return short_term_history[i];
			}
		}
		else
		{
			for (int i = 6; i >= 0; i--) 
			{
				if (7 - i == command_number)
					return short_term_history[7-i-1];
			}
		}
	}
	return ""; // becaue I know that the input correct 
}

/* replace all of the appears of string in a certain command to another string (string or int, doesn't matter) */
void str_replace(char *target, const char *needle, const char *replacement){

	char buffer[1024] = { 0 };
	char *insert_point = &buffer[0];
	const char *tmp = target;
	size_t needle_len = strlen(needle);
	size_t repl_len = strlen(replacement);
	while (1) 
	{
		const char *p = strstr(tmp, needle);
		if (p == NULL) {
			strcpy(insert_point, tmp);
			break;
		}
		memcpy(insert_point, tmp, p - tmp);
		insert_point += p - tmp;
		memcpy(insert_point, replacement, repl_len);
		insert_point += repl_len;
		tmp = p + needle_len;
	}
	strcpy(target, buffer);
}

/* splits the history command to parts and calls to the appropriate functions  */
void executeHistoryCommand(char* command, Apartment_List* apartments,
	char*short_term_history[7], History_List* long_term_history) {

	if (strcmp(command, history_command[0]) == 0)
		print_SH(short_term_history, getLongHistoryNumber(*long_term_history));
	else if (strcmp(command, history_command[1]) == 0)
		printHistory(*long_term_history, short_term_history);
	else if (strcmp(command, history_command[2])==0)
	{
		addToStore(short_term_history, long_term_history, short_term_history[0]);
		char* copy_command = _strdup(short_term_history[0]);
		executeCommand(copy_command, apartments, short_term_history, long_term_history);	
	}
	else if (strstr(command, history_command[4]))
	{
		char command_type;
		int command_number;
		char* re_command;
		sscanf(command, "%c%d", &command_type, &command_number);
		re_command = _strdup(getCommandNumber(short_term_history,
			long_term_history, command_number));
		char* token = strtok(command, "^");
		char* old_value = strtok(NULL, "^");
		char* new_value = strtok(NULL, "^");
		str_replace(re_command, old_value, new_value);
		addToStore(short_term_history, long_term_history, re_command);
		executeCommand(re_command, apartments, short_term_history, long_term_history);
	}
	else 
	{
		char command_type;
		int command_number;
		char* re_command;
		sscanf(command, "%c%d", &command_type, &command_number);
		re_command= _strdup(getCommandNumber(short_term_history, 
			long_term_history, command_number));
		addToStore(short_term_history, long_term_history, re_command);
		executeCommand(re_command, apartments, short_term_history, long_term_history);
	}
}