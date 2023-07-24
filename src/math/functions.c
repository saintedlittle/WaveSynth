//
// Created by saintedlittle on 24.07.2023.
//

#include <stdlib.h>
#include <time.h>
#include "functions.h"

#include "../wav/make_wav.h"

short int buffer[BUF_SIZE];

unsigned long read_bmp_image(const char* bmp_filename, uint8_t** audio_data);

void initialize_srand() {
    srand((unsigned int)time(0));
}

void create_sinusoid(float amplitude, float freq_Hz) {
    for (int i = 0; i < BUF_SIZE; i++) {

        buffer[i] = (int)(amplitude/10 * sin((float)(2*M_PI*i*freq_Hz/S_RATE))); //10%amp
        buffer[i] += (int)(amplitude/20 * sin((float)(2*M_PI*i*10*freq_Hz/S_RATE))); //5% amp
        buffer[i] +=(int)(amplitude * sin((float)(2*M_PI*i*100*freq_Hz/S_RATE))); //100% amp

    }

    write_16bit_wav("sinusoid.wav", BUF_SIZE, buffer, S_RATE);
}

void create_noise(float amplitude) {
    for (int i = 0; i<BUF_SIZE; i++)
    {
        buffer[i] +=(int)amplitude*d_random(-1.0, 1.0); //nois
    }

    write_16bit_wav("noise.wav", BUF_SIZE, buffer, S_RATE);
}

void create_complex_sinusoid(float amplitude, float freq_Hz) {
    for (int i = 0; i < BUF_SIZE; i++) {
        buffer[i] = (int)(amplitude / 10 * sin((float)(2 * M_PI * i * freq_Hz / S_RATE)));         // 10% amp
        buffer[i] += (int)(amplitude / 20 * sin((float)(2 * M_PI * i * 10 * freq_Hz / S_RATE)));   // 5% amp
        buffer[i] += (int)(amplitude * sin((float)(2 * M_PI * i * 100 * freq_Hz / S_RATE)));       // 100% amp
        buffer[i] += (int)(amplitude / 5 * sin((float)(2 * M_PI * i * 1000 * freq_Hz / S_RATE)));  // 20% amp
    }

    write_16bit_wav("complex_sinusoid.wav", BUF_SIZE, buffer, S_RATE);
}

void create_square_wave(float amplitude, float freq_Hz) {
    for (int i = 0; i < BUF_SIZE; i++) {
        buffer[i] = (int)(amplitude * signbit(sin((float)(2 * M_PI * i * freq_Hz / S_RATE))));
    }

    write_16bit_wav("square_wave.wav", BUF_SIZE, buffer, S_RATE);
}

void create_sawtooth_wave(float amplitude) {
    for (int i = 0; i < BUF_SIZE; i++) {
        buffer[i] = (int)(amplitude * ((float)i / BUF_SIZE - 0.5));
    }

    write_16bit_wav("sawtooth_wave.wav", BUF_SIZE, buffer, S_RATE);
}

void create_decay_envelope(float amplitude, float decay_factor) {
    for (int i = 0; i < BUF_SIZE; i++) {
        float t = (float)i / BUF_SIZE;
        buffer[i] = (int)(amplitude * exp(-decay_factor * t));
    }

    write_16bit_wav("decay_envelope.wav", BUF_SIZE, buffer, S_RATE);
}

void create_triangle_wave(float amplitude) {
    for (int i = 0; i < BUF_SIZE; i++) {
        float t = (float)i / BUF_SIZE;
        buffer[i] = (int)(amplitude * (2 * fabs(2 * t - 1) - 1));
    }

    write_16bit_wav("triangle_wave.wav", BUF_SIZE, buffer, S_RATE);
}

void create_bivariate_gaussian(float amplitude, float mean_x, float mean_y, float sigma_x, float sigma_y) {
    for (int i = 0; i < BUF_SIZE; i++) {
        float x = -10.0 + 20.0 * (float)i / BUF_SIZE; // Adjust the scaling factor as needed
        buffer[i] = (int)(amplitude * exp(-0.5 * ((x - mean_x) * (x - mean_x) / (sigma_x * sigma_x)
                                                  + (x - mean_y) * (x - mean_y) / (sigma_y * sigma_y))));
    }

    write_16bit_wav("bivariate_gaussian.wav", BUF_SIZE, buffer, S_RATE);
}

void create_logarithmic_function(float amplitude, float base) {
    for (int i = 0; i < BUF_SIZE; i++) {
        float x = 1.0 + 19.0 * (float)i / BUF_SIZE; // Adjust the scaling factor as needed
        buffer[i] = (int)(amplitude * log(x) / log(base));
    }

    write_16bit_wav("logarithmic_function.wav", BUF_SIZE, buffer, S_RATE);
}

void create_bessel_function(float amplitude, int n) {
    for (int i = 0; i < BUF_SIZE; i++) {
        float x = 20.0 * (float)i / BUF_SIZE; // Adjust the scaling factor as needed

#ifdef WIN32
        buffer[i] = (int)(amplitude * _jn(n, x));
#else
        buffer[i] = (int)(amplitude * jn(n, x));
#endif
    }

    write_16bit_wav("bessel_function.wav", BUF_SIZE, buffer, S_RATE);
}

void create_musical_chord(float amplitude) {
    float frequencies[] = {261.63, 329.63, 392.00, 523.25}; // C Major chord frequencies
    int num_frequencies = sizeof(frequencies) / sizeof(frequencies[0]);

    for (int i = 0; i < BUF_SIZE; i++) {
        buffer[i] = 0;
        for (int j = 0; j < num_frequencies; j++) {
            float phase = 2.0 * M_PI * frequencies[j] * (float)i / S_RATE;
            buffer[i] += (short)(amplitude * sin(phase));
        }
    }

    write_16bit_wav("musical_chord.wav", BUF_SIZE, buffer, S_RATE);
}

void create_complex_waveform(float amplitude) {
    float carrier_freq = 440.0; // Frequency of the carrier wave
    float modulator_freq = 5.0; // Frequency of the modulating wave

    for (int i = 0; i < BUF_SIZE; i++) {
        float carrier_phase = 2.0 * M_PI * carrier_freq * (float)i / S_RATE;
        float modulator_phase = 2.0 * M_PI * modulator_freq * (float)i / S_RATE;
        float modulator_value = 0.5 * sin(modulator_phase) + 1.0; // Sine wave between 0 and 1
        buffer[i] = (short)(amplitude * sin(carrier_phase) * modulator_value);
    }

    write_16bit_wav("complex_waveform.wav", BUF_SIZE, buffer, S_RATE);
}

void create_complex_envelope(float amplitude) {
    for (int i = 0; i < BUF_SIZE; i++) {
        float envelope = 0.5 * (1.0 + cos(2.0 * M_PI * (float)i / BUF_SIZE));
        buffer[i] = (short)(amplitude * envelope);
    }

    write_16bit_wav("complex_envelope.wav", BUF_SIZE, buffer, S_RATE);
}

void create_random_amplitude_modulation(float amplitude) {
    srand(time(0)); // Seed the random number generator with the current time

    for (int i = 0; i < BUF_SIZE; i++) {
        float envelope = (float)rand() / RAND_MAX;
        buffer[i] = (short)(amplitude * envelope);
    }

    write_16bit_wav("random_amplitude_modulation.wav", BUF_SIZE, buffer, S_RATE);
}
void create_2d_chirp(float amplitude) {
    float start_freq = 100.0; // Starting frequency of the chirp
    float end_freq = 1000.0;  // Ending frequency of the chirp

    for (int i = 0; i < BUF_SIZE; i++) {
        float t = (float)i / S_RATE;
        float freq = start_freq + (end_freq - start_freq) * t;
        float phase = 2.0 * M_PI * freq * t;
        buffer[i] = (short)(amplitude * sin(phase));
    }

    write_16bit_wav("2d_chirp.wav", BUF_SIZE, buffer, S_RATE);
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