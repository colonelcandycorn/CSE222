/*
	Sarah Dylan CSE222 PA4 03/02/2023

	This program is a solution to the unlimited knapsack problem utilizing dynamic
	programming. The unlimited knapsack problem is where someone is trying to find
	the most profitable combination of items they can fit into a knapsack that has
	a weight limit. You are given a list of items that have a corresponding weight
	and value. The unlimited aspect comes into play because it assumes that there
	is no limit of the number of any one item you can grab; the only limitation is
	the weight you want to grab doesn't exceed the capacity of your knapsack.

	To solve this problem, we use a greedy algorithm to determine the best option at
	each stage. Given a starting weight we select an item, subtract the weight of the
	item from our knapsack capacity, and find the solution of the knapsack problem with
	the new, smaller weight. We then test the solution if we had chosen another item. We
	continue this process until at we pick the best solution at every possible weight and
	item combination.

	The solution of this problems can involve an exceedlingly high number of recursive
	calls, which can be very inefficient because a lot of the recursive calls will be
	repeats. The solution to the inefficiency lies in storing the results of the recursive
	calls so that at the start of each call we make a check to see if we have already
	calculated the result before. 

	To use this program, the user needs to supply exactly two arguments: a knapsack capacity
	and a file to read the item name, value, weight combinations. We then run our function,
	print the results, free the memory, and close the program.
	
*/



#include <stdio.h>
#include "max.h"
#include <stdlib.h>
#define MAX_STR 256

int main(int argc, char **argv) {

	// program needs exactly two arguments

    if (argc != 3) {
		puts("Incorrect Number of Arguments. Expecting \"programName size dataFile\"");
		return 1;
	}

	// atoi will return 0 if the user types 0 or if they type a string
	// so unless the user types a number between 1 and 1024 the program won't run

	char *dbName = argv[2];
	int knapSackCapacity = atoi(argv[1]);

	if (knapSackCapacity <= 0 || knapSackCapacity > 1024) {
		puts("Error: weight must be between 0 and 1024");
		return 1;
	}


	// open the db file and start processing the data
	// I opted to store the information in three different arrays
	// I pass each array to the max function so it might be cleaner looking to store everything in a struct

	FILE *file = fopen(dbName, "r");

	if (!file) {
		puts("Error: Invalid file name");
		return 1;
	}


	char itemNames[128][32];
	int weights[128];
	int values[128];
	int size = 0;
	char input[MAX_STR];

	while (fgets(input, MAX_STR, file)) {
		if (sscanf(input, "%s%d%d", itemNames[size], &values[size], &weights[size]) != 3) {
			puts("Error with Database Inputs");
			return 1;
		}

		++size;
	}

	fclose(file);

	// Everything has been initialized correctly so we need to prepare memory for the list of solutions
	// I test at the start of each call whether dynamicKnaps[whatever weight] has been set so I need to ensure
	// that the memory is set to NULL. I had a problem where malloc was reusing the memory from fopen

	struct knapSack **dynamicKnaps = calloc((knapSackCapacity + 1), sizeof(struct knapSack));	

	struct knapSack *bestKnap = max(knapSackCapacity, weights, values, size, dynamicKnaps);

	// We successfully calculated the best combination so we record our results to the user.

	puts("Weight  Value  Name");
	puts("------  -----  ----");
	for (int i = 0; i < size; ++i) {
		printf("%6d  %5d  %s\n", weights[i], values[i], itemNames[i]);
	}
	puts("-------------------");

	printf("Bag's capcity = %d\n", knapSackCapacity);
	printf("Highest possible value = %d\n", bestKnap->totalValue);
	for (int i = 0; i < size; ++i) {
		if (bestKnap->items[i]) {
			printf("Item %d (%s): %d\n", i, itemNames[i], bestKnap->items[i]);
		}
	}

	// I made a helper function that frees the array stored inside of our knapsack struct and the pointer itself
	// at the end all that is left is to free dynamicKnaps

		
	for (int i = 0; i < knapSackCapacity + 1; ++i) {
		freeKnap(dynamicKnaps[i]);
	}

	free(dynamicKnaps);

	return 0;
}
