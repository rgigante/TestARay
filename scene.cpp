//
//  scene.cpp
//  TraceARay01
//
//  Created by Riccardo Gigante on 11/01/2019.
//

#include "scene.hpp"

void Scene::AddItem(Hitable* item)
{
	if (item)
	{
		// on adding an item just set its objID based on the number of items already added
		item->SetObjID(_items.size());
		
		// add the item
		_items.push_back(item);
	}
}

void Scene::InitObjIDColors()
{
	// resize the objectID colors based on the number of items in the scene
	_objIDcolors.resize(_items.size());
	
	// define for each entry a random color
	for (unsigned long i  = 0; i < _items.size(); i++)
		_objIDcolors[i] = Vec3 (drand48(), drand48(), drand48());

	return;
}

bool Scene::Hit(const Ray &r, float t_min, float t_max, HitRecord &rec, bool debugRay /*= false*/) const
{
	HitRecord tempRec;
	bool hitAnything = false;
	double closestSoFar = t_max;
	for (int i = 0; i < _items.size(); ++i)
	{
		Hitable* currentItem = _items[i];
		if (currentItem)
		{
			bool hitCheck = currentItem->Hit(r, t_min, closestSoFar, tempRec, debugRay);
			if (hitCheck)
			{
				if (debugRay) std::cout << "\t\t- intersecting: " << currentItem->GetName() << " - " << tempRec << "\n";
				hitAnything = true;
				closestSoFar = tempRec.t;
				rec = tempRec;
			}
			else
				if (debugRay) std::cout << "\t\t- intersecting: " << currentItem->GetName() << " - NO intersection \n";
		}
	}
	return hitAnything;
}

void Scene::Color(Vec3& col, Vec3& nrm, Vec3& objID, const Ray& r, int depth/* = 0*/)
{
	HitRecord rec;
	const bool isHit = Hit(r, _epsHit, MAXFLOAT, rec);
	if (isHit)
	{
		Ray scattered(Vec3(0, 0, 0), Vec3(0, 0, 0));
		Vec3 attenuation(0, 0, 0);
		Vec3 emission(0, 0, 0);
		
		const bool isBelowMaxDepth = depth < _maxDepth;
		bool isScattered = false;
		bool isEmitted = false;
		
		if (isBelowMaxDepth)
		{
			if (rec.mat)
			{
				isEmitted = rec.mat->Emission(r, rec, emission);
				isScattered = rec.mat->Scatter(r, rec, attenuation, scattered);
				
				if (isScattered && isEmitted)
				{
					Color(col, nrm, objID, scattered, depth + 1);
					
					// calculate attenuation
					col = (col * attenuation) + emission;
				}
				else if(isEmitted)
				{
					col = emission;
				}
				else
				{
					// color value (YELLOW) assigned for debugging scope
					col = Vec3(1, 1, 0);
				}
				
				if (depth == 0)
				{
					// calculate normal
					nrm = Vec3(rec.n.x() + 1, rec.n.y() + 1, rec.n.z() + 1) * 0.5;
					// calculate objID
					objID = _objIDcolors[rec.objID];
				}
				
				return;
			}
		}
	}
	
	Environment* env = GetEnvironment(0);
	if (env)
		col = env->Col(r);
	else
		col = Vec3(0,0,0);
	
	if (depth == 0)
	{
		nrm = Vec3(0,0,0);
		objID = Vec3(0,0,0);
	}
	
	return;
}

void Scene::DebugColor(Vec3& col, const Ray& r, int depth/* = 0*/, const bool debugRay /*= false*/)
{
	HitRecord rec;
	std::cout << "\t- ray["<<r<<"]\n";
	std::cout << "\t\t- depth["<<depth<<"]\n\t\t- col["<<col<<"]\n";
	const bool isHit = Hit(r, _epsHit, MAXFLOAT, rec, debugRay);
	if (isHit)
	{
		Ray scattered(Vec3(0, 0, 0), Vec3(0, 0, 0));
		Vec3 attenuation(0, 0, 0);
		Vec3 emission (0, 0, 0);
		
		const bool isBelowMaxDepth = depth < _maxDepth;
		bool isScattered = false;
		bool isEmitted = false;
		
		if (isBelowMaxDepth)
		{
			if (rec.mat)
			{
				isScattered = rec.mat->Scatter(r, rec, attenuation, scattered);
				isEmitted = rec.mat->Emission(r, rec, emission);
				std::cout << "\t\t- scatter["<<scattered<<"]\n\t\t- atten["<<attenuation<<"]\n" << "\t\t- emission["<<emission<<"]\n";
				if (isScattered && isEmitted)
				{
					DebugColor(col, scattered, depth + 1, debugRay);
					col = (col * attenuation) + emission;
					return;
				}
				else if(isEmitted)
				{
					col = emission;
					return;
				}
				else
				{
					col = Vec3(0,0,0);
					return;
				}
			}
		}
		
		// color value (YELLOW) assigned for debugging scope
		col = Vec3(1, 1, 0);
		return;
	}
	
	Environment* env = GetEnvironment(0);
	if (env)
		col = env->Col(r);
	
	return;
}

bool Scene::RenderPixel(const int xPix/* = 1*/, const int yPix/* = 1*/, const int activeCamIdx /* = 0*/, const bool debugRay /*= false*/)
{
	Camera* const activeCam = _cams.at(activeCamIdx);
	if (!activeCam)
		return false;
	
	const int nx = activeCam->GetXRes();
	const int ny = activeCam->GetYRes();
	
	// allocate temporary data
	Vec3 rgb(0,0,0);
	Vec3 nrm(0,0,0);
	Vec3 objID(0,0,0);
	Ray r(Vec3 (0,0,0), Vec3(0,0,0));
	
	const int x = xPix;
	const int y = yPix;

	const float inv_ny = 1.0 / float(ny - 1);
	const float inv_nx = 1.0 / float(nx - 1);
	const float u = float(x) * inv_nx;
	const float v = float(y) * inv_ny;
	std::cout << "--- start pixel ["<<x<<" ("<<u<<"), "<<y<<" ("<<v<<")]\n";

	// create the starting ray from  the camera
	r = activeCam->CreateRay(u, v);

	// add the values returned by the ray recursively exploring the scene by hitting its items
	DebugColor(rgb, r, 0, debugRay);
	Color(rgb, nrm, objID, r);
	std::cout << "--- end pixel ["<< rgb <<"],  ["<< nrm <<"],  ["<< objID <<"]\n\n";
	
	return true;
}

bool Scene::Render(const int samples/* = 1*/, const int activeCamIdx /* = 0*/, Framebuffer* const fb, std::ofstream * color, std::ofstream * normal, std::ofstream * objectID)
{
	Camera* const activeCam = _cams.at(activeCamIdx);
	if (!activeCam)
		return false;
	
	const int nx = activeCam->GetXRes();
	const int ny = activeCam->GetYRes();
	
	// allocate temporary data
	int lrs = 0; //  last refreshed sample
	float u = 0, v = 0;
	Vec3 rgb(0,0,0);
	Vec3 nrm(0,0,0);
	Vec3 objID(0,0,0);
	Ray r(Vec3 (0,0,0), Vec3(0,0,0));
	
	// loop over samples
	for (int s = 1; s < samples + 1; ++s)
	{
		std::cout << "Rendering [" << s << "/" << samples << "]\n";
		const float inv_s = 1.0 / float(s);
		
		// loop over the pixels to compute their colors
		for (int j = ny - 1; j >= 0; --j)
		{
			const float inv_ny = 1.0 / float(ny - 1);
			for (int i = 0; i < nx; ++i)
			{
				const float inv_nx = 1.0 / float(nx - 1);
//				u = float(i + drand48()) * inv_nx;
//				v = float(j + drand48()) * inv_ny;
				u = float(i) * inv_nx;
				v = float(j) * inv_ny;
				
//				std::cout << "--- start pixel ["<<i<<" ("<<u<<"), "<<j<<" ("<<v<<")]\n";
				
				// create the starting ray from  the camera
				r = activeCam->CreateRay(u, v);
				
				// add the values returned by the ray recursively exploring the scene by hitting its items
				Color(rgb, nrm, objID, r);
//				std::cout << " col["<< rgb <<"]\n";
				
				// update with color
				fb->GetColor()[j][3 * i + 0] = (fb->GetColor()[j][3 * i + 0] * ( s - 1 ) + rgb[0]) * inv_s;
				fb->GetColor()[j][3 * i + 1] = (fb->GetColor()[j][3 * i + 1] * ( s - 1 ) + rgb[1]) * inv_s;
				fb->GetColor()[j][3 * i + 2] = (fb->GetColor()[j][3 * i + 2] * ( s - 1 ) + rgb[2]) * inv_s;
				
				// update with normal
				fb->GetNormal()[j][3 * i + 0] = (fb->GetNormal()[j][3 * i + 0] * ( s - 1 ) + nrm[0]) * inv_s;
				fb->GetNormal()[j][3 * i + 1] = (fb->GetNormal()[j][3 * i + 1] * ( s - 1 ) + nrm[1]) * inv_s;
				fb->GetNormal()[j][3 * i + 2] = (fb->GetNormal()[j][3 * i + 2] * ( s - 1 ) + nrm[2]) * inv_s;
				
				// update with objectID
				fb->GetObjectID()[j][3 * i + 0] = (fb->GetObjectID()[j][3 * i + 0] * ( s - 1 ) + objID[0]) * inv_s;
				fb->GetObjectID()[j][3 * i + 1] = (fb->GetObjectID()[j][3 * i + 1] * ( s - 1 ) + objID[1]) * inv_s;
				fb->GetObjectID()[j][3 * i + 2] = (fb->GetObjectID()[j][3 * i + 2] * ( s - 1 ) + objID[2]) * inv_s;
				
//				std::cout << "uv [" << u << ", " << v << "] / dir [" << r.GetDirection().x() << ", " << r.GetDirection().y() << ", " << r.GetDirection().z() << "] / col ["<< rgb[0] <<", " << ", "<< rgb[1] << ", " << rgb[2] << "]\n";

			}
		}
		
		// update the framebuffer with an incremental sample count
		if (s >= lrs * 2)
		{
			std::cout << "Spooling [" << s << "]\n";
			if (color)
				fb->SpoolToPPM(color, "color");
			if (normal)
				fb->SpoolToPPM(normal, "normal");
			if (objectID)
				fb->SpoolToPPM(objectID, "objectID");
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
