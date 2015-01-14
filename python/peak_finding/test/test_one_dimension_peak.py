from peak_finding.one_dimension_peak import OneDimensionPeak
from hamcrest import *

class TestOneDimensionPeak:
    def setUp(self):
        pass

    def test_can_find_a_peak_in_one_dimension_on_odd_size_set(self):
        number_list = [3, 6, 3, 2, 9, 6, 1]
        possible_peaks = [6, 9]

        one_dimension_peak = OneDimensionPeak(number_list)
        found_peak = one_dimension_peak.findOne()

        assert_that(possible_peaks, contains(found_peak))
