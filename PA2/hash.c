#include "hash.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int size;

int hash(char *plate) {
	int ret = 0;
	for (int i = 0; i < strlen(plate); ++i) {
		ret += (2 * i + 3) * (2 * i + 3) * plate[i];
	}
	return ret;
}

hashEntry *hashInit(int hashsize) {
	size = hashsize;
	hashEntry *temp = (hashEntry *)malloc(sizeof(hashEntry) * hashsize);
	for (int i = 0; i < hashsize; ++i) {
		temp[i] = listInit();
	}
	return temp;
}

void hashAdd(hashEntry *hashTable, char *plate, char *first, char *last) {
	int hashValue = hash(plate) % size;
	listAdd(hashTable[hashValue], plate, first, last);
}

int hashFind(hashEntry *hashTable, char *plate, char *first, char *last) {
	int hashValue = hash(plate) % size;
	if (listFind(hashTable[hashValue], plate, first, last)) return 1;
	return 0;
}

void hashDist(hashEntry *hashTable) {
	for (int i = 0; i < size; ++i) {
		printf("Entry %2d: length=%3d\n", i, listLen(hashTable[i]));
	}
}

void hashDump(hashEntry *hashTable, int cellNum) {
	listPrint(hashTable[cellNum]);
}

void hashFree(hashEntry *hashTable) {
	for (int i = 0; i < size; ++i) {
		listFree(hashTable[i]);
	}
	free(hashTable);
}
