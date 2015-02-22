#include <gtest/gtest.h>

#include "../include/euler-project.h"


TEST(find_largest_prime_factor, returns_the_biggest_prime_factor_for_a_number) {
    ASSERT_EQ(1, find_largest_prime_factor_of(1));
    ASSERT_EQ(2, find_largest_prime_factor_of(2));
    ASSERT_EQ(3, find_largest_prime_factor_of(3));
    ASSERT_EQ(5, find_largest_prime_factor_of(5));
    ASSERT_EQ(7, find_largest_prime_factor_of(7));
    ASSERT_EQ(29, find_largest_prime_factor_of(29));
    ASSERT_EQ(5, find_largest_prime_factor_of(360));
    ASSERT_EQ(29, find_largest_prime_factor_of(13195));
    ASSERT_EQ(6857, find_largest_prime_factor_of(600851475143));
}