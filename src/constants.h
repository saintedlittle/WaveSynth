//
// Created by saintedlittle on 24.07.2023.
//

#ifndef WAVGENERATOR_CONSTANTS_H
#define WAVGENERATOR_CONSTANTS_H

// FOR MATH

#ifdef WIN32
#ifdef MSVC
#include <corecrt_math.h>
#endif

#include "math/functions.h"

#define M_PI acos(-1.0)
#else
#include <math.h>
#endif

#define S_RATE  (44100)
#define BUF_SIZE (S_RATE*10) /* 2 second buffer */

static short int buffer[BUF_SIZE];

typedef struct basic_information {
    float amplitude;

    float freq_Hz;
    float decay_factor;

    // FOR BIVARIATE GAUSSIAN
    float mean_x;
    float mean_y;
    float sigma_x;
    float sigma_y;

    float base_log;
    int order_bessel;


} basic_information;

static basic_information information;

static void setup_information() {

    information.amplitude = 20000; // 32767/(10%amp+5%amp+100%amp)

    information.freq_Hz = 100;
    information.decay_factor = 1 / information.freq_Hz;

    // FOR BIVARIATE GAUSSIAN
    information.mean_x = 0.0;       // Mean along the x-axis
    information.mean_y = 5.0;       // Mean along the y-axis
    information.sigma_x = 1.5;      // Standard deviation along the x-axis
    information.sigma_y = 2.0;      // Standard deviation along the y-axis

}

static void setup_bessel_and_log(int bessel, float base_log) {
    information.order_bessel = bessel;
    information.base_log = base_log;
}

#endif //WAVGENERATOR_CONSTANTS_H
