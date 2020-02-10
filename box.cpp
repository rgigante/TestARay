//
//  box.cpp
//  TraceARay
//
//  Created by Riccardo Gigante on 10/02/2020.
//

#include "box.hpp"

bool Box::Hit2 (const Ray& r, float t_min, float t_max, HitRecord& rec, bool debugRay /*= false*/)
{
	Ray ray(r);
	
	rec.mat = GetMaterial();
	
	float tminX = 0, tmaxX = 0;
	float tminY = 0, tmaxY = 0;
	float tminZ = 0, tmaxZ = 0;
	float smaller_tmax = 0, larger_tmin = 0;
	
	if (r.GetDirection().x())
	{
		float val_b = (_b.x() - r.GetOrigin().x())/r.GetDirection().x();
		float val_a = (_a.x() - r.GetOrigin().x())/r.GetDirection().x();
		tminX = val_b < val_a ? val_b : val_a;
		tmaxX = val_b >= val_a ? val_b : val_a;
	}
	else
	{
		float val_b = (_b.x() - r.GetOrigin().x())/1e-6;
		float val_a = (_a.x() - r.GetOrigin().x())/1e-6;
		tminX = val_b < val_a ? val_b : val_a;
		tmaxX = val_b >= val_a ? val_b : val_a;
	}
	
	if (r.GetDirection().y())
	{
		float val_b = (_b.y() - r.GetOrigin().y())/r.GetDirection().y();
		float val_a = (_a.y() - r.GetOrigin().y())/r.GetDirection().y();
		tminY = val_b < val_a ? val_b : val_a;
		tmaxY = val_b >= val_a ? val_b : val_a;
	}
	else
	{
		float val_b = (_b.y() - r.GetOrigin().y())/1e-6;
		float val_a = (_a.y() - r.GetOrigin().y())/1e-6;
		tminY = val_b < val_a ? val_b : val_a;
		tmaxY = val_b >= val_a ? val_b : val_a;
	}
	
	if (r.GetDirection().z())
	{
		float val_b = (_b.z() - r.GetOrigin().z())/r.GetDirection().z();
		float val_a = (_a.z() - r.GetOrigin().z())/r.GetDirection().z();
		tminZ = val_b < val_a ? val_b : val_a;
		tmaxZ = val_b >= val_a ? val_b : val_a;
	}
	else
	{
		float val_b = (_b.z() - r.GetOrigin().z())/1e-6;
		float val_a = (_a.z() - r.GetOrigin().z())/1e-6;
		tminZ = val_b < val_a ? val_b : val_a;
		tmaxZ = val_b >= val_a ? val_b : val_a;
	}
	
	if (tminX >= tminY && tminX >= tminZ)
		larger_tmin = tminX;
	if (tminY >= tminX && tminY >= tminZ)
		larger_tmin = tminY;
	if (tminZ >= tminX && tminZ >= tminY)
		larger_tmin = tminZ;
	
	if (tmaxX <= tmaxY && tmaxX <= tmaxZ)
		smaller_tmax = tmaxX;
	if (tmaxY <= tmaxX && tmaxY <= tmaxZ)
		smaller_tmax = tmaxY;
	if (tmaxZ <= tmaxX && tmaxZ <= tmaxY)
		smaller_tmax = tmaxZ;
	
	
	if (debugRay) std::cout << "\t\t\t\t- a/b: "<< _a << "/" << _b << "\n"
		<< "\t\t\t\t- c/r: "<< _c << "/" << _r << "\n"
		<< "\t\t\t\t- tmin(s):" << tminX <<", " << tminY <<", " << tminZ << "\n"
		<< "\t\t\t\t- tmax(s):" << tmaxX <<", " << tmaxY <<", " << tmaxZ << "\n"
		<< "\t\t\t\t- smaller_tmax:" << smaller_tmax <<" / larger_tmin:" << larger_tmin << "\n";
	
	// smaller_tmax > bigger_tmin
	if (smaller_tmax >= larger_tmin)
	{
		rec.t = larger_tmin;
		rec.p = ray.PointAtParameter(larger_tmin);
		if (abs(rec.p.z() - _a.z()) < 1e-6)
			rec.n = _nrms[0];
		if (abs(rec.p.z() - _b.z()) < 1e-6)
			rec.n = _nrms[1];
		if (abs(rec.p.y() - _a.y()) < 1e-6)
			rec.n = _nrms[2];
		if (abs(rec.p.y() - _b.y()) < 1e-6)
			rec.n = _nrms[3];
		if (abs(rec.p.x() - _a.x()) < 1e-6)
			rec.n = _nrms[4];
		if (abs(rec.p.x() - _b.x()) < 1e-6)
			rec.n = _nrms[5];
//		rec.n = Vec3(0,0,0);
		
		if (rec.t > t_min && rec.t < t_max)
			return true;
	}
	
	return false;
}
