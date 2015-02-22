#include <gtest/gtest.h>

#include "../include/euler-project.h"


int sum_up_to_n(int a, int b, int c) {
    int sum = 0;
    int i = 0;
    while(i<c) {
        if(i%a == 0 || i%b == 0) {
            sum += i;
        }
        ++i;
    }
    return sum;
}

TEST(multiples_of_a_and_b, to_upper_bound_is_properly_calculated) {
    ASSERT_EQ(sum_up_to_n(3, 5, 10), sum_of_multiples_of(3, 5, 10));
    ASSERT_EQ(sum_up_to_n(2, 4, 10), sum_of_multiples_of(2, 4, 10));
    ASSERT_EQ(sum_up_to_n(3, 5, 1000), sum_of_multiples_of(3, 5, 1000));
};