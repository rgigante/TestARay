//
//  trimesh.cpp
//  TraceARay01
//
//  Created by Riccardo Gigante on 10/01/2019.
//

#include "trimesh.hpp"

TriMesh::TriMesh(char const* name, int trisCnt, Material* mat) : _name(name), _trisCnt(trisCnt), _mat(mat)
{
	_tris = new Triangle*[_trisCnt];
	assert(_tris);
}

TriMesh::~TriMesh()
{
	if (_tris)
	{
		for (int i = 0; i < _trisCnt; ++i)
		{
			delete _tris[i];
			_tris[i] = nullptr;
		}
		delete[] _tris;
		_tris = nullptr;
	}
	
	if (_mat)
	{
		delete _mat;
		_mat = nullptr;
	}
}

Triangle* TriMesh::GetTriangleAtIndex(int triIdx)
{
	// search the vertex indexes associated to triangle index
	return _tris[triIdx];
}

bool TriMesh::SetVertexes(Vec3* points, int pointsCnt)
{
	if (!points || pointsCnt < 1)
		return false;
	
	_vertexesCnt = pointsCnt;
	_vertexes = points;
	
	return true;
}

bool TriMesh::SetTriIndexes(int* triIndexes)
{
	if (!triIndexes)
		return false;
	
	_triIndexes = triIndexes;
	
	return true;
	
}

bool TriMesh::Init()
{
	if (!_vertexes || _vertexesCnt < 1 || !_triIndexes)
		return false;
	
	for (int i = 0; i < _trisCnt; ++i)
	{
		const int vIdx[3] = {_triIndexes[3 * i + 0], _triIndexes[3 * i + 1], _triIndexes[3 * i + 2]};
		_tris[i] = new Triangle(nullptr, _vertexes[vIdx[0]], _vertexes[vIdx[1]], _vertexes[vIdx[2]], _mat, true);
	}
	
	for (int i = 0; i < _mtrs.size(); ++i)
	{
		_invmtrs.push_back(_mtrs[i].GetInverse());
	}
	
	return true;
}

bool TriMesh::Hit(const Ray& r, float t_min, float t_max, HitRecord& rec, bool isInstance) const
{	
	bool hasHit = false;
	float min_t = MAXFLOAT;
	HitRecord currentRec;
	
	Vec3 pos = r.GetOrigin();
	Vec3 dir = r.GetDirection();
	if (!isInstance)
	{
		Matrix m, im;
		for (int j = _invmtrs.size()-1; j >= 0; j--)
		{
			im = _invmtrs[j];
			pos = im * pos;
			dir = im * dir;
		}
		
		for (int i = 0; i < _trisCnt; ++i)
		{
			if (_tris[i]->Hit(Ray(pos, dir), t_min, t_max, currentRec))
			{
				hasHit = true;
				for (int j = _trfs.size()-1; j >= 0; j--)
				{
					m = _mtrs[j];
					im = _invmtrs[j];
					currentRec.p = m * currentRec.p;
					currentRec.n = m * currentRec.n;
				}
				if (currentRec.t < min_t)
				{
					min_t = currentRec.t;
					rec = currentRec;
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < _trisCnt; ++i)
		{
			if (_tris[i]->Hit(r, t_min, t_max, currentRec))
			{
				hasHit = true;
				if (currentRec.t < min_t)
				{
					min_t = currentRec.t;
					rec = currentRec;
				}
			}
		}
	}
	return hasHit;
}
