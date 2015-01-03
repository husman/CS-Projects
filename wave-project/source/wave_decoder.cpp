#include "include/wave_decoder.h"
#include "include/byte_reader.h"


int WaveDecoder::decodeWave(const char *filename, WaveInfo *wInfo) {
    ByteReader reader(filename);
    uint16_t word;
    uint32_t dword;
    int bytes_remaining;

    while(reader.read_uint32(dword, ARCH_BIG_ENDIAN) > 0) {
        switch(dword) {
            case RIFF:
            case RIFX:
                wInfo->riff_chunk_id = dword;
                if(wInfo->riff_chunk_id == RIFF) {
                    wInfo->endian = ARCH_LITTLE_ENDIAN;
                    printf("<riff-ck>:\n");
                } else {
                    wInfo->endian = ARCH_BIG_ENDIAN;
                    printf("<rifx-ck>:\n");
                }

                // Process the chunk size
                reader.read_uint32(dword, wInfo->endian);
                wInfo->riff_chunk_size = dword;
                printf("chunk size: %08X\n", wInfo->riff_chunk_size);

                // Process the 'RIFF or RIFX' chunk format/type
                // this should be 'WAVE'. If it is not, we error.
                reader.read_uint32(dword, BIG_ENDIAN);
                wInfo->riff_format = dword;
                if(wInfo->riff_format == WAVE)
                    printf("We have a WAVE file!\n\n");
                else
                    printf("We do not have a WAVE file!\n\n");
                break;
            case FMT:
                printf("<fmt-ck>:\n");

                // Process the chunk size
                reader.read_uint32(dword, wInfo->endian);
                wInfo->fmt_chunk_size = dword;
                bytes_remaining = wInfo->fmt_chunk_size;
                printf("chunk size: %08X\n", wInfo->fmt_chunk_size);

                // Process audio format
                reader.read_uint16(word, wInfo->endian);
                wInfo->wFormatTag = word;
                bytes_remaining -= 2;
                printf("Audio format: %u\n", wInfo->wFormatTag);

                // Process number of channels
                reader.read_uint16(word, wInfo->endian);
                wInfo->wChannels = word;
                bytes_remaining -= 2;
                printf("Channels: %u\n", wInfo->wChannels);

                // Process the sample rate
                reader.read_uint32(dword, wInfo->endian);
                wInfo->dwSamplesPerSec = dword;
                bytes_remaining -= 2;
                printf("Sample rate: %u\n", wInfo->dwSamplesPerSec);

                // Process the byte rate
                reader.read_uint32(dword, wInfo->endian);
                wInfo->dwAvgBytesPerSec = dword;
                bytes_remaining -= 4;
                printf("Byte rate: %u\n", wInfo->dwAvgBytesPerSec);

                // Process block alignment
                reader.read_uint16(word, wInfo->endian);
                wInfo->wBlockAlign = word;
                bytes_remaining -= 4;
                printf("Block align: %u\n", wInfo->wBlockAlign);

                // Process bits per sample
                reader.read_uint16(word, wInfo->endian);
                wInfo->wBitsPerSample = word;
                bytes_remaining -= 2;
                printf("Bits/sample: %u\n", wInfo->wBitsPerSample);

                // At this point, we expect there to be no more data for this
                // chunk if the audio format is 1 (PCM). The RIFF standard
                // requires that no additional fields be added if the audio
                // format is PCM. However, some encoders still add one or
                // two of these fields. Therefore, we skip the remaining
                // bytes of this chunk if our audio format is PCM.
                // Otherwise, we will record the field values.
                if(bytes_remaining == 0)
                    continue;
                else if(bytes_remaining > 0 && wInfo->wFormatTag == WAVE_FORMAT_PCM) {
                    if(reader.skip_bytes(bytes_remaining) == bytes_remaining)
                        printf("remaining %u bytes are being skipped for PCM.\n", bytes_remaining);
                    else {
                        printf("The file terminated prematurely, or could not allocate enough memory.");
                        return -1;
                    }
                }
                else if(bytes_remaining < 0) // Was the wrong chunk size given to us?
                    return -1;
                else {
                    // Process extra params
                    reader.read_uint16(word, wInfo->endian);
                    wInfo->wExtraParamSize = word;
                    bytes_remaining -= 2;
                    printf("Extra param size: %04X\n", wInfo->wExtraParamSize);

                    // allocate extra params based on extra param size
                    wInfo->extraParams = (uint8_t *)malloc(wInfo->wExtraParamSize);

                    if(wInfo->extraParams == NULL) {
                        printf("Could not allocate enough memory.\n");
                        return -1;
                    }

                    if(reader.read_bytes(wInfo->extraParams, wInfo->wExtraParamSize) < wInfo->wExtraParamSize) {
                        printf("The file terminated prematurely or is corrupt.\n");
                        return -1;
                    }
                    bytes_remaining -= wInfo->wExtraParamSize;

                    // Now we expect bytes remaining to be zero (0). If not, error
                    if(bytes_remaining != 0) {
                        printf("The file could not be read or is corrupt.\n");
                        return -1;
                    }
                }
                printf("\n");
                break;
            case DATA:
                printf("<data-ck>:\n");

                // Process the chunk size
                reader.read_uint32(dword, wInfo->endian);
                wInfo->data_chunk_size = dword;
                bytes_remaining = wInfo->data_chunk_size;
                printf("chunk size: %u\n", wInfo->data_chunk_size);

                // Process the WAVE data
                // allocate extra params based on extra param size
                wInfo->data = (uint8_t *)malloc(wInfo->data_chunk_size);
                if(reader.read_bytes((uint8_t *)wInfo->data, wInfo->data_chunk_size) < wInfo->data_chunk_size) {
                    printf("The file terminated prematurely or is corrupt.\n");
                    return -1;
                }
                bytes_remaining -= wInfo->data_chunk_size;

                // Now we expect bytes remaining to be zero (0). If not, error
                if(bytes_remaining != 0) {
                    printf("The file could not be read or is corrupt.\n");
                    return -1;
                }
                break;
            default:
                printf("Unregonized RIFF packet, skipping...");

                // Process the chunk size
                reader.read_uint32(dword, wInfo->endian);
                uint8_t *skipped_bytes = (uint8_t *)malloc(dword);
                if(reader.read_bytes(skipped_bytes, dword) < dword) {
                    printf("The file could not be read or is corrupt.\n");
                    return -1;
                }
                break;
        }
    }
    printf("\nDone decoding WAVE file.\n\n");
    return 1;
}