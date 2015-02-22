#ifndef EULER_PROJECT_H
#define EULER_PROJECT_H

#include <cstdio>
#include <iostream>

typedef struct tree {
    char value;
    tree *left;
    tree *right;
} tree;

int sum_of_multiples_of(int a, int b, int upper_bound);
uint64_t find_largest_prime_factor_of(uint64_t number);
int sum_of_even_fibonacci_less_than_n(int number);
int smallest_multiple_of_one_through_n(int number);
void print_tree_post_order(tree *t);
void print_tree_lowest_level_order(tree *t);

#endif