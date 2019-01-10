//
//  trimesh.cpp
//  TraceARay01
//
//  Created by Riccardo Gigante on 10/01/2019.
//

#include "trimesh.hpp"

TriMesh::TriMesh(int trisCnt, Material* mat) : _trisCnt(trisCnt), _mat(mat)
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
		_tris[i] = new Triangle(_vertexes[vIdx[0]], _vertexes[vIdx[1]], _vertexes[vIdx[2]], _mat, true);
	}
	
	return true;
}

bool TriMesh::Hit(const Ray &r, float t_min, float t_max, HitRecord &rec) const
{
	if (!_tris || _trisCnt == 0)
		return false;
	
	for (int i = 0; i < _trisCnt; ++i)
		if (_tris[i]->Hit(r, t_min, t_max, rec))
			return true;
	
	return false;
	
}
