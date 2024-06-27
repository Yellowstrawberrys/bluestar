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

typedef struct _alist {
    void** elements;
    int size;
} ArrayList;

// Linked List
List* createList();
void destroyList(List* list);
void addToList(List* list, void* address);
int removeFromListByAddress(List* list, const void* address);
void* removeFromList(List* list, const int index);

// ArrayList
ArrayList* createAList();
void addToAList(ArrayList* list, void* address);
void* getElementFromAList(const ArrayList* list, const int index);
int removeFromAListByAddress(ArrayList* list, const void* address);
void* removeFromAList(ArrayList* list, const int index);
void destroyAList(ArrayList* list);

// min max (integer)
int imin(const int a, const int b);
int imax(const int a, const int b);

#endif //BSUTILS_H
