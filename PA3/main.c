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
		} else if (scanNum == 2 && !strcmp(userInput, "*DELETE")) {
			//delete stuff
		} else {
			// search stuff
		}
	}

	treeFree(myTree);
	return 0;
}
