#include "include/stack.h"

Stack::Stack() {
    next_ptr = NULL;
    head_ptr = this;
    number_of_elements = 0;
}

void Stack::push(char value) {
    if(number_of_elements == 0) {
        data = value;
        ++number_of_elements;
        return;
    }

    Stack *node = new Stack();
    node->data = value;
    node->next_ptr = head_ptr;

    ++number_of_elements;
    head_ptr = node;
}

char Stack::pop() {
    if(head_ptr == NULL || count() == 0)
        throw std::range_error("No items on the stack.");

    Stack *next_node = head_ptr->next_ptr;
    char value = head_ptr->data;

    free(head_ptr);
    head_ptr = next_node;

    --number_of_elements;
    return value;
}

char Stack::top() {
    if(head_ptr == NULL || count() == 0)
        throw std::range_error("No items on the stack.");

    return head_ptr->data;
}

int Stack::count() {
    return number_of_elements;
}
