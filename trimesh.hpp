//
//  trimesh.hpp
//  TraceARay01
//
//  Created by Riccardo Gigante on 10/01/2019.
//

#ifndef trimesh_hpp
#define trimesh_hpp

#include "transformation.hpp"
#include "triangle.hpp"

class TriMesh: public Hitable
{
public:
	TriMesh(char const* name, int trisCnt, Material* mat);
	~TriMesh();
	bool Hit (const Ray& r, float t_min, float t_max, HitRecord& rec, bool isInstance = false) const;
	bool SetVertexes(Vec3* points, int pointsCnt);
	bool SetTriIndexes(int* triIndexes);
	bool Init(bool evaluateMatrixes = false);
	int GetVertexesCnt(){ return _vertexesCnt; }
	int GetTrisCnt(){ return _trisCnt; }
	Triangle* GetTriangleAtIndex(int triIdx);
	const Transformation& GetTransformationAt(int idx) { return _trfs[idx]; }
	void DropTransformationAt(int idx){	_trfs.erase(_trfs.begin() + idx);	}
	void AddTransformation(Transformation trf){	_trfs.push_back(trf);	}
	const Matrix& GetMatrixAt(int idx) { return _mtrs[idx]; }
	void DropMatrixAt(int idx){	_mtrs.erase(_mtrs.begin() + idx);	}
	void AddMatrix(Matrix trf){	_mtrs.push_back(trf);	}
	
private:
	Vec3* _vertexes;
	int _vertexesCnt;
	int* _triIndexes;
	int _trisCnt;
	char const *_name;
	Triangle** _tris;
	Material* _mat;
	bool _evalMatrixStackOnInit;
	
	std::vector<Transformation> _trfs;
	std::vector<Matrix> _mtrs;
	std::vector<Matrix> _invmtrs;
	Matrix _gm, _gim;
};

#endif /* trimesh_hpp */
