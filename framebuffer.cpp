//
//  framebuffer.cpp
//  TraceARay01
//
//  Created by Riccardo Gigante on 13/01/2019.
//

#include "framebuffer.hpp"


Framebuffer::Framebuffer(int xRes, int yRes, int chans):_xRes(xRes), _yRes(yRes), _nChans(chans)
{
	_fb = nullptr;
	
	if (_xRes == 0 || _yRes == 0)
		return;
	
	_fb = new float* [_yRes];
	if (_fb)
	{
		for (int i = 0; i < _yRes; ++i)
		{
			_fb[i] = new float[_xRes * _nChans];
		}
	}
}

Framebuffer::~Framebuffer()
{
	if (!_fb)
		return;
	
	for (int i = 0; i < _yRes; ++i)
	{
		delete[] _fb[i];
		_fb[i] = nullptr;
	}
	
	delete[] _fb;
	_fb = nullptr;
}

bool Framebuffer::SpoolToPPM(std::ofstream& of)
{
	of.seekp(0);
	
	// write the image header
	of << "P3\n" << _xRes << " " << _yRes << "\n255\n";
	
	if (!_fb)
		return false;
	
	Vec3 col (0,0,0);
	
	for (int j = _yRes - 1; j>= 0; --j)
	{
		for (int i = 0; i < _xRes; ++i)
		{
			if (_nChans == 3)
			{
				col[0] = _fb[j][3 * i + 0];
				col[1] = _fb[j][3 * i + 1];
				col[2] = _fb[j][3 * i + 2];
				
				// apply some "minimal" gamma correction (gamma 2 -> x^1/2)
				of << int(255.99 * sqrt(_fb[j][3 * i + 0])) << " " <<  int(255.99 * sqrt(_fb[j][3 * i + 1])) << " " << int(255.99 * sqrt(_fb[j][3 * i + 2])) << "\n";
			}
		}
	}
	
	of.flush();
	
	return true;
}
