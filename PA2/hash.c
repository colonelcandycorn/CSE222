/*

	Sarah Dylan CSE222 PA2 02/01/2023

	Implementation of the abstract data type, hash map. In this hash map
	we store our key-value pairs in an array of linked lists. We were given
	a hash function as a part of the assignment. Our hash function aren't
	particularly complex as most of the work is being done in the linked
	list functions. We have one global variable keeping track of size. Based
	on the load factor and the success of our hash function, we can gain
	amortized constant time access to any key value pair. 

*/

#include "hash.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int size; // global for keeping track of size

/*
	Parameters: plate string

	this is mostly a helper function that implements the hashing formula
	given by our assignment.

	Return: returns the hash value of the plate string

*/

int hash(char *plate) {
	int ret = 0;
	for (int i = 0; i < strlen(plate); ++i) {
		ret += (2 * i + 3) * (2 * i + 3) * plate[i];
	}
	return ret;
}

/*
	Parameters: integer size

	We initialize an array of linked lists of the given size. And then we
	use the list init function to initialize sentinel nodes in each array position

	Return: a pointer to our hashmap
*/

hashEntry *hashInit(int hashsize) {
	size = hashsize;
	hashEntry *temp = (hashEntry *)malloc(sizeof(hashEntry) * hashsize);
	for (int i = 0; i < hashsize; ++i) {
		temp[i] = listInit();
	}
	return temp;
}

/*
	Parameters: hashtable pointer, plate string, first name string, last name string

	We use our helper hash function to determine which index in our hashtable to store our new
	entry. We then call the list add function to add it to the linked list at the given index.
	
	Return: void
*/

void hashAdd(hashEntry *hashTable, char *plate, char *first, char *last) {
	int hashValue = hash(plate) % size;
	listAdd(hashTable[hashValue], plate, first, last);
}

/*
	Parameter: hashtable pointer, plate string, first name string, last name string

	We use our helper function again to determine which index to search for the given plate.
	We then use the list find function to store the found first and last name in the given pointers.

	Return: 1 for failure 0 for success
*/

int hashFind(hashEntry *hashTable, char *plate, char *first, char *last) {
	int hashValue = hash(plate) % size;
	if (listFind(hashTable[hashValue], plate, first, last)) return 1;
	return 0;
}

/*
	Parameters: hashtable pointer
	
	This is pretty simple: we go through each index of the hashtable and call the
	list len function to print a nice little message that will inform the user of
	the size of each linked list stored in the hash table.

	Return: void
*/

void hashDist(hashEntry *hashTable) {
	for (int i = 0; i < size; ++i) {
		printf("Entry %2d: length=%3d\n", i, listLen(hashTable[i]));
	}
}

/*

	Parameters: hashtable pointer, an int that tells us want index to print out
	
	We do a redundent check to make sure the function isn't called with an incorrect value.
	The main checks for this too so in theory this situation should never happen. We then
	print the contents of each cell using the list print function. We wrap our printed message
	in a format given by the assignment.

	Return: void
*/

void hashDump(hashEntry *hashTable, int cellNum) {
	if (cellNum >= size || cellNum < 0) return;

	printf("Contents of cell %d\n", cellNum);

	listPrint(hashTable[cellNum]);

	puts("----------------------------------");
}

/*
	Parameter: pointer to hashtable

	iterate through hashtable using a for loop. Call list free function on each index.
	Finally free the pointer to the hashtable.

	Return: void
*/

void hashFree(hashEntry *hashTable) {
	for (int i = 0; i < size; ++i) {
		listFree(hashTable[i]);
	}
	free(hashTable);
}
