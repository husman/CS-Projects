#include <cstdio>
#include "include/power_digit_sum.h"


void print_array(char *arr, int len) {
    printf("\n\narray:\n");
    for(int i = 0; i < len; ++i)
        printf("%c", arr[i]);

    printf("\n\n");
}

void print_array_int(int *arr, int len) {
    printf("\n\narray:\n");
    for(int i = 0; i < len; ++i)
        printf("%d ", arr[i]);

    printf("\n\n");
}

int main(int argc, char **argv) {
//    int nums[10] = { 1, 45, 5, 8, 3, 22, 4, 2, 11, 6 };
//    int len = 10;
//
//    print_array_int(nums, len);
//    heapsort(nums, len);
//    print_array_int(nums, len);

    char number_1[4] = "111";
    char number_2[4] = "21";

    str_mul(number_1, number_2);

    return 0;
}