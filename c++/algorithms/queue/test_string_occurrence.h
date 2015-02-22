#ifndef QUEUE_H
#define QUEUE_H


#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>


template <class ITEM_TYPE>
class Queue {
private:
    typedef struct List {
        List *next;
        ITEM_TYPE value;
    } List;

    List *head;
    List *current;
    int number_of_elements;

public:
    Queue();

    int length();
    void push(ITEM_TYPE &item);
    ITEM_TYPE pop();
};


template <class ITEM_TYPE>
Queue<ITEM_TYPE>::Queue() {
    number_of_elements = 0;
}

template <class ITEM_TYPE>
int Queue<ITEM_TYPE>::length() {
    return number_of_elements;
}

template <class ITEM_TYPE>
void Queue<ITEM_TYPE>::push(ITEM_TYPE &item) {
    if (&item == NULL)
        return;

    if (number_of_elements == 0) {
        head = (List *)malloc(sizeof(List));
        head->value = item;
        head->next = NULL;
        current = head;
    } else {
        List *new_node = (List *)malloc(sizeof(List));
        new_node->value = item;
        new_node->next = NULL;
        current->next = new_node;
        current = new_node;
    }
    ++number_of_elements;
}

template <class ITEM_TYPE>
ITEM_TYPE Queue<ITEM_TYPE>::pop() {
    ITEM_TYPE item = head->value;
    head = head->next;
    --number_of_elements;

    return item;
}

#endif