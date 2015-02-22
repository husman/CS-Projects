import time


def get_peak(items, start, end):
    data_len = end - start
    midpoint = int((start + end)/2)

    if data_len == 1:
        return start

    if data_len == 2:
        if items[start] > items[end - 1]:
            return start
        return end - 1

    left_item = items[midpoint - 1]
    middle_item = items[midpoint]
    right_item = items[midpoint + 1]

    if middle_item >= left_item and middle_item >= right_item:
        return midpoint
    elif right_item >= left_item:
        return get_peak(items, midpoint + 1, end)

    return get_peak(items, start, midpoint)


import random
data_len = 5
data_set = []
for i in range(data_len):
    data_set.append(random.randrange(1, data_len+100))

print data_set
peak = get_peak(data_set, 0, data_len)
print 'peak:', peak

