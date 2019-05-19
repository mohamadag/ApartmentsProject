#include "commands.h"

char* commands[] = { "add-an-apt","buy-an-apt","delete-an-apt","get-an-apt" };
char* get_commands[] = { "Enter","Date","MaximumPrice","MaximumNumRooms","MinimumNumRooms","s","sr"};

char* getCommand();
void instructionsMessage();
void executeCommand(char* command, Apartment_List* apartments, char*short_term_history[7],
	History_List* long_term_history);

void fillterToAdd(char* command, int*code, char**address, int*price, short int* rooms,
	Date* hire, Date* entry);
void add(char* command, Apartment_List* apartments);
void buy(char* command, Apartment_List* apartments);
void delete_an_apt(char* command, Apartment_List* apartments);
int getLastCode(Apartment_List* apartments);

/* returns a command from the input(user) */
char* getCommand(){
	printf(">> ");
	short logical_size = 0, physical_size = 1;
	char* command = (char*)malloc(sizeof(char));
	char character;
	do {
		scanf("%c", &character);
		if (logical_size == physical_size) {
			physical_size *= 2;
			command = (char*)realloc(command, physical_size * sizeof(char));
		}
		command[logical_size++] = character;
	} while (character != '\n');
	command[logical_size-1] = '\0';
	return command;
}

/* (Instruction) */
void instructionsMessage() {
	printf("Please enter one of the following commands:\n\n"
		"add-an-apt, get-an-apt, buy-an-apt or delete-an-apt\n\n"
	"For reconstruction commands, please enter:\n\n"
	"!!, !num, history, short_history or !num^str1^str2\n\n"
	"To exit, enter exit.\n\n");
}

/* filters the command, if it's get/add..etc */
void executeCommand(char* command, Apartment_List* apartments, char*short_term_history[7], 
	History_List* long_term_history) {

	if (strstr(command, commands[0]))
		add(command, apartments);
	else if (strstr(command, commands[1]))
		buy(command, apartments);
	else if (strstr(command, commands[2]))
		delete_an_apt(command, apartments);
	else if (strstr(command, commands[3]))
	{
		getFilter(command, apartments);// get
	}
	else // History Command
		executeHistoryCommand(command, apartments, short_term_history, long_term_history);	
}

/* split the get command, if it's MaximumPrice/MinimumRooms...etc */
void getFilter(char *command,Apartment_List *apartments)
{
	int sorted = 0;
	char command_type[30];
	Apartment_List new_list = createApartmentsList();
	copyApartments(apartments, &new_list);
	char* token = strtok(command, " ");
	token = strtok(NULL, "-");
	while (token != NULL) { // more than one command in get
		if (strstr(token, get_commands[0])) {
			int last_days;
			sscanf(token, "%s %d", command_type, &last_days);
			getEnterSince(&new_list, last_days);
		}
		else if (strstr(token, get_commands[1])) {
			Date input_date;
			sscanf(token, "%s %s", command_type, command_type);
			input_date.day = (command_type[0] - '0') * 10 + command_type[1] - '0';
			input_date.month = (command_type[2] - '0') * 10 + command_type[3] - '0';
			input_date.year = (command_type[4] - '0') * 1000 + (command_type[5] - '0') * 100 +
				(command_type[6] - '0') * 10 + (command_type[7] - '0');
			getFreeDate(&new_list, input_date);
		}
		else if (strstr(token, get_commands[2])) {
			int max_price;
			sscanf(token, "%s %d", command_type, &max_price);
			getMaximumPrice(&new_list, max_price);
		}
		else if (strstr(token, get_commands[3])) {
			int max_room;
			sscanf(token, "%s %d", command_type, &max_room);
			getMaximumRooms(&new_list, max_room);
		}
		else if (strstr(token, get_commands[4])) {
			int min_room;
			sscanf(token, "%s %d", command_type, &min_room);
			getMinimumRooms(&new_list, min_room);
		}
		else if (strstr(token, get_commands[5]) || strstr(token, get_commands[6])) {
			sortApartments(&new_list);
			if (strstr(token, get_commands[6]))
				sorted = 1; // from max to min
			else
				sorted = 0;
		}
		token = strtok(NULL, "-");
	}
	sorted ? printListOp_AP(new_list) : printList_AP(new_list);
}

/* split the add command to address/code/date.... etc, and puts them to the apartment by referrence */
void fillterToAdd(char* command, int*code, char**address, int*price, short int* rooms,
	Date* hire_date, Date* entry_date) {

	int local_code = *code;
	char* token = strtok(command, " ");
	*code = local_code+1;
	*address = _strdup(strtok(NULL, "\""));
	*price = atoi(strtok(NULL, " "));
	*rooms = atoi(strtok(NULL, " "));
	hire_date->day = atoi(strtok(NULL, " "));
	hire_date->month = atoi(strtok(NULL, " "));
	hire_date->year = atoi(strtok(NULL, " "))+2000;
	entryDate(entry_date);
}

/* gets the code of the last apartment */
int getLastCode(Apartment_List* apartments) {
	if (apartments->tail == NULL)
		return 0;
	else return apartments->tail->data.code;
}

/* adds a filled apartment to the end list apartment */
void add(char* command, Apartment_List* apartments) {

	Apartment new_apartment;
	int last_code = getLastCode(apartments);
	new_apartment.code = last_code;
	fillterToAdd(command, &new_apartment.code, &new_apartment.address,
		&new_apartment.price, &new_apartment.rooms,
		&new_apartment.date_of_hire, &new_apartment.date_of_add);
	append_AP(apartments, new_apartment);
}

/* deletes the bought apartment */
void buy(char* command, Apartment_List* apartments) {

	unsigned int found = 0, code;
	char* token = strtok(command, " ");
	code = atoi(strtok(NULL, " "));
	for (Apartment_ListNode* currentNode = apartments->head; currentNode != NULL && !found;
		currentNode = currentNode->next)
	{
		if (currentNode->data.code == code)
		{
			found = 1;
			omit_AP(apartments, currentNode);
		}
	}
}

/* deletes the apartments that has been added in the last 'x' days */
void delete_an_apt(char* command, Apartment_List* apartments){

	int last_days;
	Date date_of_day;
	char* token = strtok(command, " ");
	token = strtok(NULL, " ");
	last_days = atoi(strtok(NULL, " "));
	entryDate(&date_of_day);

	Apartment_ListNode *save_apartment,*current_apartment = apartments->head;
	while (current_apartment!=NULL) 
	{
		if (differenceOfDays(date_of_day, current_apartment->data.date_of_add) <= last_days)
		{
			save_apartment = current_apartment->next;
			omit_AP(apartments, current_apartment);
			current_apartment = save_apartment;
		}
		else
			current_apartment = current_apartment->next;	
	}
}

