//
// Created by 정은수 on 2024. 6. 13..
//

#include "bsutils.h"

#include <stdlib.h>

List* createList() {
    List* list = (List*)malloc(sizeof(List));
    return list;
}

void destroyList(List* list) {
    free(list);
}

void addToList(List* list, int address) {
    LNode* toAdd = malloc(sizeof(LNode)); // B - LNode (1)
    toAdd->address = address;
    toAdd->next = NULL;
    if(!list->head) {
        list->head = toAdd;
        list->size++;
    }else {
        LNode* node = list->head;
        for(int i=0; i<list->size; i++) {
            node = node->next;
        }
        node->next = toAdd;
    }
}

int removeToListByAddress(List* list, int address) {
    LNode* bef = NULL;
    LNode* node = list->head;
    for(int i=0; i<list->size; i++) {
        if(node->address == address) {
            if (bef) bef->next = node->next;
            else list->head = node->next;
            list->size--;
            free(node); // R - LNode (1)
            return i;
        }
        bef = node;
        node = node->next;
    }
    return -1;
}

int removeToList(List* list, int index) {
    LNode* bef = NULL;
    LNode* node = list->head;
    if(list->size < index) return -1;
    for(int i=0; i<index-1; i++) {
        bef = node;
        node = node->next;
    }
    if(!bef) list->head = node->next;
    else bef->next = node->next;
    const int ad = node->address;
    list->size--;
    free(node); // R - LNode (1)
    return ad;
}