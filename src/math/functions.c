//
// Created by saintedlittle on 24.07.2023.
//

#include "functions.h"

#include "../wav/make_wav.h"

void create_sinusoid(float amplitude, float freq_Hz) {
    for (int i = 0; i < BUF_SIZE; i++) {

        buffer[i] = (int)(amplitude/10 * sin((float)(2*M_PI*i*freq_Hz/S_RATE))); //10%amp
        buffer[i] += (int)(amplitude/20 * sin((float)(2*M_PI*i*10*freq_Hz/S_RATE))); //5% amp
        buffer[i] +=(int)(amplitude * sin((float)(2*M_PI*i*100*freq_Hz/S_RATE))); //100% amp

    }

    write_16bit_wav("sinusoid.wav", BUF_SIZE, buffer, S_RATE);
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

void create_decay_envelope(float amplitude, float decay_factor) {
    for (int i = 0; i < BUF_SIZE; i++) {
        float t = (float)i / BUF_SIZE;
        buffer[i] = (int)(amplitude * exp(-decay_factor * t));
    }

    write_16bit_wav("decay_envelope.wav", BUF_SIZE, buffer, S_RATE);
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

void create_complex_envelope(float amplitude) {
    for (int i = 0; i < BUF_SIZE; i++) {
        float envelope = 0.5 * (1.0 + cos(2.0 * M_PI * (float)i / BUF_SIZE));
        buffer[i] = (short)(amplitude * envelope);
    }

    write_16bit_wav("complex_envelope.wav", BUF_SIZE, buffer, S_RATE);
}

void create_random_amplitude_modulation(float amplitude) {
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

double calculate_golden_ratio() {
    double phi = 1.0;
    double previous_term = 1.0;

    #pragma omp parallel for
    for (int i = 0; i < STEPS; i++) {
        phi = 1.0 + 1.0 / previous_term;
        previous_term = phi;

        printf("STEP %i) %.500000f \n", i-1, previous_term);
    }

    return phi;
}

void generate_melody(char *filename, double duration_seconds) {
    // Constants for the golden ratio and musical note frequencies
    const double golden_ratio = 1.61803398875;
    const double base_frequency = 440.0; // A4 note frequency (440 Hz)
    const double semitone_ratio = pow(2, 1.0 / 12.0);

    // Sampling rate and duration
    int sampling_rate = 44100; // Adjust as per your requirements
    unsigned long num_samples = (unsigned long)(duration_seconds * sampling_rate);

    // Allocate memory for audio data
    short int *audio_data = (short int *)malloc(num_samples * sizeof(short int));

    // Calculate the time interval between consecutive notes using the golden ratio
    double time_interval = 1.0 / (base_frequency * pow(semitone_ratio, 12));

    // Generate the melody
    double time = 0.0;
    int note_index = 0;

    while (time < duration_seconds) {
        // Calculate the frequency of the current note
        double frequency = base_frequency * pow(semitone_ratio, note_index);

        // Calculate the number of samples for the note duration
        unsigned long note_duration_samples = (unsigned long)(time_interval * sampling_rate);

        // Generate the waveform for the current note (sine wave, for simplicity)
        for (unsigned long i = 0; i < note_duration_samples; i++) {
            double t = 2.0 * M_PI * frequency * ((double)i / (double)sampling_rate);
            audio_data[i] = (short int)(32767.0 * sin(t)); // Convert to 16-bit signed PCM
        }

        // Update time and move to the next note index (based on golden ratio)
        time += time_interval;
        note_index = (note_index + 1) % 12; // Assuming 12 notes in an octave
        time_interval *= golden_ratio;
    }

    // Write the generated audio data to a WAV file
    write_16bit_wav(filename, num_samples, audio_data, sampling_rate);

    // Free allocated memory
    free(audio_data);
}

void print_calculated_golden_ratio() {
    printf("Approximate value of the golden ratio: %.50f\n", calculate_golden_ratio());
}

