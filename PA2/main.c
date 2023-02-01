/*
	Sarah Dylan CSE222 PA2 01/30/2023

	This program is meant to demonstrate the functionality of my
	implementation of a hash map. The program accepts 1 or 2 arguments
	with the last argument always being the filename of a database. If
	there are 2 arguments the first should be the size of hashmap the
	user wants and then the last will be the file name. If no size is
	provided, the program will default to a size of 50. 
	
	The type of file meant to be read is a list of license plates with
	first and last names of the owners of the license plate. The hashmap
	creates an associative array between the hash value of the license plate
	and the associated first and last name. Because our hash function isn't perfect
	and the size of the hashmap is dependent on user input collisions will be
	unavoidable. Because of this our hashmap is an array of linked lists that will
	allow more than one node to be stored at each position.

	Our user can type in a plate and will receive back a first and last name.
	Alternatively they can enter three commands: *DIST which prints the lengths
	of each linked list at each array position, *DUMP someNumber will print all
	the values in the linked list at someNumber, and finally *DUMP which will just
	list every key-value pair out. 

*/

#include "hash.h"
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>

#define MAX_STR 257 // The documentaiton for PA2 stated 256 would be the limit for input

int main(int argc, char **argv) {
	char *dbName; //store database file name stored by user
	hashEntry* myHash;
	int hashSize = 50; //default to fifty if user doesn't request a size
	// argc equalling 2 means only one argument was supplied so initialize hash to default size
	if (argc == 2 ) {
		myHash = hashInit(50);
	// otherwise use the size specified by user and store that size for later use
	} else if (argc == 3 && (hashSize = atoi(argv[1])) >= 1) {
		myHash = hashInit(hashSize);
	// user must of have entered 0 or more than 2 arguments so ignore
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
			hashAdd(myHash, plate, first, last);
		}
	}
	fclose(file); 

	// our program has initialized correctly and we are ready for user input
	// usre input will continue until EOF
	char userInput[MAX_STR];
	int isRunning = 1;
	while (isRunning) {
		printf("Enter command or plate: ");
		if (!fgets(input, MAX_STR, stdin)) isRunning = 0; //check for EOF
		scanNum = sscanf(input, "%s%d", userInput, &cellNum); //check for two args

		//first we check if the user entered dumped and then we check if they entered
		// a number. If they entered the number we have to make sure its a valid index
		// otherwise, we will seg fault

		if (!strcmp(userInput, "*DUMP")) {
			if (scanNum == 2) {
				if (cellNum >= hashSize || cellNum < 0) {
					puts("ERROR: INCORRECT CELL NUMBER");
					continue;
				}
				hashDump(myHash, cellNum);
			} else {

				// we need to loop through the entire hashmap
				// use the size we stored earlier to loop through the array
				for (int i = 0; i < hashSize; ++i) {
					hashDump(myHash, i);
				}
			}

		// call the has dist function
		} else if (!strcmp(userInput, "*DIST") && scanNum == 1) {
			hashDist(myHash);

		// either they entered an incorrect command or they meant to look up a plate
		// if the plate is incorrect or an incorrect command is typed it will say
		// that a plate wasn't found
		} else {
			if (!hashFind(myHash, userInput, first, last)) {
				puts("Plate not found.");
				continue;
			}
			printf("First name: %s\n", first);
			printf("Last name: %s\n", last);
		}
	}
	

	// we reached EOF so free the memory and end
	hashFree(myHash);
	return 0; 
}
