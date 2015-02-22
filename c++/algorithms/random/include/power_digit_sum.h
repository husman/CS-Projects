#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "string_reverse.h"



typedef struct List {
    List *next;
    char value;
} List;

char *str_add(char *a, char *b) {
    int len_a = strlen(a);
    int len_b = strlen(b);
    int len = len_a > len_b? len_a : len_b;
    int carry = 0;

    reverse_string(a, len_a);
    reverse_string(b, len_b);

    char *return_value = new char[len + 2];
    for(int i = 0; i < len; ++i) {
        char sum;

        if(i < len_a && i < len_b)
            sum = ((a[i] - '0') + (b[i] - '0') + carry);
        else if(i < len_a && i >= len_b)
            sum = ((a[i] - '0') + carry);
        if(i < len_b && i >= len_a)
            sum = ((b[i] - '0') + carry);

        if(sum > 9) {
            char sum_terms[3];
            sprintf(sum_terms, "%d", sum);
            carry = sum_terms[0] - '0';
            sum = sum_terms[1];
        } else {
            sum = sum + '0';
            carry = 0;
        }

        return_value[len - i - 1] = sum;
    }

    if(carry > 0) {
        return_value[len] = carry;
        return_value[len + 1] = '\0';
    } else {
        return_value[len] = '\0';
    }

    printf("the sum is: %s\n", return_value);

    return return_value;
}

char *str_mul(char *a, char *b) {
    int len_a = strlen(a);
    int len_b = strlen(b);
    int upper_len = len_a > len_b? len_a : len_b;
    int lower_len = len_a < len_b? len_a : len_b;
    int carry = 0;

    reverse_string(a, len_a);
    reverse_string(b, len_b);

    char *add_value = new char[upper_len + 2];
    char *return_value = new char[upper_len + 2];
    return_value[0] = '0';
    return_value[1] = '\0';

    for(int z = 0; z < lower_len; ++z) {
        for(int i = 0; i < upper_len; ++i) {
            int mul;
            if(len_a > len_b) {
                mul = (a[i] - '0') * (b[z] - '0') + carry;
                printf("len_a: multiply a=%c b=%c\n", a[i], b[z]);
            } else {
                mul = (a[z] - '0') * (b[i] - '0') + carry;
                printf("len_b: multiply a=%c b=%c\n", a[z], b[i]);
            }

            printf("mul-aaa = %d\n", mul);


            if(mul > 10) {
                char *mul_terms;
                sprintf(mul_terms, "%d", mul);
                carry = mul_terms[0] - '0';
                mul = mul_terms[1];
            } else {
                mul = mul + '0';
                carry = 0;
            }

            printf("mul = %c\n", mul);
            add_value[upper_len - i - 1] = mul;
        }
        return_value = str_add(return_value, add_value);
    }

    printf("mul===: %s\n", return_value);

    return return_value;
}
