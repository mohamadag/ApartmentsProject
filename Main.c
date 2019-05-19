#include"History_Database.h"
#include "Commands.h"

#define N 7
#define EXIT "exit"
#define APARTMENT_BIN "apartments.bin"
#define HISTORY_TXT "history.txt"

void main() 
{
	char* short_term_history[N] = { NULL };
	Apartment_List apartments = createApartmentsList();
	History_List long_term_history = createLongTermHistory();

	instructionsMessage();
	fillCommandsFromFile(HISTORY_TXT, short_term_history, &long_term_history);
	apartments = FillApartmentsfromBinaryFile(APARTMENT_BIN);
	char* command = _strdup(getCommand());
	while (strcmp(command, EXIT) != 0) 
	{
		printf("\n");
		addToStore(short_term_history, &long_term_history,command);
		executeCommand(command, &apartments,short_term_history, &long_term_history); 
		command = _strdup(getCommand());

	}
	addCommandsToFile(HISTORY_TXT, short_term_history, &long_term_history);
	addApartmentsToBinaryFile(apartments, APARTMENT_BIN);
	clean_AP(apartments);
	clean_LH(long_term_history);
	printf("\nGood Bye!");
	getchar();
}