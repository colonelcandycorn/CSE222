#include <stdio.h>
#include "tree.h"
int main(void) {
	Node root = add(NULL, "poop", "first", "last");
	add(root, "2poop", "first", "last");
	add(root, "butt", "butt", "butt");
	add(root, "cutie", "cutie", "cutie");
	add(root, "zebra", "zebra", "zebra");
	add(root, "1poop", "1poop", "1poop");
	
	LNR(root);

	root = delete(root, "poop");

	LNR(root);

	root = delete(root, "2poop");
	LNR(root);
	root = delete(root, "1poop");
	LNR(root);
	root = delete(root, "cutie");
	LNR(root);
}
