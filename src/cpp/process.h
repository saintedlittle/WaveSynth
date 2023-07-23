#ifndef __PROCESS__
#define __PROCESS__

#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

#include "bitmap_image.cpp"

class Process {

	private:

		std::string _filename;

		bitmap_image* _image;

		double* _audioData;
		int _audioSize;

		double _width, _height;

		double _sampleRate;
		double _dt, _df;
		double _tmax, _fmax;
	public:

		Process(std::string file);

		void LoadImage();
		void WriteAudio();
		void Convert();
		void SetPixel(int x, int y, double value); 
};

#endif

