#include "list.h"
#include <stdlib.h>
#include <string.h>
struct node *listInit() {
	struct node *sent = (struct node *)malloc(sizeof(struct node));
	char temp[] = "SENTINAL";
	char *sentStr = (char *)malloc(sizeof(char) * (strlen(temp) + 1));
	strcpy(sentStr, temp);
	sent->plate = sentStr;
	sent->first = NULL;
	sent->last = NULL;
	sent->next = NULL;
	return sent;
}

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
	
