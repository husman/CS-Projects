#include <gtest/gtest.h>

#include "test_string_occurrence.h"

typedef struct Node {
    Node *next;
    char value;
} Node;

template class Queue<Node>;

TEST(Queue, arbitrary_item_types_added_to_queue_are_removed_first_in_first_out) {
    Queue<Node> queue;

    Node a, b, c;
    a.value = 'a';
    b.value = 'b';
    c.value = 'c';

    queue.push(a);
    queue.push(b);
    queue.push(c);

    ASSERT_EQ(queue.length(), 3);
    ASSERT_EQ(queue.pop().value, 'a');
    ASSERT_EQ(queue.pop().value, 'b');
    ASSERT_EQ(queue.pop().value, 'c');
}

TEST(Queue, standard_int_item_types_added_to_queue_are_removed_first_in_first_out) {
    Queue<int> queue;

    int a = 55, b = 12, c = 23;

    queue.push(a);
    queue.push(b);
    queue.push(c);

    ASSERT_EQ(queue.length(), 3);
    ASSERT_EQ(queue.pop(), 55);
    ASSERT_EQ(queue.pop(), 12);
    ASSERT_EQ(queue.pop(), 23);
}

TEST(Queue, standard_char_item_types_added_to_queue_are_removed_first_in_first_out) {
    Queue<char> queue;

    char f = 'f', b = 'b', r = 'r';

    queue.push(f);
    queue.push(b);
    queue.push(r);

    ASSERT_EQ(queue.length(), 3);
    ASSERT_EQ(queue.pop(), 'f');
    ASSERT_EQ(queue.pop(), 'b');
    ASSERT_EQ(queue.pop(), 'r');
}

TEST(Queue, queue_contains_number_of_elements_when_added_and_is_empty_when_all_elements_are_popped) {
    Queue<Node> queue;

    Node a, b, c, d;

    ASSERT_EQ(queue.length(), 0);

    queue.push(a);
    ASSERT_EQ(queue.length(), 1);

    queue.push(b);
    queue.push(c);
    ASSERT_EQ(queue.length(), 3);

    queue.push(d);
    ASSERT_EQ(queue.length(), 4);

    queue.pop();
    ASSERT_EQ(queue.length(), 3);

    queue.pop();
    queue.pop();
    queue.pop();
    ASSERT_EQ(queue.length(), 0);
}

char *bad_stuff() {
    char stuff[6] = "stuff";
    return stuff;
}

char *good_stuff() {
    char *stuff = new char[5];
    stuff[0] = 's';
    stuff[1] = 't';
    stuff[2] = 'u';
    stuff[3] = 'f';
    stuff[4] = 'f';
    return stuff;
}

TEST(MEMORY, stack_data_is_gone_outside_of_function_scope) {
    char *s = bad_stuff();
    ASSERT_NE('s', s[0]);
    ASSERT_NE('t', s[1]);
    ASSERT_NE('u', s[2]);
    ASSERT_NE('f', s[3]);
    ASSERT_NE('f', s[4]);
}

TEST(MEMORY, heap_data_is_present_outside_of_function_scope) {
    char *s = good_stuff();
    ASSERT_EQ('s', s[0]);
    ASSERT_EQ('t', s[1]);
    ASSERT_EQ('u', s[2]);
    ASSERT_EQ('f', s[3]);
    ASSERT_EQ('f', s[4]);
}
