#include <cstdlib>
#include <cstdio>
#include <stdexcept>

class Stack {
private:
    Stack *head_ptr, *next_ptr;
    char data;
    int number_of_elements;
public:
    Stack();
    void push(char value);
    char pop();
    char top();
    int count();
};