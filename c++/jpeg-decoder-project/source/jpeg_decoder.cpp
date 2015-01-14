#include "include/jpeg_decoder.h"


JpegDecoder::JpegDecoder(char *filename) {
    reader = new ByteReader(filename);
}
void JpegDecoder::set_zero(int *arr, int size) {
    int i;
    for (i = 0; i < size; i++)
        arr[i] = 0;
}

void JpegDecoder::setImageWidth(unsigned short width) {
    jpeg_image.width = width;
}

void JpegDecoder::setImageHeight(unsigned short height) {
    jpeg_image.height = height;
}

void JpegDecoder::setNumComponents(char num_components) {
    jpeg_image.num_components = num_components;
}

void JpegDecoder::setCompPrecision(char comp_precision) {
    jpeg_image.comp_precision = comp_precision;
}

void JpegDecoder::setYSampling(char sampling) {
    jpeg_image.sampling_y = sampling;
}

void JpegDecoder::setCbSampling(char sampling) {
    jpeg_image.sampling_cb = sampling;
}

void JpegDecoder::setCrSampling(char sampling) {
    jpeg_image.sampling_cr = sampling;
}

void JpegDecoder::print_spaces() {
    for (int i = 0; i < spaces; i++) {
        printf(" ");
    }
}

void JpegDecoder::processAPP0() {
    uint8_t file_format[5];
    unsigned short len;
    unsigned char major_version;
    unsigned char minor_version;
    uint8_t *remaining_bytes;

    reader->read_short(len);
    len = len - 2;

    reader->read_bytes(file_format, 5);
    reader->read_byte(major_version);
    reader->read_byte(minor_version);
    len = len - 7;

    remaining_bytes = (uint8_t *) malloc(sizeof(uint8_t) * len);
    if (reader->read_bytes(remaining_bytes, len) == len) {
        printf("Skipped %d bytes\n", len);
    }

    spaces += 5;
    print_spaces();
    printf("File Format: %s %d.%d\n", file_format, major_version, minor_version);
    spaces -= 5;
}

void JpegDecoder::processCOM() {
    unsigned short len;
    uint8_t *data;

    reader->read_short(len);
    len = len - 2;
    data = (uint8_t *) malloc(len);
    if (reader->read_bytes(data, len) == len) {
        data[len] = '\0';

        spaces += 5;
        print_spaces();
        printf("%s\n", data);
        spaces -= 5;
    }
}

void JpegDecoder::processDQT() {
    unsigned short len;
    unsigned char dqt_id;
    int i = 0, x = 0;
    int k = 0, j, i1, j1;
    unsigned char tmp_dqt_cbcr[8][8], tmp_dqt_y[8][8];

    int zigzag[] = {
            0, 1, 8, 16, 9, 2, 3, 10,
            17, 24, 32, 25, 18, 11, 4, 5,
            12, 19, 26, 33, 40, 48, 41, 34,
            27, 20, 13, 6, 7, 14, 21, 28,
            35, 42, 49, 56, 57, 50, 43, 36,
            29, 22, 15, 23, 30, 37, 44, 51,
            58, 59, 52, 45, 38, 31, 39, 46,
            53, 60, 61, 54, 47, 55, 62, 63
    };

    spaces = 5;
    print_spaces();

    reader->read_short(len);
    len = len - 2;

    reader->read_byte(dqt_id);

    if (dqt_id == 0) {
        for (x = 0; x < 8; x++) {
            for (i = 0; i < 8; i++) {
                reader->read_byte(tmp_dqt_y[x][i]);
            }
        }

        // Let's re-order the Luminance DQT
        for (int i = 0; i < 8; i++) {
            for (j = 0; j < 8; j++) {
                i1 = zigzag[k] / 8;
                j1 = zigzag[k] % 8;
                jpeg_image.dqt_y[i1][j1] = tmp_dqt_y[i][j];
                k++;
            }
        }

        printf("Luminance DQT:\n");
        for (int x = 0; x < 8; x++) {
            print_spaces();
            for (i = 0; i < 8; i++) {
                printf("%4d", jpeg_image.dqt_y[x][i]);
            }
            printf("\n");
        }

        reader->read_byte(dqt_id);
        if (dqt_id != 0xFF) {
            for (x = 0; x < 8; x++) {
                for (i = 0; i < 8; i++) {
                    reader->read_byte(tmp_dqt_cbcr[x][i]);
                }
            }
            // Let's re-order the Chromance DQT
            k = 0;
            for (int i = 0; i < 8; i++) {
                for (j = 0; j < 8; j++) {
                    i1 = zigzag[k] / 8;
                    j1 = zigzag[k] % 8;
                    jpeg_image.dqt_cbcr[i1][j1] = tmp_dqt_cbcr[i][j];
                    k++;
                }
            }

            printf("\n");
            print_spaces();
            printf("Chromance DQT:\n");

            for (int x = 0; x < 8; x++) {
                print_spaces();
                for (i = 0; i < 8; i++) {
                    printf("%4d", jpeg_image.dqt_cbcr[x][i]);
                }
                printf("\n");
            }
        } else {
            reader->unread_byte(dqt_id);
        }
    } else {
        for (x = 0; x < 8; x++) {
            for (i = 0; i < 8; i++) {
                reader->read_byte(tmp_dqt_cbcr[x][i]);
            }
        }

        // Let's re-order the Chromance DQT
        k = 0;
        for (int i = 0; i < 8; i++) {
            for (j = 0; j < 8; j++) {
                i1 = zigzag[k] / 8;
                j1 = zigzag[k] % 8;
                jpeg_image.dqt_cbcr[i1][j1] = tmp_dqt_cbcr[i][j];
                k++;
            }
        }

        printf("Chromance DQT:\n");
        for (int x = 0; x < 8; x++) {
            print_spaces();
            for (i = 0; i < 8; i++) {
                printf("%4d", jpeg_image.dqt_cbcr[x][i]);
            }
            printf("\n");
        }

        reader->read_byte(dqt_id);
        if (dqt_id != 0xFF) {
            for (x = 0; x < 8; x++) {
                for (i = 0; i < 8; i++) {
                    reader->read_byte(tmp_dqt_y[x][i]);
                }
            }

            // Let's re-order the Luminance DQT
            for (int i = 0; i < 8; i++) {
                for (j = 0; j < 8; j++) {
                    i1 = zigzag[k] / 8;
                    j1 = zigzag[k] % 8;
                    jpeg_image.dqt_y[i1][j1] = tmp_dqt_y[i][j];
                    k++;
                }
            }

            printf("\n");
            printf("Luminance DQT:\n");

            for (int x = 0; x < 8; x++) {
                print_spaces();
                for (i = 0; i < 8; i++) {
                    printf("%4d", jpeg_image.dqt_y[x][i]);
                }
                printf("\n");
            }
        } else {
            reader->unread_byte(dqt_id);
        }
    }

    spaces -= 5;
}

void JpegDecoder::processSOF0() {
    unsigned short len;

    reader->read_short(len);
    reader->read_byte(jpeg_image.comp_precision);
    reader->read_short(jpeg_image.width);
    reader->read_short(jpeg_image.height);

    spaces += 5;
    print_spaces();
    printf("Precision per component: %d | Dimension: %dx%d\n", jpeg_image.comp_precision, jpeg_image.width, jpeg_image.height);
    spaces -= 5;
}

void JpegDecoder::processDHT() {
    unsigned short len;
    unsigned char dht_id = 0;
    unsigned char huff_len_count[4][16];
    int total_len = 0, n = 0, i = 0, z = 0, dht_loop = 0;
    unsigned char **huff_vals = (unsigned char **) malloc(4 * sizeof(unsigned char *));

    spaces += 5;
    reader->read_short(len);
    reader->read_byte(dht_id);
    for (dht_loop = 0; dht_loop < 4; dht_loop++) {
        total_len = 0;
        switch (dht_id) {
            case 0x00: // Class = 0 (DC), Id = 0 (Luminance)
                n = Y_dc_Hidx;
                huff_table = &jpeg_image.dht_y_dc;
                break;
            case 0x01: // Class = 1 (DC), Id = 0 (Chrominance)
                n = Y_ac_Hidx;
                huff_table = &jpeg_image.dht_cbcr_dc;
                break;
            case 0x10: // Class = 0 (AC), Id = 1 (Luminance)
                n = CbCr_dc_Hidx;
                huff_table = &jpeg_image.dht_y_ac;
                break;
            case 0x11: // Class = 1 (AC), Id = 1 (Chrominance)
                n = CbCr_ac_Hidx;
                huff_table = &jpeg_image.dht_cbcr_ac;
                break;
        }
        huff_table->left = NULL;
        huff_table->right = NULL;
        huff_table->val = -1;;
        huffTreeInfo.num_nodes = 0;
        huffTreeInfo.node_shift = 0;
        huffTreeInfo.start_level = -1;
        int set_start_level = 1;
        int tmp_level_node_num = 0;
        printf("\n\n n = %d | id = %02x\n\n", n, dht_id);
        for (i = 1; i <= 16; ++i) {
            reader->read_byte(huff_len_count[n][i - 1]);
            total_len += huff_len_count[n][i - 1];
            if (set_start_level == 1) {
                if (huff_len_count[n][i - 1] > 0) {
                    huffTreeInfo.start_level = i;
                    set_start_level = 0;
                }
            }
        }
        huff_vals[n] = (unsigned char *) malloc(total_len * sizeof(unsigned char));
        for (int i = 1; i <= 16; ++i) {
            print_spaces();
            printf("Codes of length %02d %s (%03d total):", i, (i > 1 ? "bits" : "bit "), huff_len_count[n][i - 1]);
            if (huff_len_count[n][i - 1] > 0) {
                if (huffTreeInfo.start_level < i) {
                    huffTreeInfo.node_shift = huffTreeInfo.node_shift + (tmp_level_node_num << 1);
                }
                tmp_level_node_num = 0;
                for (z = 0; z < huff_len_count[n][i - 1]; ++z) {
                    reader->read_byte(huff_vals[n][i - 1]);
                    addValueToNode(huff_table, i, z, huff_vals[n][i - 1]);
                    huffTreeInfo.num_nodes++;
                    tmp_level_node_num++;
                    printf(" %02x", huff_vals[n][i - 1]);
                }
            }
            printf("\n");
        }
        // Let's read the id for only the first two loops.
        if (dht_loop < 3) {
            reader->read_byte(dht_id);
        }
        print_spaces();
        printf("Total number of codes: %03d\n\n", total_len);
    }
    spaces -= 5;
}

void JpegDecoder::processSOS() {
    unsigned short hdr_len;
    unsigned char *hdr_data;
    int dht_id, bit;
    short val_len;

    reader->read_short(hdr_len);
    hdr_len -= 2;
    hdr_data = (unsigned char *) malloc(hdr_len * sizeof(unsigned char));
    dht_id = Y_dc_Hidx;
    // Let's skip the header info (size = hdr_len)
    if (reader->read_bytes(hdr_data, hdr_len) == hdr_len) {
        printf("Skipped %d bytes\n", hdr_len);
        /* Let's allocate memory for the ac/dc/mcu counters and macroblocks */
        // dc_count/ac_count are used to keep track of how many dc or ac
        // componets we have added to the current macroblock.
        // mcu_count is used to keep track of the macroblock number we are in.
        // mcu_type is used to keep track of the macroblock type we are in.
        // dummy is used for as the iterator for the loops.
        // done_decoding is used to signify whether or not
        // we are done decoding the macroblocks
        int dc_count, ac_count, mcu_count, mcu_type, dummy, done_decoding;
        int mcu_size, ac_run, ac_size, ac_code;
        dc_count = 0;
        ac_count = 0;
        mcu_count = 0;
        ac_run = 0;
        ac_size = 0;
        ac_code = 0;
        dummy = 0;
        done_decoding = 0;
        mcu_type = MCU_BLOCK_Y_DC;
        unsigned char *z3;
        mcu_size = ceil((double) jpeg_image.width / 8 * jpeg_image.height / 8);
        jpeg_image.mcu_y = (int **) malloc(mcu_size * sizeof(int *));
        jpeg_image.mcu_cb = (int **) malloc(mcu_size * sizeof(int *));
        jpeg_image.mcu_cr = (int **) malloc(mcu_size * sizeof(int *));
        // initialize each macroblock
        for (dummy = 0; dummy < mcu_size; dummy++) {
            jpeg_image.mcu_y[dummy] = (int *) malloc(64 * sizeof(int));
            jpeg_image.mcu_cb[dummy] = (int *) malloc(64 * sizeof(int));
            jpeg_image.mcu_cr[dummy] = (int *) malloc(64 * sizeof(int));
            set_zero(jpeg_image.mcu_y[dummy], 64);
            set_zero(jpeg_image.mcu_cb[dummy], 64);
            set_zero(jpeg_image.mcu_cr[dummy], 64);
        }
        // Let's begin processing the compressed data
        while (mcu_count < mcu_size) {
            bit = reader->read_bits();
            if (bit == -1) {
                printf("[ERROR]: Jpeg image data is corrupt. [REASON]: Data prematurely terminated!\n");
                return;
            }
            val_len = searchHuffTable(dht_id, bit);
            // check for (EOB) End of block
            if (val_len == EOB) {
                // Move onto next MCU
                switch (mcu_type) {
                    // (Y) Lumninance DC/Lossless
                    case MCU_BLOCK_Y_DC:
                        mcu_type = MCU_BLOCK_Y_AC;
                        dht_id = Y_ac_Hidx;
                        ++dc_count;
                        break;
                        // (Y) Lumninance AC/Lossy
                    case MCU_BLOCK_Y_AC:
                        mcu_type = MCU_BLOCK_CB_DC;
                        dht_id = CbCr_dc_Hidx;
                        // reset the ac/dc counters for next mcu
                        ac_count = 0;
                        dc_count = 0;
                        break;
                        // (Cb) Chrominance blue DC/Lossless
                    case MCU_BLOCK_CB_DC:
                        mcu_type = MCU_BLOCK_CB_AC;
                        dht_id = CbCr_ac_Hidx;
                        ++dc_count;
                        break;
                        // (Cb) Chrominance blue AC/Lossy
                    case MCU_BLOCK_CB_AC:
                        mcu_type = MCU_BLOCK_CR_DC;
                        dht_id = CbCr_dc_Hidx;
                        // reset the ac/dc counters for next mcu
                        ac_count = 0;
                        dc_count = 0;
                        break;
                        // (Cr) Chrominance red DC/Lossless
                    case MCU_BLOCK_CR_DC:
                        mcu_type = MCU_BLOCK_CR_AC;
                        dht_id = CbCr_ac_Hidx;
                        ++dc_count;
                        break;
                        // (Cr) Chrominance red AC/Lossy
                    case MCU_BLOCK_CR_AC:
                        mcu_type = MCU_BLOCK_Y_DC;
                        dht_id = Y_dc_Hidx;
                        // reset the ac/dc counters for next mcu
                        ac_count = 0;
                        dc_count = 0;
                        // move onto the next set of macroblocks
                        mcu_count++;
                        break;
                }
            } else if (val_len > 0) {
                printf("\nReading next %02x bits as value...\n", val_len);
                // determine which macroblock type we are in
                switch (mcu_type) {
                    // (Y) Lumninance DC/Lossless
                    case MCU_BLOCK_Y_DC:
                        jpeg_image.mcu_y[mcu_count][ac_count + dc_count] = reader->read_bits(val_len);
                        printf("Setting mcu_y dc value: %02x\n", jpeg_image.mcu_y[mcu_count][ac_count + dc_count]);
                        dc_count++;
                        // move onto the AC values
                        mcu_type = MCU_BLOCK_Y_AC;
                        dht_id = Y_ac_Hidx;
                        break;
                        // (Y) Lumninance AC/Lossy
                    case MCU_BLOCK_Y_AC:
                        //ac_code = read_bits(val_len);
                        ac_run = val_len >> 4;
                        ac_size = val_len & 0x0F;
                        printf("AC_CODE = %02x\n", val_len);
                        printf("AC_RUN = %02x\n", ac_run);
                        printf("AC_SIZE = %02x\n", ac_size);
                        printf("skipping next %d ac entries\n", ac_run);
                        printf("current[0] ac_count = %d\n", ac_count);
                        ac_count += ac_run;
                        printf("current[1] ac_count = %d\n", ac_count);
                        jpeg_image.mcu_y[mcu_count][ac_count + dc_count] = reader->read_bits(ac_size);
                        printf("Setting mcu_y ac value: %02x\n", jpeg_image.mcu_y[mcu_count][ac_count + dc_count]);
                        ac_count++;
                        // if 63 AC values, then move onto next block
                        if (ac_count >= 63) {
                            ac_count = 0;
                            dc_count = 0;
                            mcu_type = MCU_BLOCK_CB_DC;
                            dht_id = CbCr_dc_Hidx;
                        }
                        break;
                        // (Cb) Chrominance blue DC/Lossless
                    case MCU_BLOCK_CB_DC:
                        jpeg_image.mcu_cb[mcu_count][ac_count + dc_count] = reader->read_bits(val_len);
                        printf("Setting mcu_cb dc value: %02x\n", jpeg_image.mcu_cb[mcu_count][ac_count + dc_count]);
                        dc_count++;
                        // move onto the AC values
                        mcu_type = MCU_BLOCK_CB_AC;
                        dht_id = CbCr_ac_Hidx;
                        break;
                        // (Cb) Chrominance blue AC/Lossy
                    case MCU_BLOCK_CB_AC:
                        //ac_code = read_bits(val_len);
                        ac_run = val_len >> 4;
                        ac_size = val_len & 0x0F;
                        printf("AC_CODE = %02x\n", val_len);
                        printf("AC_RUN = %02x\n", ac_run);
                        printf("AC_SIZE = %02x\n", ac_size);
                        printf("skipping next %d ac entries\n", ac_run);
                        printf("current[0] ac_count = %d\n", ac_count);
                        ac_count += ac_run;
                        printf("current[1] ac_count = %d\n", ac_count);
                        jpeg_image.mcu_cb[mcu_count][ac_count + dc_count] = reader->read_bits(ac_size);
                        printf("Setting mcu_cb ac value: %02x\n", jpeg_image.mcu_cb[mcu_count][ac_count + dc_count]);
                        ac_count++;
                        // if 63 AC values, then move onto next block
                        if (ac_count >= 63) {
                            ac_count = 0;
                            dc_count = 0;
                            mcu_type = MCU_BLOCK_CR_DC;
                            dht_id = CbCr_dc_Hidx;
                        }
                        break;
                        // (Cr) Chrominance red DC/Lossless
                    case MCU_BLOCK_CR_DC:
                        jpeg_image.mcu_cr[mcu_count][ac_count + dc_count] = reader->read_bits(val_len);
                        printf("Setting mcu_cr dc value: %02x\n", jpeg_image.mcu_cr[mcu_count][ac_count + dc_count]);
                        dc_count++;
                        // move onto AC values
                        mcu_type = MCU_BLOCK_CR_AC;
                        dht_id = CbCr_ac_Hidx;
                        break;
                        // (Cr) Chrominance red AC/Lossy
                    case MCU_BLOCK_CR_AC:
                        //ac_code = read_bits(val_len);
                        ac_run = val_len >> 4;
                        ac_size = val_len & 0x0F;
                        printf("AC_CODE = %02x\n", val_len);
                        printf("AC_RUN = %02x\n", ac_run);
                        printf("AC_SIZE = %02x\n", ac_size);
                        printf("skipping next %d ac entries\n", ac_run);
                        printf("current[0] ac_count = %d\n", ac_count);
                        ac_count += ac_run;
                        printf("current[1] ac_count = %d\n", ac_count);
                        jpeg_image.mcu_cr[mcu_count][ac_count + dc_count] = reader->read_bits(ac_size);
                        printf("Setting mcu_cr ac value: %02x\n", jpeg_image.mcu_cr[mcu_count][ac_count + dc_count]);
                        ac_count++;
                        // if 63 AC values, then move onto next block
                        if (ac_count >= 63) {
                            ac_count = 0;
                            dc_count = 0;
                            mcu_type = MCU_BLOCK_Y_DC;
                            dht_id = Y_dc_Hidx;
                        }
                        break;
                }
            }
        }
        // We are done decoding the huffman values. Let's output the DCT // macroblocks
        int dummy2, dummy3, **mcu_block;
        char component_label[3];
        printf("\nBASELINE DCT MCU/Macroblocks:\n\n");
        for (dummy = 0; dummy < mcu_size; ++dummy) {
            printf("DCT MCU/Macroblocks #%d:\n", dummy + 1);
            for (dummy2 = 0; dummy2 < 3; ++dummy2) {
                switch (dummy2) {
                    case 0:
                        mcu_block = jpeg_image.mcu_y;
                        component_label[0] = 'Y';
                        component_label[1] = ' ';
                        component_label[2] = '\0';
                        break;
                    case 1:
                        mcu_block = jpeg_image.mcu_cb;
                        component_label[0] = 'C';
                        component_label[1] = 'r';
                        component_label[2] = '\0';
                        break;
                    case 2:
                        mcu_block = jpeg_image.mcu_cr;
                        component_label[0] = 'C';
                        component_label[1] = 'b';
                        component_label[2] = '\0';
                        break;
                }
                for (dummy3 = 0; dummy3 < 64; ++dummy3) {
                    printf("%4d ", mcu_block[dummy][dummy3]);
                    if ((dummy3 + 1) % 8 == 0) {
                        printf("\n");
                        if ((dummy3 + 1) != 32) {
                        }
                    }
                    if ((dummy3 + 1) == 32) {
                        printf("%s = ", component_label);
                    }
                }
                printf("\n");
            }
            printf("\n\n");
        }
    }
}

void JpegDecoder::addValueToNode(treeNode *node, int level, int count, int value) {
    int i = level - 1;
    if (i >= 0) {
        if (((huffTreeInfo.node_shift + count) >> i & 1) == 0) {
            if (node->left == NULL) {
                node->left = (treeNode *) malloc(sizeof(treeNode));
                node->left->left = NULL;
                node->left->right = NULL;
                node->left->val = -1;
            }
            addValueToNode(node->left, i, count, value);
        } else {
            if (node->right == NULL) {
                node->right = (treeNode *) malloc(sizeof(treeNode));
                node->right->left = NULL;
                node->right->right = NULL;
                node->right->val = -1;
            }
            addValueToNode(node->right, i, count, value);
        }
    } else {
        node->val = value;
    }
}

short JpegDecoder::searchHuffTable(int dht_id, int bit) {
    static treeNode *last_node;
    treeNode *active_table;
    // set the huffman table to search through
    if (last_node == NULL) {
        switch (dht_id) {
            case Y_dc_Hidx:
                printf("\nIn table = Y_dc_Hidx\n");
                active_table = &jpeg_image.dht_y_dc;
                break;
            case Y_ac_Hidx:
                printf("\nIn table = dht_y_ac\n");
                active_table = &jpeg_image.dht_y_ac;
                break;
            case CbCr_dc_Hidx:
                printf("\nIn table = dht_cbcr_dc\n");
                active_table = &jpeg_image.dht_cbcr_dc;
                break;
            case CbCr_ac_Hidx:
                printf("\nIn table = dht_cbcr_ac\n");
                active_table = &jpeg_image.dht_cbcr_ac;
                break;
        }
    } else {
        active_table = last_node;
    }
    if (bit == 0) {
        printf("0");
        if (active_table->left->val == -1) {
            printf(".");
            last_node = active_table->left;
        } else {
            printf(". = %02x\n", active_table->left->val);
            last_node = NULL;
        }
        return active_table->left->val;
    }
    printf("1");
    if (active_table->right->val == -1) {
        printf(".");
        last_node = active_table->right;
    } else {
        printf(". = %02x\n", active_table->right->val);
        last_node = NULL;
    }
    return active_table->right->val;
}

void JpegDecoder::decode() {
    unsigned short short_val = 0;
    int continue_reading = 1;

    while (reader->read_short(short_val) > 0 && continue_reading) {
        switch (short_val) {
            case SOI:
                printf("\nread (%02x): SOI\n", short_val);
                break;
            case APP0:
                printf("\nread (%02x): APP0\n", short_val);
                processAPP0();
                break;
            case DQT:
                printf("\nread (%02x): DQT\n", short_val);
                processDQT();
                break;
            case SOF0:
                printf("\nread (%02x): SOF0\n", short_val);
                processSOF0();
                break;
            case DHT:
                printf("\nread (%02x): DHT\n", short_val);
                processDHT();
                break;
            case SOS:
                printf("\nread (%02x): SOS\n", short_val);
                processSOS();
                //continue_reading = 0;
                break;
            case COM:
                printf("\nread (%02x): COM\n", short_val);
                processCOM();
                break;
            default:
                break;
        }
    }
}