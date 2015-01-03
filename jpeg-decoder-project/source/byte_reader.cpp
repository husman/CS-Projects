#include "include/byte_reader.h"


ByteReader::ByteReader(char *filename) {
    file = fopen(filename, "rb");
    if(!file) {
        printf("Could not open inpute file: %s\n", filename);
        exit(-1);
    }
}

int ByteReader::read_short(unsigned short &short_val) {
    unsigned char short_buf[2];
    int read_amt = 0;
    short_val = 0;
    if ((read_amt = fread(short_buf, sizeof(short_buf), 1, file)) > 0) {
        short_val = (short_val & 0) | (short_buf[0] << 8 ) | short_buf[1];
    }
    return read_amt;
}

size_t ByteReader::read_bytes(unsigned char *bytes_val, int length) {
    return fread(bytes_val, 1, length, file);
}

size_t ByteReader::read_byte(unsigned char &byte_val) {
    return fread(&byte_val, 1, 1, file);
}

int ByteReader::unread_byte(unsigned char last_char) {
    unsigned char buf;
    return ungetc(last_char, file);
}

int ByteReader::read_bits(short num_bits) {
    static unsigned char buf, last_buf;
    static int remainder = 0, store_last_buf = 0;
    int nbits_val = 0, dummy = 0;

    if (remainder == 0) {
        if (store_last_buf == 1) {
            last_buf = buf;
        } else {
            store_last_buf = 1;
        }
        if (read_byte(buf) == 0) {
            return -1;
        }
        printf("\ncurrent byte: %02x last byte: %02x\n", buf, last_buf);
        if (last_buf == 0xFF && buf == 0x00) {
            // skip this byte because it's a stuff byte
            if (read_byte(buf) == 0)
                return -1;
            printf("STUFF BYTE - SKIPPING 00, CURRENT = %02x\n", buf);
        }
        remainder = 8;
    }
    remainder--;
    if (num_bits == 0) {
        return buf >> remainder & 1;
    } else {
        int sign = 1;
        nbits_val = nbits_val | (buf >> remainder & 1); // upper bit
        if (nbits_val == 0)
            sign = -1;
        num_bits--;
        for (dummy = 0; dummy < num_bits; ++dummy) {
            nbits_val = nbits_val << 1 | read_bits();
        }
        return sign * nbits_val;
    }
}