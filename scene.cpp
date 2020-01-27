//
//  scene.cpp
//  TraceARay01
//
//  Created by Riccardo Gigante on 11/01/2019.
//

#include "scene.hpp"

bool Scene::Hit(const Ray &r, float t_min, float t_max, HitRecord &rec) const
{
	HitRecord tempRec;
	bool hitAnything = false;
	double closestSoFar = t_max;
	
	for (int i = 0; i < _items.size(); ++i)
	{
		if (_items[i] && _items[i]->Hit(r, t_min, closestSoFar, tempRec))
		{
			hitAnything = true;
			closestSoFar = tempRec.t;
			rec = tempRec;
		}
	}
	return hitAnything;
}

void Scene::Color(Vec3& col, Vec3& nrm, const Ray& r, int depth/* = 0*/)
{
	const float epsHit = 1e-5;
	const int maxDepth = 20;
	HitRecord rec;
	if (Hit(r, epsHit, MAXFLOAT, rec))
	{
		Ray scattered(Vec3(0, 0, 0), Vec3(0, 0, 0));
		Vec3 attenuation(0, 0, 0);
		if (depth < maxDepth && rec.mat && rec.mat->Scatter(r, rec, attenuation, scattered))
		{
			Color(col, nrm, scattered, depth + 1);
			nrm = Vec3(rec.n.x() + 1, rec.n.y() + 1, rec.n.z() + 1) * 0.5;
			col *= attenuation;
//			std::cout << "\tdepth["<<depth<<"], col["<<col<<"], nrm["<<nrm<<"], ray["<<r.GetOrigin()<<" / "<<r.GetDirection()<<"]\n";
			return;
		}
		col = Vec3(1, 1, 0);
//		std::cout << "\tdepth["<<depth<<"], col["<<col<<"], nrm["<<nrm<<"], ray["<<r.GetOrigin()<<" / "<<r.GetDirection()<<"]\n";
		return;
	}
	
	// compute the background color
	const float blend = 0.5 * (r.GetDirection().y() + 1.0);
	col = Lerp(Vec3(1.0, 1.0, 1.0), Vec3(0.5, 0.7, 1.0), blend);
	nrm = Vec3(0,0,0);
	//	std::cout << "\tdepth["<<depth<<"], col["<<col<<"], nrm["<<nrm<<"], ray["<<r.GetOrigin()<<" / "<<r.GetDirection()<<"]\n";
	return;
}


bool Scene::Render(const int samples/* = 1*/, const int activeCamIdx /* = 0*/, Framebuffer* const fb, std::ofstream& color, std::ofstream& normal)
{
	Camera* const activeCam = _cams.at(activeCamIdx);
	if (!activeCam)
		return false;
	
	const int nx = activeCam->GetXRes();
	const int ny = activeCam->GetYRes();
	
	// allocate temporary data
	int lrs = 0; //  last refreshed sample
	float u = 0, v = 0; //
	Vec3 rgb(0,0,0);
	Vec3 nrm(0,0,0);
	Ray r(Vec3 (0,0,0), Vec3(0,0,0));
	
	// loop over samples
	for (int s = 1; s < samples + 1; ++s)
	{
		std::cout << "Rendering [" << s << "/" << samples << "]\n";
		float inv_s = 1.0 / float(s);
		
		// loop over the pixels to compute their colors
		for (int j = ny - 1; j>= 0; --j)
		{
			const float inv_ny = 1.0 / float(ny);
			for (int i = 0; i < nx; ++i)
			{
				const float inv_nx = 1.0 / float(nx);
//				std::cout << "--- start pixel ["<<i<<","<<j<<"]\n";
//				u = float(i + drand48()) * inv_nx;
//				v = float(j + drand48()) * inv_ny;
				u = float(i) * inv_nx;
				v = float(j) * inv_ny;
				
				// create the starting ray from  the camera
				r = activeCam->CreateRay(u, v);
				
				// add the values returned by the ray recursively exploring the scene by hitting its items
				Color(rgb, nrm, r);
//				std::cout << "--- end pixel ["<< rgb <<"]\n";
				
				// update with color
				fb->GetColor()[j][3 * i + 0] = (fb->GetColor()[j][3 * i + 0] * ( s - 1 ) + rgb[0]) * inv_s;
				fb->GetColor()[j][3 * i + 1] = (fb->GetColor()[j][3 * i + 1] * ( s - 1 ) + rgb[1]) * inv_s;
				fb->GetColor()[j][3 * i + 2] = (fb->GetColor()[j][3 * i + 2] * ( s - 1 ) + rgb[2]) * inv_s;
				
				// update with normal
				fb->GetNormal()[j][3 * i + 0] = (fb->GetNormal()[j][3 * i + 0] * ( s - 1 ) + nrm[0]) * inv_s;
				fb->GetNormal()[j][3 * i + 1] = (fb->GetNormal()[j][3 * i + 1] * ( s - 1 ) + nrm[1]) * inv_s;
				fb->GetNormal()[j][3 * i + 2] = (fb->GetNormal()[j][3 * i + 2] * ( s - 1 ) + nrm[2]) * inv_s;
				
//				std::cout << "uv [" << u << ", " << v << "] / dir [" << r.GetDirection().x() << ", " << r.GetDirection().y() << ", " << r.GetDirection().z() << "] / col ["<< rgb[0] <<", " << ", "<< rgb[1] << ", " << rgb[2] << "]\n";

			}
		}
		
		// update the framebuffer with an incremental sample count
		if (s >= lrs * 2)
		{
			std::cout << "Spooling [" << s << "]\n";
			fb->SpoolToPPM(color, "color");
			fb->SpoolToPPM(normal, "normal");
			lrs = s;
		}
	}
	return true;
}

Scene::~Scene()
{
	// dispose cameras
	for (int i = 0; i < _cams.size(); ++i)
	{
		if (_cams.at(i))
		{
			delete (_cams.at(i));
			_cams.at(i) = nullptr;
		}
	}
	
	// dispose geometries
	for (int i = 0; i < _items.size(); ++i)
	{
		if (_items.at(i))
		{
			delete (_items.at(i));
			_items.at(i) = nullptr;
		}
	}
	
	// dispose materials
	for (int i = 0; i < _materials.size(); ++i)
	{
		if (_materials.at(i))
		{
			delete (_materials.at(i));
			_materials.at(i) = nullptr;
		}
	}
}
