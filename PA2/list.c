/*
	Sarah Dylan CSE 215 PA2 01/30/2023

	This is the implementation of a linked list. The implementation
	is almost exactly the same as PA1 outside of the fact taht we our
	nodes are also storing a first and last name. An another  difference
	is we do not care the order in which the values are stored so we always
	insert at the front of thelist. Because we don't know the size of the 
	strings that will be needed to store the names and plate number, we will
	have to dynamically allocate them. 

*/

#include "list.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


/* 
	Parameters: none

	initialize a list with a sentinel node. We store the string SENTINEL
	in the plate field of the node and set the rest of the node. This would
	be useful if needed to check if we were at sentinel, but for this particular
	project it just matters that a node exists so we don't segfault with an empty
	list.

	Return: returns a pointer to the newly initialized sentinel node

*/


struct node *listInit() {
	struct node *sent = (struct node *)malloc(sizeof(struct node));
	char temp[] = "SENTINEL";
	char *sentStr = (char *)malloc(sizeof(char) * (strlen(temp) + 1));
	strcpy(sentStr, temp);
	sent->plate = sentStr;
	sent->first = NULL;
	sent->last = NULL;
	sent->next = NULL;
	return sent;
}

/*
	Parameters: a sentinel node, a string for plate number, a string for the first name
	and a string for the last name.

	We then malloc memory for the node, then for each string based on the strlen + 1
	because of the null value at the end of strings. We place this new node at the
	front of the list so the time complexity is O(1).

	Return: void

*/

void listAdd(struct node*sent, char *plate, char *firstname, char *lastname) {
	struct node *temp = (struct node *)malloc(sizeof(struct node));
	temp->plate = (char *)malloc(sizeof(char) * (strlen(plate) + 1));
	strcpy(temp->plate, plate);
	temp->first = (char *)malloc(sizeof(char) * (strlen(firstname) + 1));
	strcpy(temp->first, firstname);
	temp->last = (char *)malloc(sizeof(char) * (strlen(lastname) + 1));
	strcpy(temp->last, lastname);
	temp->next = sent->next;
	sent->next = temp;
}

/*
	Parameters: sentinel node, plate string, firstname, last name

	The big difference here between add is we are using the first name and last name
	parameters to store the found name so that value can be printed out later. We perform
	our search starting at the sentinel and go until the end is reached so time complexity is
	O(n)

	Return: returns a 1 for success 0 for failure
*/


int listFind(struct node *sent, char *plate, char *firstname, char *lastname) {
	int temp =0;
	struct node *cur = sent->next;
	while (cur) {
		++temp;
		if (!strcmp(cur->plate, plate)) {
			strcpy(firstname, cur->first);
			strcpy(lastname, cur->last);
			return 1;
		}
		cur = cur->next;
	}
	return 0;
}

/*
	Parameter: sentinel node

	We start at the sentinel node and keep moving until we reach null. Each
	time we move we increment the counter.

	Return: return the value of our counter as it represents the length of the linked list
*/

int listLen(struct node *sent) {
	int temp = 0;
	struct node *cur = sent->next;
	while (cur) {
	++temp;
	cur = cur->next;
	}
	return temp;
}

/*
	Parameter: sentinel node
	
	Our PA2 project specifies that a format to print the value of the node. So we do the 
	same as len but each node we visit we print the value. 

	Return: void
*/

void listPrint(struct node *sent) {
	struct node *cur = sent->next;
	while (cur) {
	printf("Plate: <%s>  Name: %s, %s\n", cur->plate, cur->last, cur->first);
	cur = cur->next;
	}
}

/*
	Parameter: sentinel

	Similar to PA1 but different because we not only have to free the pointer to the structure
	but the pointers for each string inside of the structure. So each node this time will free
	4 times. 

	Return: void
*/

void listFree(struct node *sent) {
	struct node *cur = sent->next;
	struct node *prev = sent;
	while (cur) {
		free(prev->plate);
		free(prev->first);
		free(prev->last);
		free(prev);
		prev = cur;
		cur = cur->next;
	}
	free(prev->plate);
	free(prev->first);
	free(prev->last);
	free(prev);
}
