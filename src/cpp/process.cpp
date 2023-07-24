#include "process.h"

#include "../constants.h"

using namespace std;

Process::Process(string file) {

	_filename = file;

	_image = new bitmap_image(_filename);

	_tmax = 9;
	_fmax = 8000;

	_dt = _tmax/_image->width();	// second
	_df = _fmax/_image->height();	// hertz

	_audioSize = (int)(_tmax+1.)*44100;
	_audioData = new double[_audioSize];
}

void Process::Convert() {

	unsigned char r,g,b;
	double value;


		double min, max, factorA, factorB;
	for (unsigned int x(0); x < _image->width(); x++) {
		for (unsigned int y(0); y < _image->height(); y++) {
			value = (r+g+b)/3./255.;
			if (value < min) { min = value; }
			if (value > max) { max = value; }	
		}		
	}
	factorA = 1./(double)(max-min);
	factorB = 1.-max*factorA;

	for (unsigned int x(0); x < _image->width(); x++) {

	cout << "Processing " << _filename << " ..." << round((double)x/_image->width()*100) << "%     \r";

		for (unsigned int y(0); y < _image->height(); y++) {
		
			_image->get_pixel(x,y,r,g,b);
			
			value = (r+g+b)/3./255.;
			SetPixel(x,y,value);
		}		
	}
	cout << "Processing " << _filename << " ...done" << endl;
}


void Process::WriteAudio() {


	_filename.resize(_filename.find('.'));
	_filename += ".wav";

	cout << "Writing " << _filename << endl;
    
    ofstream file(_filename.c_str(), ios::out | ios::binary);
    
    unsigned char header[44] = { 0x52,0x49,0x46,0x46,
                        0x54,0x13,0x08,0x00,
                        0x57,0x41,0x56,0x45,
                        0x66,0x6d,0x74,0x20,
                        0x10,0x00,0x00,0x00,
                        0x01,0x00,0x01,0x00,
                        0x44,0xac,0x00,0x00,
                        0x10,0xb1,0x02,0x00,
                        0x04,0x00,0x20,0x00,
                        0x64,0x61,0x74,0x61,
                        0x00,0x00,0x00,0x00};



    int value(_audioSize*4);
    header[40] = value/0x1000000;
    header[41] = value%0x1000000/0x10000;
    header[42] = value%0x10000/0x100;
    header[43] = value%0x100/0x1;

    file.write((const char*)header,44);

	char* out = new char[value];

        for (int i(0); i < _audioSize; i++) {

                value = round(_audioData[i]);

                out[4*i+3] = value/0x1000000;
                out[4*i+2] = value%0x1000000/0x10000;
                out[4*i+1] = value%0x10000/0x100;
                out[4*i+0] = value%0x100/0x1;
        }

	file.write(out,_audioSize*4);
	
}


void Process::SetPixel(int x, int y, double value) {

	int index = x*_dt*44100;
	double freq = (_image->width()-y)*_fmax/(_image->width()+0.);

	int sample_size = _dt*44100;

//  cout << freq << "\t" << x << "\t" << y << endl;

	for (int i(index); i < (index+sample_size); i++) {
		
		_audioData[i] += sin(2*M_PI*(double)i/44100.*freq)*1e7*value;
//		_audioData[i] += sin(2*M_PI*(double)i/44100.*freq)*1e8*value*exp(-1e-6*pow(i-(index+sample_size*0.5),2));

//		cout << _audioData[i] << endl;
	}
}

