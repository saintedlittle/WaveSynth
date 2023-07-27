//
// Created by saintedlittle on 27.07.2023.
//

#ifndef WAVGENERATOR_PURER_MELODY_H
#define WAVGENERATOR_PURER_MELODY_H

#include <stdio.h>
#include <malloc.h>
#include "../wav/make_wav.h"

#define SAMPLE_RATE 44100   // Standard audio sample rate
#define AMPLITUDE 0.8       // Maximum amplitude for 32-bit floating-point WAV
#define NOTE_DURATION 1.0        // Duration of each note in seconds

static const int scale_notes[] = {261, 293, 329, 349, 392, 440, 493};
static const int scale_size = sizeof(scale_notes) / sizeof(scale_notes[0]);

void generate_sine_wave(float frequency, float duration, float *buffer);

int generate_purer_melody(int melody_length);

#endif //WAVGENERATOR_PURER_MELODY_H
