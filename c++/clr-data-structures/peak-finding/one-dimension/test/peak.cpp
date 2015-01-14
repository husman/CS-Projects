#include <gtest/gtest.h>

#include "../include/peak.h"

TEST(Peak, can_find_a_valid_peak_at_edges) {
    Peak peak;
    int number_list_1[] = { 1, 2, 3, 4, 5, 6 },
        number_list_2[] = { 7, 5, 4, 3, 2, 1 };

    peak.setData(number_list_1, 6);
    ASSERT_EQ(peak.findOne(), 6);

    peak.setData(number_list_2, 6);
    ASSERT_EQ(peak.findOne(), 7);
};

TEST(Peak, can_find_valid_peak_in_random_set) {
    Peak peak;
    int number_list_1[] = { 2, 1, 3, 2, 5, 0 },
        number_list_2[] = { 2, 2, 3, 1, 3, 20 },
        number_list_3[] = { 20, 34, 8, 9, 5, 33 };

    peak.setData(number_list_1, 6);
    ASSERT_EQ(peak.findOne(), 5);

    peak.setData(number_list_2, 6);
    ASSERT_EQ(peak.findOne(), 3);

    peak.setData(number_list_3, 6);
    ASSERT_EQ(peak.findOne(), 9);
};

bool inArray(int value, int *array, int size) {
    for(int i=0; i<size; ++i) {
        if(value == array[i])
            return true;
    }

    return false;
}

TEST(Peak, can_find_all_peaks) {
    Peak peak;
    int number_list[] = { 4, 8, 5, 4, 3, 10, 15, 12, 2 };
    int expect_peaks[] = { 8, 15 };
    int *found_peaks;

    peak.setData(number_list, 9);
    found_peaks = peak.find();

    if(found_peaks == NULL)
        FAIL();

    ASSERT_TRUE(inArray(expect_peaks[0], found_peaks, 2));
    ASSERT_TRUE(inArray(expect_peaks[1], found_peaks, 2));
};
