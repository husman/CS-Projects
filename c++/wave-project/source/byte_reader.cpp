#include "include/byte_reader.h"


ByteReader::ByteReader(const char *filename) {
    file = fopen(filename, "rb");
    if(file == NULL) {
        printf("File not found or could not be opened!\n");
        exit(-1);
    }

    // Determine the endian of the current machine
    const int cpu_endian_test = 1;
    machine_endian = ((*(char*)&cpu_endian_test) == 0? 1 : 0);
}
size_t ByteReader::read_bytes_short(short *dest_data, uint32_t num_bytes) {
    return fread(dest_data, 2, num_bytes, file);
}

size_t ByteReader::read_uint8(uint8_t &uint8_val) {
    return fread(&uint8_val, 1, 1, file);
}

size_t ByteReader::read_uint16(uint16_t &uint16_val, int endian) {
    size_t read_amt = fread(&uint16_val, 2, 1, file);
    cpu_uint16(uint16_val, endian);
    return read_amt;
}

size_t ByteReader::read_uint32(uint32_t &uint32_val, int endian) {
    size_t read_amt = fread(&uint32_val, 4, 1, file);
    cpu_uint32(uint32_val, endian);
    return read_amt;
}

size_t ByteReader::read_bytes(uint8_t *dest_data, uint32_t num_bytes) {
    return fread(dest_data, 1, num_bytes, file);;
}

size_t ByteReader::skip_bytes(uint32_t num_bytes) {
    uint8_t *buf;
    buf = (uint8_t *)malloc(num_bytes);

    if(buf == NULL)
        return 0;

    return fread(buf, 1, num_bytes, file);
}

void ByteReader::cpu_uint16(uint16_t &val, int val_endian) {
    if(cpu_endian() == val_endian)
        return;

    val = (uint16_t) ((val << 8) | (val >> 8 & 0x00FF));
}

void ByteReader::cpu_uint32(uint32_t &val, int val_endian) {
    if(cpu_endian() == val_endian)
        return;

    val = val << 24
            | (val << 8  & 0x00FF0000)
            | (val >> 8  & 0x0000FF00)
            | (val >> 24 & 0x000000FF);
}
