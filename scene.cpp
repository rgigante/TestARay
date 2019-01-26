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

Scene::~Scene()
{
	// dispose camera
	delete _cam;
	_cam = nullptr;
	
	// dispose geometries
	for (int i = 0; i < _items.size(); ++i)
	{
		delete (_items.at(i));
		_items.at(i) = nullptr;
	}
}
