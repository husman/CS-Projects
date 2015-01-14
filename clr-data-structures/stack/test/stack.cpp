#include <gtest/gtest.h>

#include "../include/stack.h"

TEST(Stack, can_push_items_into_stack) {
    Stack *stack = new Stack();

    ASSERT_EQ(0, stack->count());

    stack->push('G');
    stack->push('o');
    stack->push('o');
    stack->push('g');
    stack->push('l');
    stack->push('e');

    ASSERT_EQ(6, stack->count());
}

TEST(Stack, elements_are_popped_from_stack_in_first_in_last_out_order) {
    Stack *stack = new Stack();

    stack->push('D');
    stack->push('o');
    stack->push('g');

    ASSERT_EQ(3, stack->count());
    ASSERT_EQ('g', stack->pop());
    ASSERT_EQ('o', stack->pop());
    ASSERT_EQ('D', stack->pop());
    ASSERT_EQ(0, stack->count());
}

TEST(Stack, can_view_element_at_top_without_popping_from_stack) {
    Stack *stack = new Stack();

    stack->push('C');
    stack->push('a');
    stack->push('t');

    ASSERT_EQ(3, stack->count());
    ASSERT_EQ('t', stack->top());
    ASSERT_EQ(3, stack->count());
    ASSERT_EQ('t', stack->pop());

    ASSERT_EQ(2, stack->count());
    ASSERT_EQ('a', stack->top());
    ASSERT_EQ(2, stack->count());
    ASSERT_EQ('a', stack->pop());

    ASSERT_EQ(1, stack->count());
    ASSERT_EQ('C', stack->top());
    ASSERT_EQ(1, stack->count());
    ASSERT_EQ('C', stack->pop());

    ASSERT_EQ(0, stack->count());
}

TEST(Stack, popping_elements_when_there_is_nothing_in_the_stack_raises_exception) {
    Stack *stack = new Stack();

    try {
        stack->pop();
        FAIL();
    } catch (std::range_error &error) {
        ASSERT_STREQ("No items on the stack.", error.what());
    }

    stack->push('H');
    stack->pop();

    try {
        stack->pop();
        FAIL();
    } catch (std::range_error &error) {
        ASSERT_STREQ("No items on the stack.", error.what());
    }
};

TEST(Stack, attempt_to_view_element_on_top_of_stack_when_stack_has_no_items_raises_exception) {
    Stack *stack = new Stack();

    try {
        stack->top();
        FAIL();
    } catch(std::range_error &error) {
        ASSERT_STREQ("No items on the stack.", error.what());
    }

    stack->push('a');
    stack->pop();

    try {
        stack->top();
        FAIL();
    } catch(std::range_error &error) {
        ASSERT_STREQ("No items on the stack.", error.what());
    }
}
