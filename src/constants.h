//
// Created by saintedlittle on 24.07.2023.
//

#ifndef WAVGENERATOR_CONSTANTS_H
#define WAVGENERATOR_CONSTANTS_H

// FOR MATH

#ifdef WIN32
#include <corecrt_math.h>

#define M_PI acos(-1.0)
#else
#include <math.h>
#endif

#define S_RATE  (44100)
#define BUF_SIZE (S_RATE*10) /* 2 second buffer */


#endif //WAVGENERATOR_CONSTANTS_H
