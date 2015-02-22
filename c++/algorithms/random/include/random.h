#include <iostream>

void swap(int *arr, int index1, int index2) {
    int temp = arr[index1];
    arr[index1] = arr[index2];
    arr[index2] = temp;
}

void shift(int *arr, int root_index, int end_index) {
    int left_child_index = root_index * 2 + 1;

    // while there is a left child of the current root
    // heapify the root against its children
    while(left_child_index < end_index) {
        int swap_index = left_child_index;
        int right_child_index = swap_index + 1;

        if(right_child_index < end_index && arr[left_child_index] < arr[right_child_index])
            swap_index = right_child_index;

        if(arr[root_index] < arr[swap_index]) {
            swap(arr, root_index, swap_index);
            root_index = swap_index;
        } else
            break;

        left_child_index = root_index * 2 + 1;
    }
}

void heapsort(int *arr, int count) {
    // start at the last child of the array
    int parent_of_last_child_index = count / 2 - 1;
    int end_index = count - 1;

    // 1 heapify the root of the array so that the maximum element is in the root
    while(parent_of_last_child_index >= 0) {
        shift(arr, parent_of_last_child_index, count);
        --parent_of_last_child_index;
    }

    // heapify from the root downwards will make sure everything is in the right place
    while(end_index > 0) {
        swap(arr, 0, end_index);
        shift(arr, 0, end_index);
        --end_index;
    }
}