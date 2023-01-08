//
// Sarah Dylan 1/5/23 CSE222 PA1
//

#ifndef PA1_MAIN_H
#define PA1_MAIN_H

struct DataNode {
    char data[16];
    struct DataNode *next;
};

struct DataNode *init();
int add(struct DataNode *list, char *data);
void print(struct  DataNode *list);
int myDelete(struct DataNode *list, char *data);
int search(struct DataNode *list, char *data);
void cleanup(struct DataNode *list);

#endif //PA1_MAIN_H
