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
#include "framebuffer.hpp"
#include "materials.hpp"
#include <vector>

class Scene
{
public:
	Scene(){}
	~Scene();
	
	void AddItem(Hitable* item) { if (item) _items.push_back(item); }
	
	void AddMaterial(Material* material) { if(material) _materials.push_back(material); }
	
	void AddCamera(Camera* cam){ if (cam) _cams.push_back(cam); }
	Camera* GetCamera(const int i){ return _cams.at(i); }
	
	bool Render(const int samples, const int activeCamIdx, Framebuffer* const fb, std::ofstream& color, std::ofstream& normal);
	bool Hit (const Ray& r, float t_min, float t_max, HitRecord& rec, bool debugRay = false) const;
	void Color(Vec3& col, Vec3& nrm, const Ray& r, int depth = 0);
	
	void DebugColor(Vec3& col, const Ray& r, int depth = 0, const bool debugRay = false);
	bool ColorPixel(const int x = 1, const int y = 1, const int activeCamIdx = 0, const bool debugRay = false);
	
	
	
private:
	std::vector<Hitable*> _items;
	std::vector<Material*> _materials;
	std::vector<Camera*> _cams;
	
	float _epsHit = 1e-5;
	int _maxDepth = 20;
};

#endif /* scene_hpp */
