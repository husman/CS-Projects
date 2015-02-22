#include <gtest/gtest.h>

#include "../include/euler-project.h"


TEST(smallest_multiple_of_one_through_n, is_divisible_by_one_through_n) {
    ASSERT_EQ(2, smallest_multiple_of_one_through_n(2));
    ASSERT_EQ(6, smallest_multiple_of_one_through_n(3));
    ASSERT_EQ(12, smallest_multiple_of_one_through_n(4));
    ASSERT_EQ(2520, smallest_multiple_of_one_through_n(10));
    ASSERT_EQ(232792560, smallest_multiple_of_one_through_n(20));
}

TEST(print_tree_post_order, can_print_max_tree_items_in_order) {
    tree f, e, d, c, b, a;
    f.value = 'f';
    e.value = 'e';
    d.value = 'd';
    c.value = 'c';
    b.value = 'b';
    a.value = 'a';


    a.left = a.right = NULL;
    b.left = b.right = NULL;
    c.left = c.right = NULL;
    e.left = NULL;

    f.left = &d;
    f.right = &e;
    d.left = &a;
    d.right = &b;
    e.right = &c;

    printf("\n\n\n\n");
    print_tree_post_order(&f);
    printf("\n\n\n\n");
}

TEST(print_tree_lowest_level_order, can_print_max_tree_items_in_order) {
    tree f, e, d, c, b, a;
    f.value = 'f';
    e.value = 'e';
    d.value = 'd';
    c.value = 'c';
    b.value = 'b';
    a.value = 'a';


    a.left = a.right = NULL;
    b.left = b.right = NULL;
    c.left = c.right = NULL;
    e.left = NULL;

    f.left = &d;
    f.right = &e;
    d.left = &a;
    d.right = &b;
    e.right = &c;

    printf("\n\n\n\n");
    print_tree_lowest_level_order(&f);
    printf("\n\n\n\n");
}