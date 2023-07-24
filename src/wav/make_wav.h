#ifndef MAKE_WAV_H
#define MAKE_WAV_H

#include <stdint.h>

#include "../constants.h"

void write_16bit_wav(char* filename, unsigned long num_samples, short int * data, int s_rate);

void write_24bit_wav(const char* filename, unsigned long num_samples, uint8_t* data, int s_rate);

#endif
