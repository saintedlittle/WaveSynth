//
// Created by saintedlittle on 24.07.2023.
//

#ifndef WAVGENERATOR_FUNCTIONS_H
#define WAVGENERATOR_FUNCTIONS_H

#include "../constants.h"

#include "../stb/stb_image.h"

void create_sinusoid(float amplitude, float freq_Hz);

void create_complex_sinusoid(float amplitude, float freq_Hz);
void create_decay_envelope(float amplitude, float decay_factor);

void create_musical_chord(float amplitude);
void create_complex_envelope(float amplitude);
void create_random_amplitude_modulation(float amplitude);
void create_2d_chirp(float amplitude);

void create_bivariate_gaussian(float amplitude, float mean_x, float mean_y, float sigma_x, float sigma_y);

void create_logarithmic_function(float amplitude, float base);
void create_bessel_function(float amplitude, int n);

#endif //WAVGENERATOR_FUNCTIONS_H
