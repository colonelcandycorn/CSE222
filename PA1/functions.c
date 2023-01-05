#include "main.h"
#include <stdlib.h>
#include <string.h>


/* 
	DataNode Constructor Function: this initializes the linklist with a sentinal node.
	The sentinal node acts as an invariant that always indicates the position before
	the start of the list.
*/

struct DataNode *init() {
    struct DataNode *ret = (struct DataNode*) malloc(sizeof(struct DataNode));
//    char sent[16] = {'S', 'E', 'N', 'T', 'I', 'N', 'A', 'L', '\0'};
//    for (int i = 0; i < sizeof(sent); ++i) {
//        ret->data[i] = sent[i];
//    }

    char sent[16] = "SENTINAL";
    memcpy(ret->data, sent, sizeof(sent));

    ret->next = NULL;

    return ret;
}

/*
	The add function adds a new node to the list in order according to the strcmp
	function in string.h. 

	*Time Complexity*
	The search begins at the start of the list and worst case scenario will go until
	it has traversed the length of list. So worst case is order of n / o(n)

*/
int add(struct DataNode *list, char *data) {
	// initalize new node
	struct DataNode *newNode = (struct DataNode *) malloc(sizeof(struct DataNode));
	
	//check for memory failure
	if (!newNode) return 0;
	
	//initialize DataNode data
	memcpy(newNode->data, data, sizeof(data));
	newNode->next = NULL;

	int cmp;
	struct DataNode *prev = list;
	struct DataNode *cur = list->next;

	while (cur) {
		cmp = strcmp(data, cur->data);

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
void print(struct  DataNode *list);
//int delete(struct DataNode *list, char *data);
int search(struct DataNode *list, char *data);
void cleanup(struct DataNode *list);
