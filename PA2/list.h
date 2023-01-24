// linked list Sarah Dylan 1/23/23

#ifndef PA2_LIST_H
#define PA2_LIST_H

struct node {
	char *plate;
	char *first;
	char *last;
	struct node *next;
};

struct node *listInit();
void listAdd(struct node *sent,
			 char *plate,
			 char *firstname,
			 char *lastname);
void listFind(struct node *sent,
			  char *plate,
			  char *firstname,
			  char *lastname);
int listLen(struct node *sent);
void listPrint(struct node *sent);
void listFree(struct node *sent);
#endif // PA2_LIST_H
