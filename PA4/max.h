#ifndef PA4_MAX_H
#define PA4_MAX_H

struct knapSack {
    int totalValue;
    int *items;
};

struct knapSack *max(int w, int *wt, int*val, int size, struct knapSack** dKnaps);
void freeKnap(struct knapSack *deleteKnap);

#endif 
