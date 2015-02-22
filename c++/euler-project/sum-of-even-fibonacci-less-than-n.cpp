#include "include/euler-project.h"


int sum_of_even_fibonacci_less_than_n(int number) {
    int sum = 0;

    if(number < 2)
        return 0;

    sum = 2;

    int previous_number = 1;
    int current_number = 2;
    int next_number = previous_number + current_number;

    while(next_number < number) {
        if(next_number%2 == 0)
            sum += next_number;

        previous_number = current_number;
        current_number = next_number;
        next_number = previous_number + next_number;
    }

    return sum;
}