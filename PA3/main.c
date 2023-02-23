#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include "tree.h"

#define MAX_STR 257
int main(int argc, char **argv) {
	char *dbName;

	if (argc != 2) {
		puts("Error starting program");
		argc > 2 ? puts("too many arguments") : puts("too few arguments");
		return 1;
	}

	dbName = argv[1];

	Node myTree = NULL;

	FILE *file = fopen(dbName, "r");
	char input[MAX_STR]; 
	char plate[MAX_STR];
	char first[MAX_STR];
	char last[MAX_STR];
	int scanNum = 0;
	int cellNum = 0;

	// make sure file opened or exists
	if (!file) {
		puts("ERROR READING FILE");
		return 1;

	//start scanning the file and store the plate, first, and last names into our hashmap
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

	char userInput[MAX_STR];
	char userPlate[MAX_STR];
	int isRunning = 1;
	while (isRunning) {
		printf("Enter command or plate: "); 
		if (!fgets(input, MAX_STR, stdin)) break; // exit if eof

		scanNum = sscanf(input, "%s%s", userInput, userPlate); //check for two args

		if (scanNum == 1 && !strcmp(userInput, "*DUMP")) {
			//do stuff
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
			//delete stuff
			if (!search(myTree, userPlate, first, last)) {
				 printf("user plate is %s\n", userPlate);
				 puts("PLATE NOT FOUND");
				 continue;
			}

			myTree = delete(myTree, userPlate);
			puts("SUCCESS");
		} else {
			// search stuff
			if (!search(myTree, userInput, first, last)) {
				puts("PLATE NOT FOUND");
				continue;
			}
			printf("First name: %s\n", first);
			printf("Last name: %s\n", last);
		}
	}

	treeFree(myTree);
	return 0;
}
