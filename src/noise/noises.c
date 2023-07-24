//
// Created by saintedlittle on 24.07.2023.
//

#include "noises.h"
#include "../wav/make_wav.h"
#include "../utils/utils.h"

void create_default_noise(float amplitude) {
    for (int i = 0; i<BUF_SIZE; i++)
    {
        buffer[i] +=(int)amplitude*d_random(-1.0, 1.0); //nois
    }

    write_16bit_wav("default_noise.wav", BUF_SIZE, buffer, S_RATE);
}


void create_perlin_noise_1d(float amplitude, float frequency) {
    for (int i = 0; i < BUF_SIZE; i++) {
        float x = (float)i / S_RATE;
        buffer[i] += (int)(amplitude * 0.5 * (sin(x / frequency)));
    }

    write_16bit_wav("perlin_noise_1d.wav", BUF_SIZE, buffer, S_RATE);

}

void create_perlin_noise_2d(float amplitude, float frequency, int* buffer) {
    int mark = 0;

    if (buffer == NULL)
        mark = 1;

    for (int i = 0; i < BUF_SIZE; i++) {
        float x = (float)i / S_RATE;
        float y = 0.5; // Replace this with the 2D noise generation logic
        buffer[i] += (int)(amplitude * 0.5 * (sin(x / frequency) + sin(y / frequency)));
    }

    if (mark != 0)
        write_16bit_wav("perlin_noise_2d.wav", BUF_SIZE, buffer, S_RATE);

}

// Function to generate 3D Perlin Noise
void create_perlin_noise_3d(float amplitude, float frequency, int* buffer) {
    int mark = 0;

    if (buffer == NULL)
        mark = 1;

    for (int i = 0; i < BUF_SIZE; i++) {
        float x = (float)i / S_RATE;
        float y = 0.5; // Replace this with the 3D noise generation logic
        float z = 0.5; // Replace this with the 3D noise generation logic
        buffer[i] += (int)(amplitude * 0.5 * (sin(x / frequency) + sin(y / frequency) + sin(z / frequency)));
    }

    if (mark != 0)
        write_16bit_wav("perlin_noise_3d.wav", BUF_SIZE, buffer, S_RATE);

}


void create_simplex_noise(float amplitude, float frequency) {
    for (int i = 0; i < BUF_SIZE; i++) {
        float x = (float)i / S_RATE;
        float y = 0.0; // Initialize y value for 1D noise
        float z = 0.0; // Initialize z value for 1D noise
        buffer[i] += (int)(amplitude * 0.5 * (sin(x / frequency) + sin(y / frequency) + sin(z / frequency)));
    }

    write_16bit_wav("simplex_noise.wav", BUF_SIZE, buffer, S_RATE);
}

void create_gradient_noise(float amplitude, float frequency) {
    for (int i = 0; i < BUF_SIZE; i++) {
        float x = (float)i / S_RATE;
        float y = 0.0; // Initialize y value for 1D noise
        buffer[i] += (int)(amplitude * 0.5 * (cos(x / frequency) + cos(y / frequency)));
    }

    write_16bit_wav("gradient_noise.wav", BUF_SIZE, buffer, S_RATE);
}

// Function to generate 3D Fractal Brownian Motion (FBM)
void create_fbm_3d(float amplitude, float frequency, int layers, float lacunarity) {
    for (int i = 0; i < BUF_SIZE; i++) {
        float x = (float)i / S_RATE;
        float y = 0.5; // Replace this with the 3D noise generation logic
        float z = 0.5; // Replace this with the 3D noise generation logic
        float noise = 0.0;

        for (int j = 0; j < layers; j++) {
            int temp_buffer[BUF_SIZE] = {0}; // Temporary buffer to store perlin noise
            create_perlin_noise_3d(amplitude * pow(x, j), frequency * pow(lacunarity, j), temp_buffer);
            noise += temp_buffer[i];
        }

        buffer[i] += (int) noise;
    }

    write_16bit_wav("fbm_3d_noise.wav", BUF_SIZE, buffer, S_RATE);

}

void create_pink_noise(float amplitude, float intensity) {
    for (int i = 0; i < BUF_SIZE; i++) {
        float x = (float)i / S_RATE;
        double y = 0.5;
        buffer[i] += (int)(amplitude / pow(x, y + intensity));
    }

    write_16bit_wav("pink_noise.wav", BUF_SIZE, buffer, S_RATE);
}
