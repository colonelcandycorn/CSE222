/*
	Sarah Dylan CSE222 PA4 03/02/2023

	This is my implementation of solving the unlimited knapsack problem
	using recursion. I also included a utility funciton in this file for
	freeing memory after the program has completed running.
	
	max is a relatively complicated function that requires 5 parameters:
	a knapsack capacity(w), a list of item weights(wt), a list of item
	values(val), an int that is the size of the wt and val arrays, and
	finally a struct that stores solutions returned by max. 

	The same index for val and wt represent the same item (index 0 for wt and
	val gives the corresponding weight and value of item 0)

	The knapsack struct that is returned has a associated totalvalue that represents
	the monetary worth of everything it is carrying. It also has a items array
	where each index corresponds the same items from val and wt arrays. The value
	at each index indicates how many of each item the knapsack contains.

	Our first step in the function is to check to see if we have already solved max
	given weight, w.

	When then check our basecase which is when weight is 0. If it is 0 then we return
	a empty knapsack. 

	If we haven't solved it and the weight isn't zero, we iterate through each item,
	subtract its weight from w and call max with the new weight. We store the result
	in our tempknaps array. We see which result return the highest value and then increment
	the item and value, store the result in dKnaps, and return the result.
*/


#include <stdlib.h>
#include "max.h"

struct knapSack *max(int w, int *wt, int*val, int size, struct knapSack** dKnaps) {

	// check if we have solved the problem for this weight 

    if (dKnaps[w]) return dKnaps[w];


	// check our base case

    if (!w) {
        struct knapSack* newKnap = (struct knapSack *)malloc(sizeof(struct knapSack));

        newKnap->totalValue = 0;
        newKnap->items = (int *)malloc(sizeof(int) * size);

        for (int i = 0; i < size; ++i) {
            newKnap->items[i] = 0;
        }

        dKnaps[w] = newKnap;
        return newKnap;
    }

    struct knapSack * tempKnaps[size];
    struct knapSack * newKnap;
    int bestValue = 0;
    int bestIndex;

	// compare the results of our recursive calls
	// this is based on the amount of items in our datafile
	// we also check to see if subtracting the weight of a given item would give us a capacity less than zero
	// this prevents us from calling max with a negative carrying capacity
    for (int i = 0; i < size; ++i) {
        int newWeight = w - wt[i];
        if (newWeight < 0) continue;

        tempKnaps[i] = max(newWeight, wt, val, size, dKnaps);

        if (tempKnaps[i]->totalValue + val[i] > bestValue) {
            bestValue = tempKnaps[i]->totalValue + val[i];
            bestIndex = i;
        }
    }

	// we know the best combination now so we create a new struct knapsack to store it
	// we place it in dKnaps after incrementing the items list and the total value
    newKnap = (struct knapSack *)malloc(sizeof(struct knapSack));
    newKnap->items = (int *)malloc(sizeof(int) * size);
    newKnap->totalValue = bestValue;

    for (int i = 0; i < size; ++i) {
        if (i == bestIndex) {
            newKnap->items[i] = tempKnaps[bestIndex]->items[i] + 1;
        } else {
            newKnap->items[i] = tempKnaps[bestIndex]->items[i];
        }
    }

    dKnaps[w] = newKnap;

    return newKnap;
}

// simple utility for freeing memory once we are done

void freeKnap(struct knapSack *deleteKnap) {
	free(deleteKnap->items);
	free(deleteKnap);
}
