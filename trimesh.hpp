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
	TriMesh(char const* name, int trisCnt, Material* mat);
	~TriMesh();
	bool Hit (const Ray& r, float t_min, float t_max, HitRecord& rec) const;
	bool SetVertexes(Vec3* points, int pointsCnt);
	bool SetTriIndexes(int* triIndexes);
	bool Init();
	int GetVertexesCnt(){ return _vertexesCnt; }
	int GetTrisCnt(){ return _trisCnt; }
	Triangle* GetTriangleAtIndex(int triIdx);
	Matrix* GetM() { return &_mtx; }
	void SetM(const Matrix& mtx) {_mtx = mtx;}
	
private:
	Vec3* _vertexes;
	int _vertexesCnt;
	int* _triIndexes;
	int _trisCnt;
	char const *_name;
	Triangle** _tris;
	Material* _mat;
	
	Matrix _mtx;
};

#endif /* trimesh_hpp */
