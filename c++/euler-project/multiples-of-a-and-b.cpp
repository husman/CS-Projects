#include "include/euler-project.h"


int sum_of_multiples_of(int a, int b, int upper_bound) {
    int sum = 0;
    int b_offset = std::abs(b - a);
    int a_and_b_are_multiples = b%a == 0 || a%b == 0;
    int z = 1;

    for(int i = a; i < upper_bound; i += a) {
        sum += i;

        int next_multiple_value = i + b_offset * z++;
        if(!a_and_b_are_multiples && next_multiple_value % a != 0 && next_multiple_value < upper_bound) {
            sum += next_multiple_value;
        }
    }
    return sum;
}