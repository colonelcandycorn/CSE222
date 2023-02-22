#ifndef PA3_TREE_H
#define PA3_TREE_H

struct node {
	char *plate;
	char *first;
	char *last;
	struct node *left;
	struct node *right;
};

typedef struct node *Node;

int height(Node root);
Node add(Node root,
		 char *plate,
		 char *first,
		 char *last);
int search(Node root,
		   char *plate,
		   char *first,
		   char *last);
Node delete(Node root,
		    char *plate);
void LNR(Node root);
void NLR(Node root);
void LRN(Node root);

void treeFree(Node root);
void freeNode(Node);
Node inorderSuccessor(Node);
#endif // PA3_TREE_H
