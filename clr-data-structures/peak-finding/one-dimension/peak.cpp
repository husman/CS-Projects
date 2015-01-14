#include "include/peak.h"


void Peak::setData(int *number_list, int size) {
    if(number_list == NULL || size == 0)
        throw std::underflow_error("number_lit passed as argument has no elements.");

    data = number_list;
    this->size = size;
}

int Peak::findOne(int index) {
    if(index == 0) {
        return data[index];
    }
    else if(index == size)
        return data[index -1];

    int left_value = data[index - 1];
    int middle_value = data[index];
    int right_value = data[index + 1];

    if(left_value <= middle_value && middle_value >= right_value)
        return middle_value;
    else if(left_value >= right_value)
        return findOne(index/2);
    else if(left_value < right_value && index == 1)
        return right_value;
    else
        return findOne(index + index/2);
}

int Peak::findOne() {
    return findOne(size/2);
}

int *Peak::find() {
    return 0;
}

int Peak::count() {
    return 0;
}