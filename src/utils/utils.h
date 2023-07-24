//
// Created by saintedlittle on 24.07.2023.
//

#ifndef WAVGENERATOR_UTILS_H
#define WAVGENERATOR_UTILS_H

#include <stdint.h>

#include "../stb/stb_image.h"

#include "../wav/make_wav.h"
#include "../constants.h"

static unsigned long read_bmp_image(const char* bmp_filename, uint8_t** audio_data) {
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

static int write_bmp(char* bmp_filename, char* output_filename) {
    uint8_t* audio_data = NULL;
    unsigned long num_samples = read_bmp_image(bmp_filename, &audio_data);

    if (num_samples == 0) {
        return 1;
    }

    write_24bit_wav(output_filename, num_samples, audio_data, S_RATE);

    free(audio_data);

    return 0;
}

static double d_random(double min, double max) {
    return min + (max - min) / RAND_MAX * rand();
}

#endif //WAVGENERATOR_UTILS_H
