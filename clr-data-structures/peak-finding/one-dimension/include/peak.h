#include <cstdio>
#include <cstdlib>
#include <stdexcept>

class Peak {
private:
    int *data;
    int size;

    int findOne(int index);

public:
    void setData(int *number_list, int size);
    int *find();
    int findOne();
    int count();
};