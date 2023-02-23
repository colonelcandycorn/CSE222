#include "tree.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
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
		if (cmp < 0) curNode = curNode->left;
		if (cmp > 0) curNode = curNode->right;
	}

	cmp < 0 ? (prev->left = toBeAdded) :( prev->right = toBeAdded);

	return root;
}
*/
	
Node add(Node root, char *plate, char *first, char* last) {
	
	//base case
	if (!root) {
	// initialize space for new node and it's internals
	Node toBeAdded = (Node)malloc(sizeof(struct node));
	toBeAdded->plate = (char *)malloc(sizeof(plate));
	toBeAdded->first = (char *)malloc(sizeof(first));
	toBeAdded->last = (char*)malloc(sizeof(last));
	toBeAdded->left =  NULL;
	toBeAdded->right = NULL;

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
	Node temp;
	if (cmp > 0) {
		temp = add(root->left, plate, first, last);
		root->left = temp;
	} else if (cmp < 0) {
		temp =  add(root->right, plate, first, last);
		root->right = temp;
	}

	return root;
}

int search(Node root, char *plate, char *first, char *last) {
	if (!root) return 0;

	int cmp = strcmp(root->plate, plate);
	if (!cmp) {
		strcpy(first, root->first);
		strcpy(last, root->last);
		return 1;
	} else if (cmp > 0) {
		return search(root->left, plate, first, last);
	} else {
		return search(root->right, plate, first, last);
	}
}

// DELETE AND UTILITY
Node delete(Node root, char *plate) {
	if (!root) return root;

	int cmp = strcmp(root->plate, plate);
	if (!cmp) {
		// do delete stuff call inorder successor
		Node temp = inorderSuccessor(root);
		//if (!temp) temp = root->left;
		freeNode(root);
		return temp;
		
	} else if (cmp > 0) {
		root->left = delete(root->left, plate);
	} else {
		root->right = delete(root->right, plate);
	}
	
	return root;
}

void freeNode(Node deleteNode) {
	free(deleteNode->plate);
	free(deleteNode->first);
	free(deleteNode->last);
	free(deleteNode);
} 

Node inorderSuccessor(Node root) {
	if (!root->left) return root->right;
	Node prev = root->left;
	Node cur = prev->right;
	if (!cur) {
		prev->right = root->right;
		return prev;
	}
	while (cur->right) {
		prev = cur;
		cur = cur->right;
	}
	prev->right = cur->left;
	cur->left = root->left;
	cur->right = root->right;

	return cur;
}
//////////////////////////////////////
//PRINT
void LNR(Node root) {
	if (!root) return;

	LNR(root->left);
	printf("Plate: <%s>  Name: %s, %s\n", root->plate, root->last, root->first);
	LNR(root->right);
}

void NLR(Node root) {
	if (!root) return;
	
	printf("Plate: <%s>  Name: %s, %s\n", root->plate, root->last, root->first);	
	NLR(root->left);
	NLR(root->right);
}

void LRN(Node root) {
	if (!root) return;
	
	LRN(root->left);
	LRN(root->right);
	printf("Plate: <%s>  Name: %s, %s\n", root->plate, root->last, root->first);
}


void treeFree(Node root) {
	if (!root) return;
	
	treeFree(root->left);
	treeFree(root->right);
	freeNode(root);
}

int height(Node root) {
	int left, right;

	if (!root) return -1;
	if (!root->left && !root->right) return 0;

	left = 1 + height(root->left);
	right = 1 + height(root->right);

	return  left > right ? left : right;
}

int balanced(Node root) {
	if (!root) return 1;

	int left, right;
	left = balanced(root->left);
	right = balanced(root->right);

	if (!left || !right) return 0;

	return abs(height(root->left) - height(root->right)) <= 1;
}	
