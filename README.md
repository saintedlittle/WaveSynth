Title: "WaveSynth - A Sound and Image Generation Project"

## Overview

Welcome to WaveSynth, a versatile project that combines sound and image generation using various mathematical functions and noise algorithms. This README.md file provides an overview of the project, its components, and how to get started.

## Project Description

WaveSynth is a C-based project designed to explore the creative possibilities of sound and image synthesis. It offers a wide range of features, including wave generation, noise algorithms, mathematical functions, and melody generation. With WaveSynth, you can create unique audiovisual experiences, experiment with different soundscapes, and generate captivating melodies.

## Features

- **Wave Generation**: WaveSynth allows you to create square, sawtooth, and triangle waves with adjustable amplitudes and frequencies.

- **Mathematical Functions**: Explore a variety of mathematical functions, including sinusoids, complex sinusoids, decay envelopes, musical chords, chirps, bivariate Gaussians, Bessel functions, and logarithmic functions.

- **Noise Generation**: Generate noise with different characteristics, such as default noise, simplex noise, gradient noise, and pink noise. You can control the amplitude and frequency of the noise.

- **Melody Generation**: WaveSynth can also create melodies, including a melody based on the golden ratio and a purer melody with customizable parameters.

- **Image Generation (Commented Out)**: Although the code for image generation is currently commented out, you can use it to create images based on the generated waves and noises.

## Getting Started

To get started with WaveSynth, follow these steps:

1. Clone the project repository to your local machine.

2. Compile the code using a C compiler (e.g., GCC) by running `gcc main.c -o wavesynth -lm -fopenmp` if you have OpenMP support.

3. Run the executable by executing `./wavesynth`.

4. The program will generate waves, mathematical functions, and noise according to the specified parameters. By default, it will print the calculated golden ratio and generate a melody as a WAV file.

5. Optionally, you can uncomment the code to generate images and use the `write_bmp` function to save them.

## Configuration

- Adjust the parameters in the `main` function to customize the generated waves, mathematical functions, and noise.

- Modify the `generate_melody` and `generate_purer_melody` functions to create melodies with specific characteristics.

## Dependencies

- This project uses the C standard library and, optionally, OpenMP for parallel processing.

## Contributing

We welcome contributions to the WaveSynth project. Feel free to submit pull requests, report issues, or suggest enhancements.

## License

WaveSynth is open-source software released under the [MIT License](https://github.com/saintedlittle/wav-funning/blob/main/LICENSE).

## Acknowledgments

We would like to thank the open-source community for their contributions to the libraries and tools used in this project.

## Contact

For questions or feedback, please contact saintedlittle at fetik228zxc@gmail.com.

Enjoy exploring the creative possibilities of WaveSynth!