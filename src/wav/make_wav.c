/*
 * Creates a WAV file from an array of ints.
 */

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

void write_32bit_float_wav(char *filename, unsigned long num_samples, float *data, int s_rate) {
    FILE *wav_file = fopen(filename, "wb");

    if (!wav_file) {
        printf("Error opening file for writing.\n");
        return;
    }

    // Prepare WAV header
    WavHeader header;
    header.chunk_id[0] = 'R';
    header.chunk_id[1] = 'I';
    header.chunk_id[2] = 'F';
    header.chunk_id[3] = 'F';
    header.chunk_size = num_samples * sizeof(float) + sizeof(WavHeader) - 8;
    header.format[0] = 'W';
    header.format[1] = 'A';
    header.format[2] = 'V';
    header.format[3] = 'E';
    header.subchunk1_id[0] = 'f';
    header.subchunk1_id[1] = 'm';
    header.subchunk1_id[2] = 't';
    header.subchunk1_id[3] = ' ';
    header.subchunk1_size = 16;
    header.audio_format = 3; // 3 represents floating-point format
    header.num_channels = 1; // Mono audio
    header.sample_rate = s_rate;
    header.byte_rate = s_rate * sizeof(float);
    header.block_align = sizeof(float);
    header.bits_per_sample = sizeof(float) * 8;
    header.subchunk2_id[0] = 'd';
    header.subchunk2_id[1] = 'a';
    header.subchunk2_id[2] = 't';
    header.subchunk2_id[3] = 'a';
    header.subchunk2_size = num_samples * sizeof(float);

    // Write WAV header
    fwrite(&header, sizeof(WavHeader), 1, wav_file);

    // Write audio data
    fwrite(data, sizeof(float), num_samples, wav_file);

    // Close the file
    fclose(wav_file);

    printf("WAV file '%s' has been successfully written.\n", filename);
}