#include"Apartments.h"

typedef unsigned short int TWOBYTE;
typedef unsigned char BYTE;

int isEmptyList(Apartment_List*list);
Apartment_List createApartmentsList();
void fillDataFromAptToNode(Apartment newApartment, Apartment_ListNode* newNode);
Apartment_ListNode* crateNode(Apartment newApartment);
void append_AP(Apartment_List* list, Apartment newApartment);
void deleteFromFrist(Apartment_List* list, Apartment_ListNode* delNode);
void deleteFromEnd(Apartment_List* list, Apartment_ListNode* delNode);
void deleteFromMiddle(Apartment_List* list, Apartment_ListNode* delNode);
void omit_AP(Apartment_List* list, Apartment_ListNode* delNode);
void freeNode(Apartment_ListNode* node);
void clean_AP(Apartment_List list);
void checkMemoryAllocation(void* ptr);

Apartment_List FillApartmentsfromBinaryFile(char *filename);
void addApartmentsToBinaryFile(Apartment_List aptlst, char* filename);

void entryDate(Date* entry_date);
int daysOfOneDate(Date one_date);
int differenceOfDays(Date date_of_day, Date apartment_entry_date);
void sortApartments(Apartment_List* apartments);
Apartment getMinApartmentPrice(Apartment_List* apartments,Apartment_ListNode** save_apartment,Apartment_ListNode* limit);
void getMaximumPrice(Apartment_List* apartments, int max_price);
void getMaximumRooms(Apartment_List* apartments, int max_rooms);
void getMinimumRooms(Apartment_List* apartments, int min_rooms);
void copyApartments(Apartment_List* src, Apartment_List* des);



/*makes an empty list ( head+tail to NULL )  */
int isEmptyList(Apartment_List*list) {
	return list->head == NULL;
}

/* creates an apartment and points the head and tail to NULL */
Apartment_List createApartmentsList() {

	Apartment_List newList;
	newList.head = newList.tail = NULL;
	return newList;
}


/*  fills the input to a node   */
void fillDataFromAptToNode(Apartment newApartment, Apartment_ListNode* newNode) {

	newNode->data.code = newApartment.code;
	newNode->data.address = _strdup(newApartment.address);
	checkMemoryAllocation(newNode->data.address);
	newNode->data.price = newApartment.price;
	newNode->data.rooms = newApartment.rooms;
	newNode->data.date_of_hire.day = newApartment.date_of_hire.day;
	newNode->data.date_of_hire.month = newApartment.date_of_hire.month;
	newNode->data.date_of_hire.year = newApartment.date_of_hire.year;
	newNode->data.date_of_add.day = newApartment.date_of_add.day;
	newNode->data.date_of_add.month = newApartment.date_of_add.month;
	newNode->data.date_of_add.year = newApartment.date_of_add.year;
}


/* Creates a list node, and fill it with data  */
Apartment_ListNode* crateNode(Apartment newApartment) {

	Apartment_ListNode* newNode;
	newNode = (Apartment_ListNode*)malloc(sizeof(Apartment_ListNode));
	checkMemoryAllocation(newNode);
	newNode->previous = NULL;
	newNode->next = NULL;
	fillDataFromAptToNode(newApartment, newNode);
	return newNode;
}


/* Inserts a list node the the end of list */
void append_AP(Apartment_List* list, Apartment newApartment) {

	Apartment_ListNode* newNode = crateNode(newApartment);
	if (isEmptyList(list))
		list->head = list->tail = newNode;
	else 
	{
		newNode->previous = list->tail;
		list->tail->next = newNode;
		list->tail = newNode;
	}
}


/* deletes a node from first of list*/
void deleteFromFrist(Apartment_List* list, Apartment_ListNode* delNode) {

	Apartment_ListNode* seconde_node = list->head->next;
	list->head->next->previous = NULL;
	list->head = seconde_node;
}

/* deletes a node from the end of list */
void deleteFromEnd(Apartment_List* list, Apartment_ListNode* delNode) {

	Apartment_ListNode* befor_last_node = list->tail->previous;
	list->tail->previous->next = NULL;
	list->tail = befor_last_node;
}


/* deletes from the middle of list */
void deleteFromMiddle(Apartment_List* list, Apartment_ListNode* delNode) {

	Apartment_ListNode* befor_node = delNode->previous;
	Apartment_ListNode* next_node = delNode->next;
	befor_node->next = next_node;
	next_node->previous = befor_node;
}

/* deletes a node, checks where the node is and calls to the appropriate function to delete the node */
void omit_AP(Apartment_List* list, Apartment_ListNode* delNode) {

	if (!isEmptyList(list))
	{
		if (list->head == list->tail)
			list->head = list->tail = NULL;
		else if (list->head == delNode)
			deleteFromFrist(list, delNode);
		else if (list->tail == delNode)
			deleteFromEnd(list, delNode);
		else
			deleteFromMiddle(list, delNode);
		freeNode(delNode);
	}
}

/* frees a node */
void freeNode(Apartment_ListNode* node) {
	free(node->data.address);
	free(node);
}

/* cleans the apartment list (frees all the memory) */
void clean_AP(Apartment_List list) {

	Apartment_ListNode* current_node = list.head;
	Apartment_ListNode* next_node;
	while (current_node) 
	{
		next_node = current_node->next;
		freeNode(current_node);
		current_node = next_node;
	}
}

/* Checks if allocation succedded*/
void checkMemoryAllocation(void* ptr) {
	if (ptr == NULL)
	{
		puts("Memory allocaton Faild\n");
		exit(1);
	}
}

/* Prints a list full of apartments */
void printList_AP(Apartment_List list) {
	Apartment_ListNode* currentNode = list.head;
	if (currentNode == NULL)
		printf("Empty Storage\n\n");
	while (currentNode != NULL)
	{
		printf("Apt details:\n\n");
		printf("Code: %d\n\nAddress: %s\n\nNumber of rooms: %d\n\nPrice: %d\n\nEntry date: %d.%d.%d\n\n"
			"Database entry date: %d.%d.%d\n\n",
			currentNode->data.code,currentNode->data.address,currentNode->data.rooms,
			currentNode->data.price,currentNode->data.date_of_hire.day,
			currentNode->data.date_of_hire.month,currentNode->data.date_of_hire.year,
			currentNode->data.date_of_add.day,currentNode->data.date_of_add.month,
			currentNode->data.date_of_add.year);
		currentNode = currentNode->next;
	}
}

/* prints the list reversed (from end to start) */
void printListOp_AP(Apartment_List list) {
	Apartment_ListNode* currentNode = list.tail;
	while (currentNode != NULL)
	{
		printf("Apt details:\n\n");
		printf("Code: %d\n\nAddress: %s\n\nNumber of rooms: %d\n\nPrice: %d\n\nEntry date: %d.%d.%d\n\n"
			"Database entry date: %d.%d.%d\n\n",
			currentNode->data.code,currentNode->data.address,currentNode->data.rooms,
			currentNode->data.price,currentNode->data.date_of_hire.day,
			currentNode->data.date_of_hire.month,currentNode->data.date_of_hire.year,
			currentNode->data.date_of_add.day,currentNode->data.date_of_add.month,
			currentNode->data.date_of_add.year);
		currentNode = currentNode->previous;
	}
}

/* Gets the date of the current day we are in */
void entryDate(Date* entry_date) {

	time_t current_date;
	time(&current_date);
	struct tm *MyDate = localtime(&current_date);
	entry_date->day = MyDate->tm_mday;
	entry_date->month = MyDate->tm_mon + 1;
	entry_date->year = MyDate->tm_year + 1900;
}

/* returns how many days passed from the date */
int daysOfOneDate(Date one_date) {
	int sum_of_days = 0;
	sum_of_days += one_date.day;
	for (short current_month = 1; current_month <one_date.month; current_month++) 
	{
		if (current_month == 2)
			sum_of_days += 28;
		else if (current_month == 4 || current_month == 6 ||
			current_month == 9 || current_month == 11)
			sum_of_days += 30;
		else
			sum_of_days += 31;
	}
	sum_of_days += one_date.year * 365;
	return sum_of_days;
}

/* check the differnce between two different days */
int differenceOfDays(Date date_of_day, Date apartment_entry_date) {

	return(daysOfOneDate(date_of_day) - daysOfOneDate(apartment_entry_date));
}


/* gets the minimum apartment price */
Apartment getMinApartmentPrice(Apartment_List* apartments, Apartment_ListNode** save_apartment,
	Apartment_ListNode* limit) {
	
	int min_price = apartments->head->data.price;
	Apartment_ListNode* min_apartment = apartments->head;
	Apartment_ListNode* current_apartment = apartments->head;
	while (current_apartment!=limit) 
	{
		if (current_apartment->data.price <= min_price)
		{
			min_price = current_apartment->data.price;
			min_apartment = current_apartment;
		}
		current_apartment = current_apartment->next;
	}
	if (current_apartment->data.price < min_price) 
	{
		min_price = current_apartment->data.price;
		min_apartment = current_apartment;
	}
	*save_apartment = min_apartment;
	return min_apartment->data;
}

/* sorting a list of apartments  */
void sortApartments(Apartment_List* apartments) {

	Apartment_ListNode* current_apartment = apartments->head;
	Apartment_ListNode* old_tail = apartments->tail;
	Apartment_ListNode* save_apartment = NULL;
	while (old_tail) 
	{
		append_AP(apartments, getMinApartmentPrice(apartments,&save_apartment,old_tail));
		if (save_apartment == old_tail)
			old_tail = old_tail->previous;
		omit_AP(apartments, save_apartment);
	}
}

/* copy apartment list to a new list, so when I can change in it and do not change the origin apartment list */
void copyApartments(Apartment_List* src, Apartment_List* des) {

	Apartment_ListNode* current_apartment = src->head;
	while (current_apartment) 
	{
		append_AP(des, current_apartment->data);
		current_apartment = current_apartment->next;
	}
}

/* gets the apartments that has been added from a certain date */
void getEnterSince(Apartment_List* apartments, int last_days) {

	Apartment_ListNode* current_apartment = apartments->head;
	Apartment_ListNode* save_location = apartments->head;
	Date current_date;
	entryDate(&current_date);
	while (current_apartment)
	{
		if (differenceOfDays(current_date, current_apartment->data.date_of_add) > last_days) 
		{
			save_location = current_apartment->next;
			omit_AP(apartments, current_apartment);
			current_apartment = save_location;
		}
		else
			current_apartment = current_apartment->next;
	}
}

/* deletes all the apartments that are higher than the price that in the input, deletes the apartments from the copied apartment list */
void getMaximumPrice(Apartment_List* apartments, int max_price) {

	Apartment_ListNode* current_apartment = apartments->head;
	Apartment_ListNode* save_location = apartments->head;
	while (current_apartment) 
	{
		if (current_apartment->data.price > max_price) 
		{
			save_location = current_apartment->next;
			omit_AP(apartments, current_apartment);
			current_apartment = save_location;
		}
		else
			current_apartment = current_apartment->next;
	}
}

/* deletes the apartments that are higher than the max rooms from the input. (deletes the apartments from the copied apartment list) */
void getMaximumRooms(Apartment_List* apartments, int max_rooms) {

	Apartment_ListNode* current_apartment = apartments->head;
	Apartment_ListNode* save_location = apartments->head;
	while (current_apartment) 
	{
		if (current_apartment->data.rooms > max_rooms)
		{
			save_location = current_apartment->next;
			omit_AP(apartments, current_apartment);
			current_apartment = save_location;
		}
		else
			current_apartment = current_apartment->next;
	}
}

/* deletes all the apartments that the number of rooms in it lower than the number of rooms input. (deletes from the copied apartment list) */
void getMinimumRooms(Apartment_List* apartments, int min_rooms) {

	Apartment_ListNode* current_apartment = apartments->head;
	Apartment_ListNode* save_location = apartments->head;
	while (current_apartment) 
	{
		if (current_apartment->data.rooms < min_rooms)
		{
			save_location = current_apartment->next;
			omit_AP(apartments, current_apartment);
			current_apartment = save_location;
		}
		else
			current_apartment = current_apartment->next;
	}
}

/* deletes the apartments that their date are higher than the date in the input. (deletes from the copied apartment list) */
void getFreeDate(Apartment_List* apartments, Date free_date) {

	Apartment_ListNode* current_apartment = apartments->head;
	Apartment_ListNode* save_location = apartments->head;
	Date current_date;
	entryDate(&current_date);
	while (current_apartment) 
	{
		if (differenceOfDays(current_apartment->data.date_of_hire,free_date) > 0) 
		{
			save_location = current_apartment->next;
			omit_AP(apartments, current_apartment);
			current_apartment = save_location;
		}
		else
			current_apartment = current_apartment->next;
	}
}

/* fills the apartment list from the binary file, if the file doesn't exist (first input) it returns an empty list. */
Apartment_List FillApartmentsfromBinaryFile(char *filename)
{
	Apartment_List aptlst;
	aptlst = createApartmentsList();
	if (_access(filename, 0) == 0)// _access(filename,0), checks if a file is exists in my program file, if it exist the function returns 0. 
	{
		TWOBYTE code, len;
		BYTE c, mask;
		FILE *f = fopen(filename, "rb");
		int size;
		fread(&size, sizeof(int), 1, f);
		for (int i = 0;i < size;i++)
		{
			Apartment_ListNode *p = (Apartment_ListNode*)malloc(sizeof(Apartment_ListNode));
			fread(&code, sizeof(TWOBYTE), 1, f);
			fread(&len, sizeof(TWOBYTE), 1, f);
			p->data.code = code;
			p->data.address = (char*)malloc(len * sizeof(char));
			fread(p->data.address, sizeof(char), len, f);
			p->data.address[len] = '\0';
			fread(&p->data.price, sizeof(int), 1, f);
			fread(&c, sizeof(BYTE), 1, f);
			p->data.rooms=c >> 4 ;
			mask = 0x0F;
			mask = mask & c;
			mask = mask << 1;
			fread(&c, sizeof(BYTE), 1, f);
			BYTE mask2 = 0x80;
			mask2 = mask2 & c;
			mask2 = mask2 >> 7;
			mask = mask | mask2;
			p->data.date_of_hire.day = mask;
			mask = 0x78;
			mask = mask & c;
			mask = mask >> 3;
			p->data.date_of_hire.month = mask;
			mask = 0x07;
			mask = mask & c;
			mask = mask << 4;
			fread(&c, sizeof(BYTE), 1, f);
			mask = mask | (c >> 4);
			p->data.date_of_hire.year = mask + 2000; // so it's 2000's for the output print.
			fread(&p->data.date_of_add, sizeof(Date), 1, f);
			append_AP(&aptlst, p->data);
		}
	}
	return aptlst;
}

/* adds the apartment list to a binary file, compress the code of apartment and the date of hire to a smaller chars array */
void addApartmentsToBinaryFile(Apartment_List aptlst, char* filename)
{
	FILE *f = fopen(filename, "wb");
	checkMemoryAllocation(f);
	int len; int size = CountApts(aptlst.head);
	Apartment_ListNode *p = aptlst.head;
	fwrite(&size, sizeof(int), 1, f);
	while (p != NULL)
	{
		BYTE year;
		BYTE c[3];
		c[0] = (BYTE)p->data.rooms;
		c[0] = c[0] << 4;
		c[1] = (BYTE)p->data.date_of_hire.day;
		BYTE mask = 0x1E;
		mask = c[1] & mask;
		mask = mask >> 1;
		c[0] = mask | c[0];
		c[1] = c[1] << 7;
		mask = c[1];
		c[1] = (BYTE)p->data.date_of_hire.month;
		c[1] = c[1] << 3;
		c[1] = c[1] | mask;
		year = (BYTE)p->data.date_of_hire.year % 2000;
		c[2] = year;
		c[1] = c[1] | (c[2] >> 4);
		c[2] = c[2] << 4;
		TWOBYTE code;
		code = (TWOBYTE)p->data.code;
		fwrite(&code, sizeof(TWOBYTE), 1, f);
		len = strlen(p->data.address);
		fwrite(&len, sizeof(TWOBYTE), 1, f);
		fwrite(p->data.address, sizeof(char), len, f);
		fwrite(&p->data.price, sizeof(int), 1, f);
		fwrite(&c[0], sizeof(BYTE), 1, f);
		fwrite(&c[1], sizeof(BYTE), 1, f);
		fwrite(&c[2], sizeof(BYTE), 1, f);
		fwrite(&p->data.date_of_add, sizeof(Date), 1, f);
		p = p->next;
	}
	fclose(f);
}

/* returns how many apartments exist in the list */
int CountApts(Apartment_ListNode *apt)
{
	int c = 0;
	while (apt != NULL)
	{
		c++;
		apt = apt->next;
	}
	return c;
}




