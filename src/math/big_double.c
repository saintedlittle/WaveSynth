#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

void my_double_init(MyDouble *number, double value) {
    // Convert the 'value' to the internal representation (two's complement)

    // Get the pointer to the double value
    unsigned char *doubleData = (unsigned char *)&value;

    // Copy the double value bytes to the MyDouble data array
    for (int i = 0; i < sizeof(double); i++) {
        number->data[i] = doubleData[i];
    }

    // Set the remaining bytes to 0 (if MyDouble is larger than double)
    for (int i = sizeof(double); i < sizeof(number->data); i++) {
        number->data[i] = 0;
    }
}


void my_double_write_to_buffer(const MyDouble *number, unsigned char *buffer) {
    memcpy(buffer, number->data, sizeof(number->data));
}

void my_double_read_from_buffer(MyDouble *number, const unsigned char *buffer) {
    memcpy(number->data, buffer, sizeof(number->data));
}

// Function to print MyDouble to the console
//void print_my_double(const MyDouble *number) {
//    printf("MyDouble value: ");
//    for (int i = 0; i < sizeof(number->data); i++) {
//        printf("%02X", number->data[i]);
//    }
//    printf("\n");
//}

void print_my_double(const MyDouble *number) {
    printf("MyDouble value (decimal): ");
    // Flag to ignore leading zeros
    int ignore_zeros = 1;

    // Loop through each byte and print each decimal digit
    for (int i = 0; i < sizeof(number->data); i++) {
        unsigned char byte = number->data[i];
        int base = 100;
        // Process each decimal digit in the byte
        for (int j = 0; j < 2; j++) {
            unsigned char digit = byte / base;
            byte -= digit * base;
            base /= 10;
            // Check if it's a leading zero and whether to ignore it
            if (digit != 0 || !ignore_zeros) {
                printf("%u", digit);
                ignore_zeros = 0;
            }
        }
    }

    // Handle the case where the MyDouble value is zero
    if (ignore_zeros)
        printf("0");

    printf("\n");
}

MyDouble my_double_from_double(double value) {
    MyDouble result;
    my_double_init(&result, value);
    return result;
}

MyDouble my_double_add(const MyDouble *a, const MyDouble *b) {
    MyDouble result;
    unsigned char carry = 0;

    for (int i = sizeof(result.data) - 1; i >= 0; i--) {
        unsigned char sum = a->data[i] + b->data[i] + carry;
        result.data[i] = sum;
        carry = (sum < a->data[i] || sum < b->data[i]) ? 1 : 0;
    }

    return result;
}

MyDouble my_double_divide(const MyDouble *a, const MyDouble *b) {
    MyDouble result;

    // Check if 'b' is zero, return NaN (not a number) in such case
    for (int i = 0; i < sizeof(result.data); i++) {
        if (b->data[i] != 0) {
            // 'b' is not zero
            break;
        }
        if (i == sizeof(result.data) - 1) {
            // 'b' is zero, division by zero
            unsigned char nanValue[sizeof(double)] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
            memcpy(result.data, nanValue, sizeof(result.data));
            return result;
        }
    }

    // Initialize the result to zero
    memset(result.data, 0, sizeof(result.data));

    // Perform long division
    MyDouble dividend;
    memcpy(dividend.data, a->data, sizeof(dividend.data));

    for (int i = 0; i < 8 * sizeof(result.data); i++) {
        // Shift the dividend left by 1 bit
        for (int j = 0; j < sizeof(result.data) - 1; j++) {
            dividend.data[j] = (dividend.data[j] << 1) | (dividend.data[j + 1] >> 7);
        }
        dividend.data[sizeof(result.data) - 1] <<= 1;

        // Compare the dividend with the divisor (b)
        int cmp = memcmp(dividend.data, b->data, sizeof(result.data));

        // If dividend >= divisor, subtract and set the corresponding bit in the result
        if (cmp >= 0) {
            for (int j = sizeof(result.data) - 1; j >= 0; j--) {
                unsigned char diff = dividend.data[j] - b->data[j];
                if (dividend.data[j] >= b->data[j]) {
                    result.data[j] |= 1;
                    dividend.data[j] = diff;
                } else {
                    unsigned char borrow = 0;
                    if (j > 0) {
                        borrow = 1;
                    }
                    unsigned char borrowFrom = dividend.data[j - 1] - borrow;
                    dividend.data[j] = 256 + dividend.data[j] - b->data[j];
                    dividend.data[j - 1] = borrowFrom;
                }
            }
        }
        // Shift the result left by 1 bit
        for (int j = 0; j < sizeof(result.data) - 1; j++) {
            result.data[j] = (result.data[j] << 1) | (result.data[j + 1] >> 7);
        }
        result.data[sizeof(result.data) - 1] <<= 1;
    }

    return result;
}

MyDouble read_first_result_from_file(const char *filename) {
    MyDouble result;
    FILE *file = fopen(filename, "rb");

    unsigned char buffer[128];


    if (file == NULL) {
        printf("Error opening file: %s\n", filename);
        return result;
    }

    if (fread(buffer, sizeof(unsigned char), sizeof(MyDouble), file) == sizeof(MyDouble)) {
        my_double_read_from_buffer(&result, buffer);
    }

    fclose(file);
    return result;
}

MyDouble read_last_result_from_file(const char *filename, int num_results) {
    MyDouble result;
    FILE *file = fopen(filename, "rb");

    unsigned char buffer[128];

    if (file == NULL) {
        printf("Error opening file: %s\n", filename);
        return result;
    }

    fseek(file, -(long)(sizeof(MyDouble)), SEEK_END);
    if (fread(buffer, sizeof(unsigned char), sizeof(MyDouble), file) == sizeof(MyDouble)) {
        my_double_read_from_buffer(&result, buffer);
    }

    fclose(file);
    return result;
}

//int main() {
//    // Allocate memory for the MyDouble object (10000000 bytes)
//    MyDouble *myDouble = (MyDouble *)malloc(BUFFER_SIZE);
//
//    // Use the function to initialize MyDouble with a double value
//    double value = 3.14;
//    my_double_init(myDouble, value);
//
//    // Output the MyDouble number to the console
//    print_my_double(myDouble);
//
//    return EXIT_SUCCESS;
//}
