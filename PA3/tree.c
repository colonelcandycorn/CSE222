#include "tree.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


/*
	Parameters: root of a tree, plate string, first name, last name
	
	This is a way to recursively add to a binary search tree. Our base case is
	when the add function is called with a NULL root. We then create a new node
	and return that new node.
	
	If it is called with a non-NULL root, we then strcmp on the plate string. If
	it is 0 then that means the plate already exists so we do nothing and return.
	If cmp is > 0 then that means the plate we want to add is less than the root
	so we call add on root->left. If cmp is < 0 then what we are adding is greater
	then root and we need to add on root->right.

	Return: Once all the recursive calls are finished, we return the root that is
	properly updated.
*/
	
Node add(Node root, char *plate, char *first, char* last) {
	
	//base case
	if (!root) {
	// initialize space for new node and it's internals
	Node toBeAdded = (Node)malloc(sizeof(struct node));
	toBeAdded->plate = (char *)malloc(sizeof(char) * (strlen(plate) + 1));
	toBeAdded->first = (char *)malloc(sizeof(char) * (strlen(first) + 1));
	toBeAdded->last = (char*)malloc(sizeof(char) * (strlen(last) + 1));
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

/*
	Parameters: root of tree, plate string, first name, last name

	recursive search function. More or less the same function as add
	without the actual adding of a node. Our base case is when root is null.
	Reaching our base case means the plate wasn't found so we just return.

	If strcmp isn't 0 we recursively call search on the appropriate side of the
	tree and continue our search. If we do find the node we are looking for
	we strcpy first and last from root into the parameter first and last.

	Return: 1 if successful and 0 if not found
*/

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
/* 
	This is obviously the most complicated function of the project.
	I decided to create utility functions to make the code a little
	less complicated. The freeNode function has the added benefit of
	also being useful in the treeFree function.

	Parameters: root of tree and a plate string

	Our base case is when delete is called with a null root. We simply
	return root or NULL in that case.

	Else we do a strcmp. If we find the node we are tyring to delete,
	we call our helper function to find the inorder predecessor. The
	helper function is called with root, and it takes care of editing
	the tree. But our delete function does the actual 'deleting'.
	
	If we are less than or greater than the node we are looking for we
	set root->left or root->right equal to the result of the recursive
	call of delete.

	Return: return the root or the newly edited root
*/
Node delete(Node root, char *plate) {
	if (!root) return root;

	int cmp = strcmp(root->plate, plate);
	if (!cmp) {
		Node temp = inorderPredecessor(root);
		freeNode(root);
		return temp;
		
	} else if (cmp > 0) {
		root->left = delete(root->left, plate);
	} else {
		root->right = delete(root->right, plate);
	}
	
	return root;
}


/*
	Simple utility delete that takes a node as a parameter.
	It then frees all the allocated memory inside the node
	before freeing the node itself
*/
void freeNode(Node deleteNode) {
	free(deleteNode->plate);
	free(deleteNode->first);
	free(deleteNode->last);
	free(deleteNode);
} 

/*
	Parameter: node of tree we are finding the predecessor for

	Our easiest case we finding the inorder predecessor is when there
	is no left part of tree. In that case, we simply return the right
	the right branch.

	We then create two pointers: a previous node pointer and a current
	node pointer. We need the previous because once we find the predecessor
	we need to adjust its and its parents relations.

	The next case we need to handle is when there is a left branch, but that left
	branch has no right node. In that case we simply make the new root node the left
	branch. That new root needs to be made to have the original roots right branch
	as it's right branch.

	Last, we just go to the left once and then all the way to the right and use that
	node as the new root. If it had any children on left side, we make sure that prev
	pointer is updated to point to it's left children.

	Return: we either return the right of the root or the new updated left side of root
	or we find a predecessor left once and all the way to the right and return that.

*/

Node inorderPredecessor(Node root) {
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
/*
	These are our three print functions which are all relatively self explanatory.

	Parameters: a tree we'd like to print out

	Base case in all three is if the root is NULL.

	LNR is inorder printing. We recursively call the function on the left, print
	the current node, and then recursively call on right. This will print out are
	items in ascending order.

	NLR is preorder printing. We print first this time, then recursively call on the
	left then right.

	LRN is postorder printing. We recursively call on the left then right and then
	print.

	Return: we return void in all instances

*/
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


////////////////////////////////////////////////////////////////////

/*
	Our treeFree function is almost the exact same as our postorder printing
	function.

	Parameters: a tree we'd like to completely remove.

	Our base case is if the root is NULL. We recursively call the function on the
	left and then the right. We then free the current Node. Post order made the most
	sense to me because we needed to use root to call it's left and right child, and if
	we had deleted it first that wouldn't work. 

	Return: void
*/
void treeFree(Node root) {
	if (!root) return;
	
	treeFree(root->left);
	treeFree(root->right);
	freeNode(root);
}


/*
	Parameter: a tree we want the height of

	There are two ways to write out the height: either the root counts as 1 or it
	counts as 0. I went with the way where the root is height 0 because that is the
	way we discussed it in class, but I believe it's relatively arbitrary. For this
	function, I have two base cases. Either the root itself are NULL or both it's
	children are NULL. If the root is null we set the return to be -1. We are adding
	one on the return call so this will make sure that it returns 0. The other base
	case returns 0 so it'll become one when recusrively called.

	If we pass the base cases, that means that root has at least one child, which
	means our height is more than 0. So we create two variables to store the height
	of the left side and the right side. We then set those variables to 1 + the value
	returned by the recursive call on their respective side. 

	After we obtain a left and right value we return the max of the two values.

	Return: either -1, 0 or the max of the left and right sides
*/
int height(Node root) {
	int left, right;

	if (!root) return -1;
	if (!root->left && !root->right) return 0;

	left = 1 + height(root->left);
	right = 1 + height(root->right);

	return  left > right ? left : right;
}

/*
	This function is a little more confusing than the height function, but
	it also relies on calling the height function.

	Parameter: a tree we want to see if it's balanced.

	Our base is if the function is called with a NULL root. If that is the
	case, then we return 1 because of course NULL is balanced. Else, we
	create two variables to store the results of the left and right recursive
	calls of balance. If either left or right are equal to zero then that means
	that the result of one of the recursive calls reported an imbalance so we
	immediately return 0. Else we have to check the absolute value of the
	height on the left side minus the height on the right side to see if it is
	less than or equal to zero. If it is, that means the tree is balanced and we
	return 1. Otherwise, we return 0.

	Return: 1 for balanced and 0 for unbalanced
*/

int balanced(Node root) {
	if (!root) return 1;

	int left, right;
	left = balanced(root->left);
	right = balanced(root->right);

	if (!left || !right) return 0;

	return abs(height(root->left) - height(root->right)) <= 1;
}	
