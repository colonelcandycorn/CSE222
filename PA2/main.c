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

	myHash = hashInit(750);
	FILE *file = fopen("database.txt", "r");
	char input[257];
	char plate[257];
	char first[257];
	char last[257];
	int error = 0;
	if (!file) puts("ERROR");
	else {
		while (fgets(input, 257, file)) {
			if (error = sscanf(input, "%s%s%s", plate, first, last) != 3) {
				puts("ERROR inputting");
				printf("Number scanned = %d\n", error);
				printf("%s\n", input);
			}
			hashAdd(myHash, plate, first, last);
		}
	}
	fclose(file);

	for (int i = 0; i < 750; ++i) {
		listPrint(myHash[i]);
	}

	hashDist(myHash);
	hashFree(myHash);
	return 0; 
}
