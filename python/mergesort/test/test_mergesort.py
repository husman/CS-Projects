from hamcrest import *
from mergesort.mergesort import MergeSort


class TestMergeSort():

    def test_sorts_data_in_ascending_order(self):
        unsorted_data = [4, 3, 2, 5, 6, 1]
        expected_sorted_data = [1, 2, 3, 4, 5, 6]

        mergesort = MergeSort()
        sorted_data = mergesort.sort(unsorted_data)

        print sorted_data, expected_sorted_data

        assert_that(sorted_data, all_of(expected_sorted_data))
