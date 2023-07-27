#ifndef MAKE_WAV_H
#define MAKE_WAV_H

#include <stdint.h>

#include "../constants.h"

typedef struct {
    char chunk_id[4];
    uint32_t chunk_size;
    char format[4];
    char subchunk1_id[4];
    uint32_t subchunk1_size;
    uint16_t audio_format;
    uint16_t num_channels;
    uint32_t sample_rate;
    uint32_t byte_rate;
    uint16_t block_align;
    uint16_t bits_per_sample;
    char subchunk2_id[4];
    uint32_t subchunk2_size;
} WavHeader;


void write_16bit_wav(char* filename, unsigned long num_samples, short int * data, int s_rate);

void write_24bit_wav(const char* filename, unsigned long num_samples, uint8_t* data, int s_rate);

void write_32bit_float_wav(char *filename, unsigned long num_samples, float *data, int s_rate);

#endif
