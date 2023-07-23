#ifndef MAKE_WAV_H
#define MAKE_WAV_H
 
void write_wav(char * filename, unsigned long num_samples, short int * data, int s_rate);

double d_random(double min, double max);

#endif
