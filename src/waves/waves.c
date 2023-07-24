//
// Created by saintedlittle on 24.07.2023.
//

#include "waves.h"
#include "../constants.h"
#include "../wav/make_wav.h"

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

void create_triangle_wave(float amplitude) {
    for (int i = 0; i < BUF_SIZE; i++) {
        float t = (float)i / BUF_SIZE;
        buffer[i] = (int)(amplitude * (2 * fabs(2 * t - 1) - 1));
    }

    write_16bit_wav("triangle_wave.wav", BUF_SIZE, buffer, S_RATE);
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