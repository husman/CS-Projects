class OneDimensionPeak:
    def __init__(self, number_list):
        self.number_list = number_list
        self.numbers_len = len(self.number_list)

    def findOne(self):
        self.get_peaks(self.number_list, self.numbers_len)

    def get_peaks(self, number_list, numbers_len):
        midpoint = int(numbers_len/2)

        if numbers_len == 1:
            return number_list[0]

        if midpoint == 0 and numbers_len > 1:
            if number_list[midpoint] > number_list[midpoint + 1]:
                return number_list[midpoint]
            else:
                return number_list[midpoint + 1]

        if number_list[midpoint - 1] < number_list[midpoint] and number_list[midpoint] > number_list[midpoint + 1]:
            return number_list[midpoint]

        if number_list[midpoint -1] <= number_list[midpoint + 1]:
            return self.get_peaks(number_list[0:midpoint -1])
        else:
            return self.get_peaks(number_list[midpoint + 1:numbers_len])
