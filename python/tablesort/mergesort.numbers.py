import time


def mergesort(items):
    """ Implementation of mergesort """
    if len(items) > 1:

        mid = len(items) / 2        # Determine the midpoint and split
        left = items[0:mid]
        right = items[mid:]

        mergesort(left)            # Sort left list in-place
        mergesort(right)           # Sort right list in-place

        l, r = 0, 0
        for i in range(len(items)):     # Merging the left and right list

            lval = left[l] if l < len(left) else None
            rval = right[r] if r < len(right) else None

            if (lval and rval and lval < rval) or rval is None:
                items[i] = lval
                l += 1
            elif (lval and rval and lval >= rval) or lval is None:
                items[i] = rval
                r += 1
            else:
                raise Exception('Could not merge, sub arrays sizes do not match the main array')


def msort(items):
    start_time = time.time()
    mergesort(items)
    print("--- %s seconds ---" % (time.time() - start_time))

import random
data_len = 1000000
data_set = []
for i in range(data_len):
    data_set.append(random.randrange(1, data_len))

msort(data_set)

