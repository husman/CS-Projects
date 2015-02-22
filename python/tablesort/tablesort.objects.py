import time


data_len = 5

def normalize(value, min, max):
    index = (value - min)/(max - min)


def tablesort(items):
    start_time = time.time()
    table = [None for x in range(data_len)]
    min_value = None
    max_value = None
    for item in items:
        if not min_value:
            min_value = item.__hash__() % data_len
        if not max_value:
            max_value = item.__hash__() % data_len

        if min_value > item.__hash__() % data_len:
            min_value = item.__hash__() % data_len

        if max_value < item.__hash__() % data_len:
            max_value = item.__hash__() % data_len

        if not isinstance(table[item.__hash__() % data_len], list):
            table[item.__hash__() % data_len] = [item]
        else:
            table[item.__hash__() % data_len].append(item)

    result = []
    print 'table len', table
    while min_value <= max_value:
        items = table[min_value]
        min_value = min_value + 1
        if isinstance(items, list) and len(items) > 0:
            for item in items:
                result.append(item)
                print item

    print("--- %s seconds ---" % (time.time() - start_time))


class Circle():
    def __init__(self, radius, center=None):
        self.radius = radius
        self.center = center

    def __hash__(self):
        return self.radius * (self.center[0] + self.center[1])

    def __str__(self):
        return 'Radius: {radius} Center: ({x}, {y}) Magnitude: {magnitude}'.format(
            radius=self.radius,
            x=self.center[0],
            y=self.center[1],
            magnitude=self.__hash__(),
        )


import random
data_set = []
for i in range(data_len):
    radius = random.randrange(1, data_len)
    x = random.randrange(1, 5)
    y = random.randrange(1, 5)
    data_set.append(Circle(radius, (x, y)))

tablesort(data_set)