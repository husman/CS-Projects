#include <gtest/gtest.h>

#include "../include/vertex.h"


TEST(Vertex, can_hold_multiple_items) {
    Vertex v1, v2, v3;
    v1.value = 'a';
    v2.value = 'b';
    v3.value = 'c';
    v1.next = &v2;
    v2.next = &v3;

    Vertex *node = &v1;
    ASSERT_EQ(node->value, 'a');

    node = node->next;
    ASSERT_EQ(node->value, 'b');

    node = node->next;
    ASSERT_EQ(node->value, 'c');
}