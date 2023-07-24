//
// Created by saintedlittle on 24.07.2023.
//

#ifndef WAVGENERATOR_NOISES_H
#define WAVGENERATOR_NOISES_H

#include <malloc.h>
#include <stdlib.h>

#include "../constants.h"

typedef struct noise_arguments {
    float perlin_amp_1d;
    float perlin_freq_1d;

    float perlin_amp_2d;
    float perlin_freq_2d;

    float perlin_amp_3d;
    float perlin_freq_3d;

    float fbm_amp;
    float fbm_freq;
    int fbm_layers;
    float fbm_lacunarity;
} noise_arguments;

static noise_arguments noise_information;

static noise_arguments* setup_noise_information() {

    noise_information.perlin_amp_1d = (float)(rand() % 100 + 1); // Random amplitude (1D Perlin Noise)
    noise_information.perlin_freq_1d = (float)(rand() % 10 + 1);  // Random frequency (1D Perlin Noise)

    noise_information.perlin_amp_2d = (float)(rand() % 100 + 1); // Random amplitude (2D Perlin Noise)
    noise_information.perlin_freq_2d = (float)(rand() % 10 + 1);  // Random frequency (2D Perlin Noise)

    noise_information.perlin_amp_3d = (float)(rand() % 100 + 1); // Random amplitude (3D Perlin Noise)
    noise_information.perlin_freq_3d = (float)(rand() % 10 + 1);  // Random frequency (3D Perlin Noise)

    noise_information.fbm_amp = (float)(rand() % 100 + 1);      // Random amplitude (FBM)
    noise_information.fbm_freq = (float)(rand() % 10 + 1);      // Random frequency (FBM)
    noise_information.fbm_layers = rand() % 5 + 1;                // Random number of layers (FBM)
    noise_information.fbm_lacunarity = (float)(rand() % 3 + 1); // Random lacunarity (FBM)

    return &noise_information;
}

void create_default_noise(float amplitude);

void create_perlin_noise_1d(float amplitude, float frequency);
void create_perlin_noise_2d(float amplitude, float frequency, int* buffer);
void create_perlin_noise_3d(float amplitude, float frequency, int* buffer);

void create_simplex_noise(float amplitude, float frequency);
void create_gradient_noise(float amplitude, float frequency);

void create_fbm_3d(float amplitude, float frequency, int layers, float lacunarity);

void create_pink_noise(float amplitude, float intensity);


#endif //WAVGENERATOR_NOISES_H
