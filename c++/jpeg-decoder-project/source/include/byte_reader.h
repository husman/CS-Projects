#ifndef BYTE_READER_H_
#define BYTE_READER_H_

#include "globals.h"
#include <stdio.h>
#include <stdlib.h>


class ByteReader {
private:
    FILE *file;

public:
    ByteReader(char *filename);

    int read_short(unsigned short &short_val);

    size_t read_bytes(unsigned char *bytes_val, int length);

    size_t read_byte(unsigned char &byte_val);

    int unread_byte(unsigned char last_char);

    int read_bits(short num_bits = 0);

};

#endif
