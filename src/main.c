#include <stdlib.h>
#include <time.h>

#include "math/functions.h"

int main() {

    float amplitude = 20000; // 32767/(10%amp+5%amp+100%amp)

    float freq_Hz = 100;
    float decay_factor = 1 / freq_Hz;

    // FOR BIVARIATE GAUSSIAN
    float mean_x = 0.0;       // Mean along the x-axis
    float mean_y = 5.0;       // Mean along the y-axis
    float sigma_x = 1.5;      // Standard deviation along the x-axis
    float sigma_y = 2.0;      // Standard deviation along the y-axis
    // END.

    float base_log = (float) d_random(1.1, 10.0); // Base of the logarithm
    int order_bessel = (int)d_random(1.0, 10.0); // Order of the Bessel function


    initialize_srand();
    
    create_sinusoid(amplitude, freq_Hz);

    create_complex_sinusoid(amplitude, freq_Hz);

    create_square_wave(amplitude, freq_Hz);
    create_decay_envelope(amplitude, decay_factor);

    create_noise(amplitude);

    create_sawtooth_wave(amplitude);
    create_triangle_wave(amplitude);
    create_musical_chord(amplitude);
    create_complex_waveform(amplitude);

    create_2d_chirp(amplitude);
    create_complex_envelope(amplitude);
    create_random_amplitude_modulation(amplitude);

    create_bivariate_gaussian(amplitude, mean_x, mean_y, sigma_x, sigma_y);

    create_bessel_function(amplitude, order_bessel);

    create_logarithmic_function(amplitude, base_log);

    write_bmp("image.bmp", "image.wav");

    return EXIT_SUCCESS;
}