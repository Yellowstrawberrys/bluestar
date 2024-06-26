//
// Created by 정은수 on 2024. 6. 13..
//

#include "bsutils.h"
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

int imin(const int a, const int b) {
    return a<b?a:b;
}

int imax(const int a, const int b) {
    return a>b?a:b;
}

List* createList() {
    List* list = (List*)malloc(sizeof(List));
    list->head = NULL;
    return list;
}

void destroyList(List* list) {
    LNode* node = list->head;
    while (node) {
        LNode* next = node->next;
        free(node); // R - LNode (1)
        node = next;
    }
    free(list);
}

void addToList(List* list, void* address) {
    LNode* toAdd = malloc(sizeof(LNode)); // B - LNode (1)
    toAdd->address = address;
    toAdd->next = NULL;
    if(list->head) {
        LNode* node = list->head;
        for(int i=0; i<list->size-1; i++) {
            node = node->next;
        }
        node->next = toAdd;
    }else {
        list->head = toAdd;
    }
    list->size++;
}

int removeFromListByAddress(List* list, const void* address) {
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

void* removeFromList(List* list, const int index) {
    LNode* bef = NULL;
    LNode* node = list->head;
    if(list->size < index) return NULL;
    for(int i=0; i<index-1; i++) {
        bef = node;
        node = node->next;
    }
    if(!bef) list->head = node->next;
    else bef->next = node->next;
    void* ad = node->address;
    list->size--;
    free(node); // R - LNode (1)
    return ad;
}

/**
 * @deprecated 램 누수
 */
void clearListWithValues(List* list) {
    LNode* node = list->head;
    while (node) {
        free(node->address);
        node = node->next;
        free(node); // R - LNode (1)
    }
    free(list);
}