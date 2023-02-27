#include <stdio.h>
#include <malloc.h>

struct knapSack {
    int totalValue;
    int *items;
};

struct knapSack *max(int w, int *wt, int*val, int size, struct knapSack** dKnaps);

int main() {
    int weight = 3378;
    int weights[] = {1, 2, 7, 5};
    int val[] = {10, 21, 40 ,200};


    struct knapSack **dynamicKnaps = (struct knapSack **)malloc(sizeof(struct knapSack) * (weight + 1));

    struct knapSack * best = max(weight, weights, val, 4, dynamicKnaps);

    printf("The total value is %d\n", best->totalValue);

    for (int i = 0; i < 4; ++i) {
        printf("There are %d of item %d\n", best->items[i], i);
    }


    return 0;
}

//struct knapSack *maxValue(int w, int *wt, int *val, int size, struct knapSack *knap, struct knapSack **dKnaps, int index) {
//    if (dKnaps[w]) return dKnaps[w];
//
//    struct knapSack* newKnap = (struct knapSack *)malloc(sizeof(struct knapSack));
//
//    newKnap->totalValue = knap->totalValue;
//    if (index >= 0) newKnap->totalValue += val[index];
//    newKnap->items = (int *)malloc(sizeof(int) * size);
//
//    for (int i = 0; i < size; ++i) {
//        newKnap->items[i] = i == index ? knap->items[i] + 1 : knap->items[i];
//    }
//
//    if (w == 0) return newKnap;
//
//    struct knapSack *tempKnap;
//    struct knapSack *bestKnap = NULL;
//    int bestValue = newKnap->totalValue;
//    int bestWeight;
//
//    for (int i = 0; i < size; ++i) {
//        int newWeight = w - wt[i];
//        if (newWeight < 0) continue;
//        tempKnap = maxValue(w - wt[i], wt, val, size, newKnap, dKnaps, i);
//        if (tempKnap->totalValue > bestValue) {
//            bestKnap = tempKnap;
//            bestWeight = newWeight;
//        } else {
//            if (dKnaps[newWeight] != tempKnap) free(tempKnap);
//        }
//    }
//
//    dKnaps[bestWeight] = bestKnap;
//
//    return bestKnap ? bestKnap : newKnap;
//}

struct knapSack *max(int w, int *wt, int*val, int size, struct knapSack** dKnaps) {
    if (dKnaps[w]) return dKnaps[w];


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

    for (int i = 0; i < size; ++i) {
        int newWeight = w - wt[i];
        if (newWeight < 0) continue;

        tempKnaps[i] = max(newWeight, wt, val, size, dKnaps);

        if (tempKnaps[i]->totalValue + val[i] > bestValue) {
            bestValue = tempKnaps[i]->totalValue + val[i];
            bestIndex = i;
        }
    }

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

