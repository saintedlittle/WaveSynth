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
    assert(wav_file);

    // WAV file header information
    const int PCM_FORMAT = 1; // PCM format code
    const int NUM_CHANNELS = 2; // Stereo audio
    const int BITS_PER_SAMPLE = 24; // 24-bit audio

    unsigned long byte_rate = s_rate * NUM_CHANNELS * (BITS_PER_SAMPLE / 8);
    unsigned long block_align = NUM_CHANNELS * (BITS_PER_SAMPLE / 8);

    // WAV file header
    fwrite("RIFF", 1, 4, wav_file); // RIFF header
    unsigned long chunk_size = 36 + num_samples * NUM_CHANNELS * (BITS_PER_SAMPLE / 8);
    fwrite(&chunk_size, sizeof(chunk_size), 1, wav_file); // File size
    fwrite("WAVE", 1, 4, wav_file); // WAVE header
    fwrite("fmt ", 1, 4, wav_file); // Format chunk header
    unsigned long subchunk_size = 16;
    fwrite(&subchunk_size, sizeof(subchunk_size), 1, wav_file); // Subchunk size
    unsigned short audio_format = PCM_FORMAT;
    fwrite(&audio_format, sizeof(audio_format), 1, wav_file); // Audio format
    fwrite(&NUM_CHANNELS, sizeof(NUM_CHANNELS), 1, wav_file); // Number of channels
    fwrite(&s_rate, sizeof(s_rate), 1, wav_file); // Sample rate
    fwrite(&byte_rate, sizeof(byte_rate), 1, wav_file); // Byte rate
    fwrite(&block_align, sizeof(block_align), 1, wav_file); // Block align
    fwrite(&BITS_PER_SAMPLE, sizeof(BITS_PER_SAMPLE), 1, wav_file); // Bits per sample

    // Data chunk
    fwrite("data", 1, 4, wav_file);
    unsigned long data_size = num_samples * NUM_CHANNELS * (BITS_PER_SAMPLE / 8);
    fwrite(&data_size, sizeof(data_size), 1, wav_file);
    fwrite(data, sizeof(uint8_t), num_samples, wav_file);

    fclose(wav_file);
}

unsigned long read_bmp_image(const char* bmp_filename, uint8_t** audio_data) {
    int width, height, channels;
    uint8_t* bmp_data = stbi_load(bmp_filename, &width, &height, &channels, STBI_rgb);

    if (!bmp_data) {
        printf("Error loading BMP image: %s\n", stbi_failure_reason());
        return 0;
    }

    unsigned long num_samples = width * height;
    *audio_data = (uint8_t*)malloc(num_samples * sizeof(uint8_t));

    for (unsigned long i = 0; i < num_samples; i++) {
        // Convert BMP RGB data to mono audio (simple average of RGB values)
        uint8_t r = bmp_data[i * channels];
        uint8_t g = bmp_data[i * channels + 1];
        uint8_t b = bmp_data[i * channels + 2];
        (*audio_data)[i] = (r + g + b) / 3;
    }

    stbi_image_free(bmp_data);

    return num_samples;
}

int write_bmp(char* bmp_filename, char* output_filename) {
    uint8_t* audio_data = NULL;
    unsigned long num_samples = read_bmp_image(bmp_filename, &audio_data);

    if (num_samples == 0) {
        return 1;
    }

    write_24bit_wav(output_filename, num_samples, audio_data, S_RATE);

    free(audio_data);

    return 0;
}

double d_random(double min, double max) {
    return min + (max - min) / RAND_MAX * rand();
}
