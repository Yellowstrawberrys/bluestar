//
// Created by 정은수 on 2024. 6. 13..
//

#ifndef BSUTILS_H
#define BSUTILS_H

typedef struct _lnode {
    int address;
    struct _lnode *next;
} LNode;

typedef struct _list {
    LNode *head;
    int size;
} List;

List* createList();
void destroyList(List* list);
void addToList(List* list, int address);
void destroyList(List* list);

#endif //BSUTILS_H
