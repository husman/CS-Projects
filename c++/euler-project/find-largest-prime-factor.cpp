#include "include/euler-project.h"


uint64_t find_largest_prime_factor_of(uint64_t number) {
    uint64_t largest_prime = 2;

    if(number <= 3)
        return number;

    while(number != largest_prime) {

        if(number % largest_prime == 0)
            number = number/largest_prime;
        else
            ++largest_prime;
    }

    return largest_prime;
}