//
//  framebuffer.hpp
//  TraceARay01
//
//  Created by Riccardo Gigante on 13/01/2019.
//

#ifndef framebuffer_hpp
#define framebuffer_hpp

#include <stdint.h>
#include "main.hpp"

class Framebuffer
{
public:
	Framebuffer(int xRes, int yRes, int chans);
	~Framebuffer();
	float** GetColor(){ return _color; }
	float** GetNormal(){ return _normal; }
	float** GetObjectID(){ return _objectID; }
	float** GetDepth(){ return _depth; }
	void SetZDepthExtremes(float val)
	{
		if (val <= 1e-6) return;
		val > _maxZDepth ? _maxZDepth = val : _maxZDepth;
		val < _minZDepth ? _minZDepth = val : _minZDepth;
		return;
	}
	bool GetXRes(){ return _xRes; }
	bool GetYRes(){ return _yRes; }
	bool SpoolToPPM(std::ofstream * of, const char* type);
	
private:
	float** _color = nullptr;
	float** _normal = nullptr;
	float** _objectID = nullptr;
	float** _depth = nullptr;
	int _xRes = 0, _yRes = 0, _nChans = 0;
	float _minZDepth = MAXFLOAT, _maxZDepth = -MAXFLOAT;
};

#endif /* framebuffer_hpp */
