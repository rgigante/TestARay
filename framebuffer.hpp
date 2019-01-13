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
//	uint8_t** GetUInt8RGB(){};
//	bool ConvertFloatToUInt8(){};
	bool GetXRes(){ return _xRes; }
	bool GetYRes(){ return _yRes; }
	bool SpoolToPPM(std::ofstream& of, const char* type);
	
private:
	float** _color;
	float** _normal;
	int _xRes, _yRes, _nChans;
};

#endif /* framebuffer_hpp */
