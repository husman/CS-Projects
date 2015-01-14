#include "include/jpeg_decoder.h"


int main(int argc, char **argv) {
    char *filename = argv[1];
    JpegDecoder jpeg_decoder(filename);
    jpeg_decoder.decode();
    return 0;
}