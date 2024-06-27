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

ArrayList* createAList() {
    ArrayList* list = (ArrayList*) malloc(sizeof(ArrayList)); // B - ArrayList (1)
    list->elements = NULL;
    list->size = 0;
    return list;
}

void addToAList(ArrayList* list, void* address) {
    void** elements = malloc(sizeof(void*) * (++list->size)); // B - void** (1)
    for(int i=0; i<list->size-1; i++) {
        elements[i] = list->elements[i];
    }
    elements[list->size-1] = address;
    free(list->elements); // R - void** (1)
    list->elements = elements;
}

void* getElementFromAList(const ArrayList* list, const int index) {
    if(index < 0 || list->size < index) return NULL;
    return list->elements[index];
}

int removeFromAListByAddress(ArrayList* list, const void* address) {
    void** elements = malloc(sizeof(void*) * (--list->size)); // B - void** (2)
    int a = -1;
    for(int i=0,off=0; i<list->size+off; i++) {
        if(elements[i]==address) {
            off++;
            a = i;
        }
        else elements[i-off] = list->elements[i];
    }
    if(a==-1) {
        free(elements); // R - void** (2)
    }else {
        free(list->elements); // R - void** (2)
        list->elements = elements;
    }
    return a;
}

void* removeFromAList(ArrayList* list, const int index) {
    if(index > list->size) return NULL;
    void** elements = malloc(sizeof(void*) * (--list->size)); // B - void** (3)
    void* t = list->elements[index];
    for (int i=0,off=0; i<list->size; i++) {
        if(i==index) {
            off++;
        }else elements[i-off] = list->elements[i];
    }
    free(list->elements); // R - void** (3)
    list->elements = elements;
    return t;
}

void destroyAList(ArrayList* list) {
    free(list->elements); // R - void** (1,2,3)
    free(list); // R - ArrayList (1)
}