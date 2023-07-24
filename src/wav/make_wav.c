/*
 * Creates a WAV file from an array of ints.
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "make_wav.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../stb/stb_image.h"

void write_little_endian(unsigned int word, int num_bytes, FILE *wav_file) {
	unsigned buf;
	while(num_bytes > 0) {
        buf = word & 0xff;
		fwrite(&buf, 1,1, wav_file);
		num_bytes--;
	word >>= 8;
	}
}
 
/* information about the WAV file format from
 
http://ccrma.stanford.edu/courses/422/projects/WaveFormat/
 
 */
 
void write_16bit_wav(char * filename, unsigned long num_samples, short int * data, int s_rate) {
	FILE* wav_file;
	unsigned int sample_rate;
	unsigned int num_channels;
	unsigned int bytes_per_sample;
	unsigned int byte_rate;
	unsigned long i;    /* counter for samples */
 
	num_channels = 1;   /* monoaural */
	bytes_per_sample = 2;
 
	if (s_rate<=0) sample_rate = 44100;
	else sample_rate = (unsigned int) s_rate;
 
	byte_rate = sample_rate*num_channels*bytes_per_sample;
 
	wav_file = fopen(filename, "w");
	assert(wav_file);   /* make sure it opened */
 
	/* write RIFF header */
	fwrite("RIFF", 1, 4, wav_file);
	write_little_endian(36 + bytes_per_sample* num_samples*num_channels, 4, wav_file);
	fwrite("WAVE", 1, 4, wav_file);
 
	/* write fmt  subchunk */
	fwrite("fmt ", 1, 4, wav_file);
	write_little_endian(16, 4, wav_file);   /* SubChunk1Size is 16 */
	write_little_endian(1, 2, wav_file);    /* PCM is format 1 */
	write_little_endian(num_channels, 2, wav_file);
	write_little_endian(sample_rate, 4, wav_file);
	write_little_endian(byte_rate, 4, wav_file);
	write_little_endian(num_channels*bytes_per_sample, 2, wav_file);  /* block align */
	write_little_endian(8*bytes_per_sample, 2, wav_file);  /* bits/sample */
 
	/* write data subchunk */
	fwrite("data", 1, 4, wav_file);
	write_little_endian(bytes_per_sample* num_samples*num_channels, 4, wav_file);
	
	for (i=0; i< num_samples; i++) {
        write_little_endian((unsigned int)(data[i]),bytes_per_sample, wav_file);
	}
 
	fclose(wav_file);
}

void write_24bit_wav(const char* filename, unsigned long num_samples, uint8_t* data, int s_rate) {
    FILE* wav_file = fopen(filename, "wb");
    assert(wav_file);   /* make sure it opened */


    // WAV file header information
    const int PCM_FORMAT = 1; // PCM format code
    const int NUM_CHANNELS = 2; // Stereo audio
    const int BITS_PER_SAMPLE = 24; // 24-bit audio

    unsigned long byte_rate = s_rate * NUM_CHANNELS * (BITS_PER_SAMPLE / 8);
    unsigned long block_align = NUM_CHANNELS * (BITS_PER_SAMPLE / 8);

    // WAV file header
    fwrite("RIFF", 1, 4, wav_file); // RIFF header
    unsigned long chunk_size = 36 + num_samples * NUM_CHANNELS * (BITS_PER_SAMPLE / 8);
    write_little_endian(chunk_size, 4, wav_file); // File size
    fwrite("WAVE", 1, 4, wav_file); // WAVE header
    fwrite("fmt ", 1, 4, wav_file); // Format chunk header
    unsigned long subchunk_size = 16;
    write_little_endian(subchunk_size, 4, wav_file); // Subchunk size
    unsigned short audio_format = PCM_FORMAT;
    write_little_endian(audio_format, 2, wav_file); // Audio format
    write_little_endian(NUM_CHANNELS, 2, wav_file); // Number of channels
    write_little_endian(s_rate, 4, wav_file); // Sample rate
    write_little_endian(byte_rate, 4, wav_file); // Byte rate
    write_little_endian(block_align, 2, wav_file); // Block align
    write_little_endian(BITS_PER_SAMPLE, 2, wav_file); // Bits per sample

    // Data chunk
    fwrite("data", 1, 4, wav_file);
    unsigned long data_size = num_samples * NUM_CHANNELS * (BITS_PER_SAMPLE / 8);
    write_little_endian(data_size, 4, wav_file);

    // Convert 24-bit audio data to little-endian format
    for (unsigned long i = 0; i < num_samples; i++) {
        write_little_endian(data[i * NUM_CHANNELS * 3 + 2], 1, wav_file); // 1st byte (LSB)
        write_little_endian(data[i * NUM_CHANNELS * 3 + 1], 1, wav_file); // 2nd byte
        write_little_endian(data[i * NUM_CHANNELS * 3], 1, wav_file);     // 3rd byte (MSB)
    }

    fclose(wav_file);
}