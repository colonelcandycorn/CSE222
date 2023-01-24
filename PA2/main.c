#include "hash.h"
#include <stdio.h>

int main(int argc, char **argv) {
	struct node *test = listInit();
	listAdd(test, "123", "Sarah", "Dylan");
	listPrint(test);
	int num = hash(test->next->plate);
	printf("%d\n", num); 	
	listFree(test);


	hashEntry *myHash = hashInit(50);
	hashAdd(myHash, "123", "Sarah", "Dylan");
	hashDist(myHash);
	hashDump(myHash, hash("123")%50);
	hashFree(myHash);
	return 0; 
}
