//
// Created by saintedlittle on 27.07.2023.
//

#ifndef WAVGENERATOR_BIG_DOUBLE_H
#define WAVGENERATOR_BIG_DOUBLE_H

#define BUFFER_SIZE 10000000

typedef struct {
    unsigned char data[128]; // 1024 bits / 8 bits per char = 128 bytes
} MyDouble;

// Function to initialize MyDouble with a given value (not implemented for simplicity)
void my_double_init(MyDouble *number, double value);

// Function to write MyDouble to a memory buffer
void my_double_write_to_buffer(const MyDouble *number, unsigned char *buffer);

// Function to read MyDouble from a memory buffer
void my_double_read_from_buffer(MyDouble *number, const unsigned char *buffer);

void print_my_double(const MyDouble *number);

// Function to convert double to MyDouble
MyDouble my_double_from_double(double value);

// Function to add two MyDouble numbers
MyDouble my_double_add(const MyDouble *a, const MyDouble *b);

// Function to divide two MyDouble numbers
MyDouble my_double_divide(const MyDouble *a, const MyDouble *b);

// Function to read the first MyDouble result from the binary file
MyDouble read_first_result_from_file(const char *filename);

// Function to read the last MyDouble result from the binary file
MyDouble read_last_result_from_file(const char *filename, int num_results);

#endif //WAVGENERATOR_BIG_DOUBLE_H
