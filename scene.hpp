//
//  scene.hpp
//  TraceARay01
//
//  Created by Riccardo Gigante on 11/01/2019.
//

#ifndef scene_hpp
#define scene_hpp

#include "hitable.hpp"
#include "camera.hpp"
#include <vector>

class Scene
{
public:
	Scene(){}
	~Scene();
	void AddItem(Hitable* item) { _items.push_back(item); }
	bool Hit (const Ray& r, float t_min, float t_max, HitRecord& rec) const;
	void AddCamera(Camera* cam){ if (cam) _cam = cam; }
	Camera* GetCamera(){ return _cam; }
	
private:
	std::vector<Hitable*> _items;
	Camera* _cam;
};

#endif /* scene_hpp */
