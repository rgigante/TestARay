//
//  framebuffer.cpp
//  TraceARay01
//
//  Created by Riccardo Gigante on 13/01/2019.
//

#include "framebuffer.hpp"


Framebuffer::Framebuffer(int xRes, int yRes, int chans):_xRes(xRes), _yRes(yRes), _nChans(chans)
{
	_color = nullptr;
	_normal = nullptr;
	_objectID = nullptr;
	
	if (_xRes == 0 || _yRes == 0)
		return;
	
	_color = new float* [_yRes];
	_normal = new float* [_yRes];
	_objectID = new float* [_yRes];
	
	if (_color || !_normal || !_objectID)
	{
		for (int i = 0; i < _yRes; ++i)
		{
			_color[i] = new float[_xRes * _nChans];
			_normal[i] = new float[_xRes * _nChans];
			_objectID[i] = new float[_xRes * _nChans];
		}
	}
}

Framebuffer::~Framebuffer()
{
	if (!_color ||
		!_normal ||
		!_objectID)
		return;
	
	for (int i = 0; i < _yRes; ++i)
	{
		delete[] _color[i];
		delete[] _normal[i];
		delete[] _objectID[i];
		_color[i] = nullptr;
		_normal[i] = nullptr;
		_objectID[i] = nullptr;
	}
	
	delete[] _color;
	delete[] _normal;
	delete[] _objectID;
	_color = nullptr;
	_normal = nullptr;
	_objectID = nullptr;
}

bool Framebuffer::SpoolToPPM(std::ofstream * of, const char* type)
{
	of->seekp(0);
	
	// write the image header
	*of << "P3\n" << _xRes << " " << _yRes << "\n255\n";
	
	if (!_color || !_normal)
		return false;
	
	Vec3 col (0,0,0);
	
	for (int j = _yRes - 1; j>= 0; --j)
	{
		for (int i = 0; i < _xRes; ++i)
		{
			if (_nChans == 3)
			{
				if (strcmp(type, "color") == 0)
				{
					// apply some "minimal" gamma correction (gamma 2 -> x^1/2)
					*of << int(255.99 * sqrt(_color[j][3 * i + 0])) << " " <<  int(255.99 * sqrt(_color[j][3 * i + 1])) << " " << int(255.99 * sqrt(_color[j][3 * i + 2])) << "\n";
				}
				if (strcmp(type, "normal") == 0)
				{
					*of << int(255.99 * _normal[j][3 * i + 0]) << " " <<  int(255.99 * _normal[j][3 * i + 1]) << " " << int(255.99 * _normal[j][3 * i + 2]) << "\n";
				}
				if (strcmp(type, "objectID") == 0)
				{
					*of << int(255.99 * _objectID[j][3 * i + 0]) << " " <<  int(255.99 * _objectID[j][3 * i + 1]) << " " << int(255.99 * _objectID[j][3 * i + 2]) << "\n";
				}
			}
		}
	}
	
	of->flush();
	
	return true;
}
