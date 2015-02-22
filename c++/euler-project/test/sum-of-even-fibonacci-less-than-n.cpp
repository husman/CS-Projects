#include <gtest/gtest.h>

#include "../include/euler-project.h"


TEST(sum_of_even_fibonacci_less_than_n, can_find_the_sum_of_even_fibonacci_numbers) {
    ASSERT_EQ(0, sum_of_even_fibonacci_less_than_n(0));
    ASSERT_EQ(2, sum_of_even_fibonacci_less_than_n(2));
    ASSERT_EQ(10, sum_of_even_fibonacci_less_than_n(15));
    ASSERT_EQ(44, sum_of_even_fibonacci_less_than_n(50));
    ASSERT_EQ(4613732, sum_of_even_fibonacci_less_than_n(4000000));
}