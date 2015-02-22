class MergeSort(object):
    def sort(self, data):
        length = len(data)

        if length > 1:
            midpoint = length/2
            left_piece = data[0:midpoint]
            right_piece = data[midpoint:length]

            left = self.sort(left_piece)
            right = self.sort(right_piece)
            return self.merge(left, right)

        return data

    def merge(self, left_piece, right_piece):
        i, j = 0, 0
        left_piece_len = len(left_piece)
        right_piece_len = len(right_piece)
        data = []

        while i < left_piece_len and j < right_piece_len:
            if left_piece[i] < right_piece[j]:
                data.append(left_piece[i])
                i += 1
            else:
                data.append(right_piece[j])
                j += 1

        while i < left_piece_len:
            data.append(left_piece[i])
            i += 1

        while j < right_piece_len:
            data.append(right_piece[j])
            j += 1

        return data