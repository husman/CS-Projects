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


class Circle():
    def __init__(self, radius, center=None):
        self.radius = radius
        self.center = center

    def __hash__(self):
        return self.radius * (self.center[0] + self.center[1])

    def __cmp__(self, other):
        if self.__hash__() < other.__hash__():
            return -1

        if self.__hash__() > other.__hash__():
            return 1

        return 0

    def __eq__(self, other):
        return self.__hash__() == other.__hash()

    def __str__(self):
        return 'Radius: {radius} Center: ({x}, {y}) Magnitude: {magnitude}'.format(
            radius=self.radius,
            x=self.center[0],
            y=self.center[1],
            magnitude=self.__hash__(),
        )

import random
data_len = 1000000
data_set = []
for i in range(data_len):
    radius = random.randrange(1, data_len)
    x = random.randrange(1, 5)
    y = random.randrange(1, 5)
    data_set.append(Circle(radius, (x, y)))

msort(data_set)

