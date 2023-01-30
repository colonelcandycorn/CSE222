#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR 257

int main(int argc, char **argv) {
	char *dbName;
	hashEntry* myHash;
	int hashSize = 50;
	if (argc == 2 ) {
		myHash = hashInit(50);
	} else if (argc == 3 && (hashSize = atoi(argv[1])) >= 1) {
		myHash = hashInit(hashSize);
	} else {
		puts("ERROR WITH ARGUMENTS");
		return 1;
	}

	dbName = argv[argc - 1];

	FILE *file = fopen(dbName, "r");
	char input[MAX_STR];
	char plate[MAX_STR];
	char first[MAX_STR];
	char last[MAX_STR];
	int scanNum = 0;
	int cellNum = 0;
	if (!file) {
		puts("ERROR READING FILE");
		return 1;
	} else {
		while (fgets(input, MAX_STR, file)) {
			if (scanNum = sscanf(input, "%s%s%s", plate, first, last) != 3) {
				puts("ERROR INPUTTING");
				return 1;
			}
			hashAdd(myHash, plate, first, last);
		}
	}
	fclose(file);

	
	char userInput[MAX_STR];
	int isRunning = 1;
	while (isRunning) {
		printf("Enter command or plate: ");
		if (!fgets(input, MAX_STR, stdin)) isRunning = 0; //check for EOF
		scanNum = sscanf(input, "%s%d", userInput, &cellNum); //check for two args
		if (!strcmp(userInput, "*DUMP")) {
			if (scanNum == 2) {
				if (cellNum >= hashSize || cellNum < 0) {
					puts("ERROR: INCORRECT CELL NUMBER");
					continue;
				}
				hashDump(myHash, cellNum);
			} else {
				for (int i = 0; i < hashSize; ++i) {
					hashDump(myHash, i);
				}
			}
		} else if (!strcmp(userInput, "*DIST")) {
			hashDist(myHash);
		} else {
			if (!hashFind(myHash, userInput, first, last)) {
				puts("Plate not found.");
				continue;
			}
			printf("First name: %s\n", first);
			printf("Last name: %s\n", last);
		}
	}
	
	hashFree(myHash);
	return 0; 
}
