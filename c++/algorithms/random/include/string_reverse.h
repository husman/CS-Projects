#ifndef STRING_REVERSE_H
#define STRING_REVERSE_H

void reverse_string(char *string, int len) {
    if(len < 2)
        return;

    int mid = len/2;
    len = len - 1;
    char temp;

    for(int i = 0; i < mid; ++i) {
        temp = string[i];
        *(string + i) = *(string + (len - i));
        string[len - i] = temp;
    }
}

void swap(int *arr, int left, int right) {
    int temp = arr[left];
    arr[left] = arr[right];
    arr[right] = temp;
}

int partition(int *arr, int left, int right) {
    int pivot = (right + left)/2;

    while(left != right) {
        while (arr[left] < arr[pivot])
            ++left;
        while (arr[right] > arr[pivot])
            --right;

        swap(arr, left, right);
    }

    return pivot;
}

void quicksort(int *arr, int left, int right) {
    if(left >= right)
        return;

    // get the pivot point
    int pivot = partition(arr, left, right);

    // quicksort each partition of array
    quicksort(arr, 0, pivot);
    quicksort(arr + pivot + 1, 0, pivot);
}

#endif