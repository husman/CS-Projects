#ifndef HEAP_H
#define HEAP_H

#include <iostream>

class Heap {
public:
    Heap();
    void push(int value);
    int pop();

private:
    typedef struct List {
        List *parent;
        List *left_child;
        List *right_child;
        int value;
    } List;

    List *root;
};

Heap::Heap() {
    root = NULL;
}

void Heap::push(int value) {
    // create a new node for value
    List *new_value = new List();

    new_value->parent = NULL;
    new_value->left_child = NULL;
    new_value->right_child = NULL;
    new_value->value = value;

    if(root == NULL) {
        root = new_value;
        return;
    }

    // insert value into the last available node of the right most child in heap
    List *right_most_node = root;
    while(right_most_node != NULL) {
        if(right_most_node->left_child == NULL) {
            new_value->parent = right_most_node;
            right_most_node->left_child = new_value;
            break;
        } else if(right_most_node->right_child == NULL) {
            new_value->parent = right_most_node;
            right_most_node->right_child = new_value;
            break;
        }

        right_most_node = right_most_node->right_child;
    }

    // heapify from the current nodes parent upwards
    List *current_root_node = new_value->parent;
    while(current_root_node != NULL) {
        List *largest_child_node = current_root_node->left_child;
        if(
                largest_child_node != NULL && current_root_node->right_child != NULL
                && current_root_node->right_child->value > largest_child_node->value
        ) {
            largest_child_node->value = current_root_node->right_child->value;
        }

        if(current_root_node->value < largest_child_node->value) {
            int temp_value = current_root_node->value;
            current_root_node->value = largest_child_node->value;
            largest_child_node->value = temp_value;
        }

        current_root_node = current_root_node->parent;
    }
}

int Heap::pop() {
    List *old_root = root;
    int maximum_value = root->value;

    root = root->left_child;

    if(root != NULL && root->right_child != NULL && root->right_child->value > root->value)
        root = root->right_child;

    delete old_root;

    return maximum_value;
}

#endif