import time


def tablesort(items):
    start_time = time.time()
    table = {}
    for item in items:
        if not isinstance(table.get(item), list):
            table[item] = [item]
        else:
            table[item].append(item)


    result = []
    for items in table.itervalues():
        for item in items:
            result.append(item)

    print("--- %s seconds ---" % (time.time() - start_time))


import random
data_len = 1000000
data_set = []
for i in range(0, data_len):
    data_set.append(random.randrange(1, 5))

tablesort(data_set)