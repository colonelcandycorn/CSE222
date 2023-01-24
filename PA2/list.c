#include "list.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
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


int listFind(struct node *sent, char *plate, char *firstname, char *lastname) {
	int temp =0;
	struct node *cur = sent->next;
	while (cur) {
		++temp;
		if (!strcmp(cur->plate, plate)) {
			firstname = cur->first;
			lastname = cur->last;
			return 1;
		}
		cur = cur->next;
	}
	return 0;
}

int listLen(struct node *sent) {
	int temp = 0;
	struct node *cur = sent->next;
	while (cur) {
	++temp;
	cur = cur->next;
	}
	return temp;
}

void listPrint(struct node *sent) {
	struct node *cur = sent->next;
	while (cur) {
	printf("Plate: <%s>  Name: %s, %s\n", cur->plate, cur->last, cur->first);
	cur = cur->next;
	}
}

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
