
#ifndef PA2_HASH_H
#define PA2_HASH_H
#include "list.h"

typedef struct node *hashEntry;

hashEntry *hashInit(int hashsize);
int hash(char *plate);
void hashAdd(hashEntry *hashTable,
			 char *plate,
			 char *first,
			 char *last);
int hashFind(hashEntry *hashTable,
			 char *plate,
			 char *first,
			 char *last);
void hashDist(hashEntry *hashTable);
void hashDump(hashEntry *hashTable, int cellNum);
void hashFree(hashEntry *hashTAble);




#endif // PA2_HASH_H
