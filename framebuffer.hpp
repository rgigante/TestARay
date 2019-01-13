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
	float** GetFloatRGB(){ return _fb; }
//	uint8_t** GetUInt8RGB(){};
//	bool ConvertFloatToUInt8(){};
	bool GetXRes(){ return _xRes; }
	bool GetYRes(){ return _yRes; }
	bool SpoolToPPM(std::ofstream& of);
	
private:
	float** _fb;
	int _xRes, _yRes, _nChans;
};

#endif /* framebuffer_hpp */
