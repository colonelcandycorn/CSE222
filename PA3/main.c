/*
	Sarah Dylan CSE222 PA3 02/23/2023

	This program is more or less the same as PA2: we store a database
	of license plates that has an associated first and last name, and
	allow the user to query the database and delete from it. The key
	difference being that in this project the database is stored as a
	BST. The BST offers O(log(n)) search times if the tree is balanced,
	and it has the benefit of being sorted so we can print the license
	plates in alphabetical order.

	The program accepts exactly one argument which must be the name of the
	database file. It returns an error if there are too few or too many args.
	
	We then initialize variables to store input, plates, first and last names,
	and a scanNum (keeps track of how many things are entered by user). We open
	the database file specfied by the user and make sure that it is read correctly.
	We also initialize our tree to NULL. We read each line of the file, and each time
	call the add function to add the new plate into our BST.

	Once the file is read we close it and start taking commands. The user can enter
	a plate to search for, *DUMP, or *DELETE 'plate'. If they just enter one argument
	and it isn't the word '*DUMP' we assume they are searching for a plate and call the
	search function. If the search function succeeds, we print out the name of the owner
	of the specified plate. The *DUMP command follows the instructions provided by the
	project instructions: we print the height, whether the tree is balanced, and print inorder
	preorder and postorder. The *DELETE will first search for the plate and return an
	error if it isn't there. If it is found, we delete the plate and print success.

	The program will exit when it encounters EOF.

*/
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include "tree.h"

#define MAX_STR 257 // arbitrary size for max length of string

int main(int argc, char **argv) {
	char *dbName;

	// Confirm the correct argc value, which should be exactly 2
	if (argc != 2) {
		puts("Error starting program");
		argc > 2 ? puts("too many arguments") : puts("too few arguments");
		return 1;
	}

	// database file is stored in the second position of the arg array
	dbName = argv[1];

	//we don't have an init function so we set our tree to NULL
	Node myTree = NULL;

	FILE *file = fopen(dbName, "r");
	char input[MAX_STR]; 
	char plate[MAX_STR];
	char first[MAX_STR];
	char last[MAX_STR];
	int scanNum = 0;

	// make sure file opened or exists
	if (!file) {
		puts("ERROR READING FILE");
		return 1;

	//start scanning the file and store the plate, first, and last names into our tree
	} else {
		while (fgets(input, MAX_STR, file)) {
			if (scanNum = sscanf(input, "%s%s%s", plate, first, last) != 3) {
				puts("ERROR INPUTTING"); //if the database is corrupted for some reason
				return 1;
			}
			myTree = add(myTree, plate, first, last);
		}
	}
	fclose(file);

	// If we made it this far, we are open for business and can start accepting commands

	char userInput[MAX_STR]; // used if one argument
	char userPlate[MAX_STR]; // used if two arguments
	int isRunning = 1; // we never change so could just use 1 instead of variable
	while (isRunning) {
		printf("Enter command or plate: "); 
		if (!fgets(input, MAX_STR, stdin)) break; // exit if eof

		scanNum = sscanf(input, "%s%s", userInput, userPlate); //check for two args


		// if we have one argument and it's *DUMP then print everything we know
		if (scanNum == 1 && !strcmp(userInput, "*DUMP")) {
			//Print height, balance, inorder, preorder, and then postorder
			printf("TREE HEIGHT: %d\n", height(myTree));
			printf("BALANCED: %s\n\n", balanced(myTree) ? "YES" : "NO");
			puts("LNR TRAVERSAL");
			LNR(myTree);
			puts("");
			puts("NLR TRAVERSAL");
			NLR(myTree);
			puts("");
			puts("LRN TRAVERSAL");
			LRN(myTree);
			puts("");
		} else if (scanNum == 2 && !strcmp(userInput, "*DELETE")) {
			//Search and then delete
			if (!search(myTree, userPlate, first, last)) {
				 printf("user plate is %s\n", userPlate);
				 puts("PLATE NOT FOUND");
				 continue;
			}

			myTree = delete(myTree, userPlate);
			puts("SUCCESS");
		} else {
			// One argument and not *DUMP means we just search for plate
			if (!search(myTree, userInput, first, last)) {
				puts("PLATE NOT FOUND");
				continue;
			}
			printf("First name: %s\n", first);
			printf("Last name: %s\n", last);
		}
	}

	treeFree(myTree); // Free all of our memory
	return 0;
}
