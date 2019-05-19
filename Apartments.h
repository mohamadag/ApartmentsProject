#ifndef __APARTMENTS_H
#define __APARTMENTS_H
#define _CRT_SECURE_NO_WARNINGS

#include<stdlib.h>
#include<stdio.h>
#include <time.h>
#include <io.h>
#include<string.h>

typedef struct date {
	short int day;
	short int month;
	short int year;
}Date;

typedef struct apartment {
	unsigned int code;
	char *address;
	int price;
	short int rooms;
	Date date_of_hire;
	Date date_of_add;
}Apartment;

typedef struct listNode {
	Apartment data;
	struct listNode* previous;
	struct listNode* next;
}Apartment_ListNode;

typedef struct list {
	Apartment_ListNode* head;
	Apartment_ListNode* tail;
}Apartment_List;

Apartment_List createApartmentsList();
void append_AP(Apartment_List* list, Apartment newApartment);
void omit_AP(Apartment_List* list, Apartment_ListNode* delNode);       
void clean_AP(Apartment_List list);
void printList_AP(Apartment_List list);
void printListOp_AP(Apartment_List list);

void getMaximumPrice(Apartment_List* apartments, int max_price);
void getMaximumRooms(Apartment_List* apartments, int max_rooms);
void getMinimumRooms(Apartment_List* apartments, int min_rooms);
void getFreeDate(Apartment_List* apartments, Date free_date);
void getEnterSince(Apartment_List* apartments, int last_days);

void entryDate(Date* entry_date);
int differenceOfDays(Date date_of_day, Date apartment_entry_date);
void copyApartments(Apartment_List* src, Apartment_List* des);
void sortApartments(Apartment_List* apartments);

Apartment_List FillApartmentsfromBinaryFile(char *filename);
void addApartmentsToBinaryFile(Apartment_List aptlst, char* filename);
int CountApts(Apartment_ListNode *apt);
void getFilter(char *command, Apartment_List *apartments);

#endif 
