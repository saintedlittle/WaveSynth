//
// Created by saintedlittle on 24.07.2023.
//

#ifndef WAVGENERATOR_FUNCTIONS_H
#define WAVGENERATOR_FUNCTIONS_H

#include <stdlib.h>
#include <omp.h>

#include "../constants.h"

#include "../stb/stb_image.h"

#define STEPS 1000000000
#define RATIO_DURATION 10

double calculate_golden_ratio();

// Function to generate_purer_melody a melody using the golden ratio as rhythm
void generate_melody(char *filename, double duration_seconds);

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

void print_calculated_golden_ratio();

#endif //WAVGENERATOR_FUNCTIONS_H
