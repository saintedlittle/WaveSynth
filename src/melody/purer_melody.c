//
// Created by saintedlittle on 27.07.2023.
//

#include "purer_melody.h"

void generate_sine_wave(float frequency, float duration, float *buffer) {
    int num_samples = duration * SAMPLE_RATE;
    for (int i = 0; i < num_samples; i++) {
        float t = i / (float)SAMPLE_RATE;
        buffer[i] = AMPLITUDE * sin(2.0 * M_PI * frequency * t);
    }
}

int generate_purer_melody(int melody_length) {

    float *melody_samples = (float *)malloc(melody_length * NOTE_DURATION * SAMPLE_RATE * sizeof(float));

    if (!melody_samples) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    int note_index = 0; // Start with the first note (do) in the scale

    for (int i = 0; i < melody_length; i++) {
        float frequency = scale_notes[note_index % scale_size];
        generate_sine_wave(frequency, NOTE_DURATION, &melody_samples[i * (int)(NOTE_DURATION * SAMPLE_RATE)]);

        // Move to the next note in the scale
        note_index++;
    }

    write_32bit_float_wav("purer_melody.wav", melody_length * NOTE_DURATION * SAMPLE_RATE, melody_samples, SAMPLE_RATE);

    free(melody_samples);
}
