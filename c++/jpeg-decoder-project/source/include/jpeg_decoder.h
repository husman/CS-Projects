#ifndef JPEG_DECODER_H_
#define JPEG_DECODER_H_

#include "byte_reader.h"


#define Y_dc_Hidx 0
#define Y_ac_Hidx 1
#define CbCr_dc_Hidx 2
#define CbCr_ac_Hidx 3
#define MCU_BLOCK_Y_DC 0
#define MCU_BLOCK_Y_AC 1
#define MCU_BLOCK_CB_DC 2
#define MCU_BLOCK_CB_AC 3
#define MCU_BLOCK_CR_DC 4
#define MCU_BLOCK_CR_AC 5

class JpegDecoder {
private:
    typedef enum MARKER {
        SOI = 0xFFD8, // Start of Image
        APP0 = 0xFFE0, // Application specific information
        DQT = 0xFFDB, // Define Quantization Table
        DHT = 0xFFC4, // Define Huffman Table
        SOS = 0xFFDA, // Start of Scan
        COM = 0xFFFE, // Comment
        SOF0 = 0xFFC0, // Start of Frame (Baseline DCT
        SOF2 = 0xFFC2, // Start of Frame (Progressive DCT)
        E0I = 0xFFD9, // End of Image
        EOB = 0x0000 // End of block
    } MARKER;

    typedef struct treeNode {
        struct treeNode *left;
        struct treeNode *right;
        int val;
    } treeNode;

    typedef struct huffTableProp {
        int num_nodes;
        int start_level;
        int node_shift;
    } huffTableProp;

    typedef struct jpegImage {
        unsigned short width;
        unsigned short height;
        unsigned char num_components;
        unsigned char comp_precision;
        unsigned char sampling_y;
        unsigned char sampling_cb;
        unsigned char sampling_cr;
        unsigned char dqt_y[8][8];
        unsigned char dqt_cbcr[8][8];
        struct treeNode dht_y_dc;
        struct treeNode dht_y_ac;
        struct treeNode dht_cbcr_dc;
        struct treeNode dht_cbcr_ac;
        int **mcu_y;
        int **mcu_cb;
        int **mcu_cr;
    } jpegImage;

    jpegImage jpeg_image;
    treeNode *huff_table;
    huffTableProp huffTreeInfo;

    ByteReader *reader;
    unsigned int spaces = 0;

public:
    JpegDecoder(char *filename);

    void set_zero(int *arr, int size);

    void setImageWidth(unsigned short width);

    void setImageHeight(unsigned short height);

    void setNumComponents(char num_components);

    void setCompPrecision(char comp_precision);

    void setYSampling(char sampling);

    void setCbSampling(char sampling);

    void setCrSampling(char sampling);

    void print_spaces();

    void processAPP0();

    void processCOM();

    void processDQT();

    void processSOF0();

    void processDHT();

    void processSOS();

    void addValueToNode(treeNode *node, int level, int count, int value);

    short searchHuffTable(int dht_id, int bit);

    void decode();
};

#endif