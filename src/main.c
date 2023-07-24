#include <time.h>
#include "noise/noises.h"
#include "waves/waves.h"
#include "utils/utils.h"

void initialize_srand();

void create_perlins();
void create_waves();
void create_math();
void create_noise();

int main() {
    initialize_srand();

    setup_information();
    setup_bessel_and_log((int)d_random(1.0, 10.0), (float) d_random(1.1, 10.0));

    create_waves();
    create_math();
    create_noise();

    setup_noise_information();

    create_perlins();
    create_fbm_3d(noise_information.fbm_amp, noise_information.fbm_freq, noise_information.fbm_layers, noise_information.fbm_lacunarity);

    write_bmp("image.bmp", "image.wav");

    return EXIT_SUCCESS;
}

void initialize_srand() {
    srand((unsigned int)time(0));
}


void create_perlins() {
    create_perlin_noise_1d(noise_information.perlin_amp_1d, noise_information.perlin_freq_1d);
    create_perlin_noise_2d(noise_information.perlin_amp_2d, noise_information.perlin_freq_2d, NULL);
    create_perlin_noise_3d(noise_information.perlin_amp_3d, noise_information.perlin_freq_3d, NULL);
}

void create_waves() {
    create_square_wave(information.amplitude, information.freq_Hz);
    create_sawtooth_wave(information.amplitude);
    create_triangle_wave(information.amplitude);

}

void create_math() {
    create_sinusoid(information.amplitude, information.freq_Hz);

    create_complex_sinusoid(information.amplitude, information.freq_Hz);

    create_decay_envelope(information.amplitude, information.decay_factor);

    create_musical_chord(information.amplitude);

    create_2d_chirp(information.amplitude);
    create_complex_envelope(information.amplitude);
    create_random_amplitude_modulation(information.amplitude);

    create_bivariate_gaussian(information.amplitude, information.mean_x, information.mean_y, information.sigma_x, information.sigma_y);

    create_bessel_function(information.amplitude, information.order_bessel);

    create_logarithmic_function(information.amplitude, information.base_log);

}

void create_noise() {
    create_default_noise(information.amplitude);

    create_simplex_noise(information.amplitude, information.freq_Hz);
    create_gradient_noise(information.amplitude, information.freq_Hz);

    create_pink_noise(information.amplitude, information.freq_Hz);
}