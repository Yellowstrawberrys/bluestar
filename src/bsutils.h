//
// Created by 정은수 on 2024. 6. 13..
//

#ifndef BSUTILS_H
#define BSUTILS_H
#include <stddef.h>

typedef struct _lnode {
    void* address;
    struct _lnode* next;
} LNode;

typedef struct _list {
    LNode* head;
    int size;
} List;

List* createList();
void destroyList(List* list);
void addToList(List* list, void* address);
int removeFromListByAddress(List* list, const void* address);
void* removeFromList(List* list, const int index);

#endif //BSUTILS_H
