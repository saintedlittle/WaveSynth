//
// Created by saintedlittle on 24.07.2023.
//

#ifndef WAVGENERATOR_FUNCTIONS_H
#define WAVGENERATOR_FUNCTIONS_H

#include "../constants.h"

#include "../stb/stb_image.h"

void initialize_srand();

void create_noise(float amplitude);
void create_sinusoid(float amplitude, float freq_Hz);

void create_complex_sinusoid(float amplitude, float freq_Hz);
void create_square_wave(float amplitude, float freq_Hz);
void create_decay_envelope(float amplitude, float decay_factor);

void create_sawtooth_wave(float amplitude);
void create_triangle_wave(float amplitude);
void create_musical_chord(float amplitude);
void create_complex_waveform(float amplitude);
void create_complex_envelope(float amplitude);
void create_random_amplitude_modulation(float amplitude);
void create_2d_chirp(float amplitude);

void create_bivariate_gaussian(float amplitude, float mean_x, float mean_y, float sigma_x, float sigma_y);

void create_logarithmic_function(float amplitude, float base);
void create_bessel_function(float amplitude, int n);

int write_bmp(char* bmp_filename, char* output_filename);

double d_random(double min, double max);

#endif //WAVGENERATOR_FUNCTIONS_H
