#ifndef __HISTORY_H
#define  __HISTORY_H
#include"Apartments.h"

typedef struct history_listNode {
	short index;
	char* data;
	struct history_listNode* next;
	struct history_listNode* previous;
}History_ListNode;


typedef struct history_list {
	History_ListNode* head;
	History_ListNode* tail;
}History_List;

History_List createLongTermHistory();
void append_LH(History_List* list, char* command);
void append_LH_Head(History_List* list, char* command,int index);

void clean_LH(History_List list);
void print_LH(History_List list);
void print_SH(char*short_term_history[7], int long_history_number);
void printHistory(History_List list, char*short_term_history[7]);
void addToStore(char*short_term_history[7], History_List* long_term_history, char* command);
int getLongHistoryNumber(History_List list);
short int getShortHistoryNumber(char*short_term_history[7]);
void executeHistoryCommand(char* command, Apartment_List* apartments,
	char*short_term_history[7], History_List* long_term_history);

#endif