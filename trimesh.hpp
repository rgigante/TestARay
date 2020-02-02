//
//  trimesh.hpp
//  TraceARay01
//
//  Created by Riccardo Gigante on 10/01/2019.
//

#ifndef trimesh_hpp
#define trimesh_hpp

#include "matrix.hpp"
#include "triangle.hpp"

class TriMesh: public Hitable
{
public:
	TriMesh(char const * name, int trisCnt, Material const * mat);
	~TriMesh();
	bool Hit2 (const Ray& r, float t_min, float t_max, HitRecord& rec, bool debugRay = false);
	
	bool SetVertexes(Vec3* points, int pointsCnt);
	bool SetTriIndexes(int* triIndexes);
	bool InitTris();
	int GetVertexesCnt(){ return _vertexesCnt; }
	int GetTrisCnt(){ return _trisCnt; }
	Triangle* GetTriangleAtIndex(int triIdx);
		
private:
	// vertexes array
	Vec3* _vertexes;
	// vertexes count
	int _vertexesCnt;
	// vertex-tri array
	int* _triIndexes;
	// tris count
	int _trisCnt;
	// triangles array
	Triangle** _tris;
};

#endif /* trimesh_hpp */
