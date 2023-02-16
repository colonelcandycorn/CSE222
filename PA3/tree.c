#include "tree.h"
#include <string.h>
/*
Node add(Node root, char *plate, char *first, char* last) {
	// initialize space for new node and it's internals
	Node toBeAdded = (Node)malloc(sizeof(Node));
	toBeAdded->plate = (char *)malloc(sizeof(plate));
	toBeAdded->first = (char *)malloc(sizeof(first));
	toBeAdded->last = (char*)malloc(sizeof(last));

	//set the newly allocated space equal to the desired values
	strcpy(toBeAdded->plate, plate);
	strcpy(toBeAdded->first, first);
	strcpy(toBeAdded->last, last);

	//if we are given a NULL root that means new Node is the new root
	if (!root) return toBeAdded;

	// find where in the current tree new node belongs
	// utilize two pointers
	Node curNode = root;
	Node prev = root;

	//declare cmp so we can use it when we are done with the loop	
	int cmp;

	//while the current node exist go to left or right to find insert point
	while (curNode) {
		prev = curNode;
		cmp = strcmp(toBeAdded->plate, curNode->plate);
		//if 0 already in tree so do nothing
		if (cmp == 0) break;
		if (cmp < 0) {
			curNode = curNode->left;
			if (
		if (cmp > 0) curNode = curNode->right;
	}

	cmp < 0 ? prev->left = toBeAdded : prev->right = toBeAdded;

	return root;
}
*/
	
Node add(Node root, char *plate, char *first, char* last) {
	
	//base case
	if (!root) {
	// initialize space for new node and it's internals
	Node toBeAdded = (Node)malloc(sizeof(Node));
	toBeAdded->plate = (char *)malloc(sizeof(plate));
	toBeAdded->first = (char *)malloc(sizeof(first));
	toBeAdded->last = (char*)malloc(sizeof(last));

	//set the newly allocated space equal to the desired values
	strcpy(toBeAdded->plate, plate);
	strcpy(toBeAdded->first, first);
	strcpy(toBeAdded->last, last);

	//if we are given a NULL root that means new Node is the new root
	return toBeAdded;
	}

	int cmp = strcmp(root->plate, plate);
	if (!cmp) return root;
	
	//recursively call
	if (cmp < 0)
		root->left = add(root->left, plate, first, last);
	else
		root->right = add(root->right, plate, first, last);
}
	
