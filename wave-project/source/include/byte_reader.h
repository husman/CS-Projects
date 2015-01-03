#ifndef BYTE_READER_H_
#define BYTE_READER_H_

// We include our standard input/output library. I like 'printf'
// and of course for our file input/output data structures/algorithms
#include <stdio.h>
#include <stdlib.h>

#include "globals.h"


#define ARCH_LITTLE_ENDIAN   0
#define ARCH_BIG_ENDIAN      1

class ByteReader {
private:
    FILE *file;

    int machine_endian;

    void cpu_uint16(uint16_t &val, int val_endian);

    void cpu_uint32(uint32_t &val, int val_endian);

public:
    ByteReader(const char *filename);

    int cpu_endian() { return machine_endian; }

    size_t read_bytes_short(short *dest_data, uint32_t num_bytes);

    size_t read_uint8(uint8_t &uint8_val);

    size_t read_uint16(uint16_t &uint16_val, int endian);

    size_t read_uint32(uint32_t &uint32_val, int endian);

    size_t read_bytes(uint8_t *dest_data, uint32_t num_bytes);

    size_t skip_bytes(uint32_t num_bytes);
};

#endif