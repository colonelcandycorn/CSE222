#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* 
	DataNode Constructor Function: this initializes the linklist with a sentinel node.
	The sentinel node acts as an invariant that always indicates the position before
	the start of the list. This helps with edgecases like when adding to an empty list
	or deleting a list of length 1.

	Return Value: returns a pointer to dynamically allocated struct DataNode
*/

struct DataNode *init() {
	// allocate mem
    struct DataNode *ret = (struct DataNode*) malloc(sizeof(struct DataNode));

	// initializing a c-style string and then strcopying that into data is the easiest way
	// for me to get the first node to say SENTINEL
    char sent[16] = "SENTINEL";
    strcpy(ret->data, sent);

	//initialize new nodes next value to NULL
    ret->next = NULL;

    return ret;
}

/*
	Parameters: a linked list and the data we want to add

	The add function adds a new node to the list in order according to the strcmp
	function in string.h. Requires two nodes, because we are traveling until we get
	to a node that is bigger than what we want. Once we find that, prev needs to point
	to new node and new node needs to point to current.

	Return value: returns 1 if added 0 if for some reason the heap is full.

	*Time Complexity*
	The search begins at the start of the list and worst case scenario will go until
	it has traversed the length of list. O(n)

*/
int add(struct DataNode *list, char *data) {
	// initalize new node
	struct DataNode *newNode = (struct DataNode *) malloc(sizeof(struct DataNode));
	
	//check for memory failure
	if (!newNode) return 0;
	
	//initialize DataNode data
	strcpy(newNode->data, data);
	newNode->next = NULL;

	//variable to store result of strcmp
	int cmp;
	//prev needs to start at sentinel so we can add to list with only the sentinel
	struct DataNode *prev = list;
	// need to start at second node because of sentinel
	struct DataNode *cur = list->next;

	while (cur) {
		cmp = strcmp(data, cur->data);

		//strcmp returns greater than 0 if the data we are adding should be placed after the current node
		// strcmp returns 0 if equal. In that case, it doesn't matter where  we would insert the word.
		//strcmp < 0 means we should insert now
		if (cmp > 0) {
			prev = cur;
			cur = cur->next;
		} else {
			prev->next = newNode;
			newNode->next = cur;
			return 1;
		}
	}

	//we are at end of list and still haven't added
	prev->next = newNode;
	return 1;
}

/*
	Parameters: a linked list

	For the print function we start at the second node because we know the first
	node is the 'sentinel' node. Make the loop go until it hits the last valid node.
	While loop is running, print the current nodes data followed by a space. When it
	exits the loop, it prints the last node's data followed by a newline.

	*Time Complexity*
	we are printing everything once so O(n)
*/
void print(struct  DataNode *list) {
	struct DataNode *cur = list->next;
	if(!cur) {
		puts("");
		return;
	}

	while (cur->next) {
		printf("%s ", cur->data);
		cur = cur->next;
	}
	
	printf("%s\n", cur->data);
}

/*
	Parameters: linked list and data we are deleting

	Delete requires two nodes like the add function. Because when we find the node, we will
	need to update the prev node to point to current's next pointer. After we update the pointers,
	there are no references to current in the list so we are safe to free that pointer. We use strcmp
	to find the data 

	Return value: returns 1 if delete was performed, 0 otherwise

	*Time Complexity*
	Worst case we search the list and don't find the data we want to delete so O(n)
*/

int myDelete(struct DataNode *list, char *data) {
	struct DataNode *prev = list;
	struct DataNode *cur = list->next; 
	while (cur) {
		if (!strcmp(data, cur->data)) {
			prev->next = cur->next;
			free(cur);
			return 1;
		}
		prev = cur;
		cur = cur->next;
	}
	return 0;
}
		
/*
	Parameters: linked list and data we are searching fo

	The search function is almost exactly the same as the delete function. We, however, only need
	one pointer this time since we won't be changing the list in anyway. We also don't need free.
	We simply start at the first node (node after sentinel) then traverse the list, printing the
	nodes.

	Return Value: returns 1 if found 0 otherwise.

	*Time Complexity*
	Worst case the data isn't found so O(n) 
*/
int search(struct DataNode *list, char *data) {
	struct DataNode *cur = list->next; 
	while (cur) {
		if (!strcmp(data, cur->data)) {
			return 1;
		}
		cur = cur->next;
	}
	return 0;
}

/*
	Parameters: linked list

	The cleanup function requires two pointers because we will remove the prev pointer and the advance the current and prev
	pointers. This process continues as long as cur is not NULL. Once we reach the end of the list cur is NULL but prev
	still has a pointer so we need to be sure to do one last free before returning.

	*Time Complexity*
	O(n)
*/

void cleanup(struct DataNode *list) {
	struct DataNode *prev = list;
	struct DataNode *cur = list->next;
	while (cur) {
		free(prev);
		prev = cur;
		cur = cur->next;
	}
	free(prev);
	return;
}
