//
//  framebuffer.cpp
//  TraceARay01
//
//  Created by Riccardo Gigante on 13/01/2019.
//

#include "framebuffer.hpp"
#include "utils.hpp"

Framebuffer::Framebuffer(int xRes, int yRes, int chans):_xRes(xRes), _yRes(yRes), _nChans(chans)
{
	_color = nullptr;
	_normal = nullptr;
	_objectID = nullptr;
	_depth = nullptr;
	
	if (_xRes == 0 || _yRes == 0)
		return;
	
	_color = new float* [_yRes];
	_normal = new float* [_yRes];
	_objectID = new float* [_yRes];
	_depth = new float* [_yRes];
	
	for (int i = 0; i < _yRes; ++i)
	{
		if (_color)
			_color[i] = new float[_xRes * _nChans];
		if (_normal)
			_normal[i] = new float[_xRes * _nChans];
		if (_objectID)
			_objectID[i] = new float[_xRes * _nChans];
		if (_depth)
			_depth[i] = new float[_xRes];
	}
}

Framebuffer::~Framebuffer()
{
	for (int i = 0; i < _yRes; ++i)
	{
		if (_color)
		{
			delete[] _color[i];
			_color[i] = nullptr;
		}
		if (_normal)
		{
			delete[] _normal[i];
			_normal[i] = nullptr;
		}
		if (_objectID)
		{
			delete[] _objectID[i];
			_objectID[i] = nullptr;
		}
		if (_depth)
		{
			delete[] _depth[i];
			_depth[i] = nullptr;
		}
	}
	if (_color)
	{
		delete[] _color;
		_color = nullptr;
	}
	
	if (_normal)
	{
		delete[] _normal;
		_normal = nullptr;
	}
	
	if (_objectID)
	{
		delete[] _objectID;
		_objectID = nullptr;
	}
	
	if (_depth)
	{
		delete[] _depth;
		_depth = nullptr;
	}
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
					// added support to clip between 0 and 1 to allow emitters to work properly
					*of << int(255.99 * clip(float(sqrt(_color[j][3 * i + 0])), float(0.0), float(1.0))) << " " <<  int(255.99 * clip(float(sqrt(_color[j][3 * i + 1])), float(0.0), float(1.0))) << " " << int(255.99 * clip(float(sqrt(_color[j][3 * i + 2])), float(0.0), float(1.0))) << "\n";
				}
				if (strcmp(type, "normal") == 0)
				{
					*of << int(255.99 * _normal[j][3 * i + 0]) << " " <<  int(255.99 * _normal[j][3 * i + 1]) << " " << int(255.99 * _normal[j][3 * i + 2]) << "\n";
				}
				if (strcmp(type, "objectID") == 0)
				{
					*of << int(255.99 * _objectID[j][3 * i + 0]) << " " <<  int(255.99 * _objectID[j][3 * i + 1]) << " " << int(255.99 * _objectID[j][3 * i + 2]) << "\n";
				}
				if (strcmp(type, "depth") == 0)
				{
					const float normalizedZVal = _depth[j][i] / (_maxZDepth - _minZDepth);
					*of << int(255.99 * normalizedZVal) << " " <<  int(255.99 * normalizedZVal) << " " << int(255.99 * normalizedZVal) << "\n";
				}
			}
		}
	}
	
	of->flush();
	
	return true;
}
