//
//  trimesh.cpp
//  TraceARay01
//
//  Created by Riccardo Gigante on 10/01/2019.
//

#include <sstream>
#include <iostream>
#include <fstream>
#include "trimesh.hpp"

TriMesh::TriMesh(char const * name, int trisCnt, Material const * mat) : _trisCnt(trisCnt)/*, _mat(mat)*/
{
	SetMaterial(mat);
	SetName(name);
	_tris = new Triangle2*[_trisCnt];
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
	
}

Triangle2* TriMesh::GetTriangleAtIndex(int triIdx)
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

bool TriMesh::InitTris()
{
	if (!_vertexes || _vertexesCnt < 1 || !_triIndexes)
		return false;
	
	for (int i = 0; i < _trisCnt; ++i)
	{
		const int vIdx[3] = {_triIndexes[3 * i + 0], _triIndexes[3 * i + 1], _triIndexes[3 * i + 2]};
		{
		_tris[i] = new Triangle2("trimesh", _vertexes[vIdx[0]], _vertexes[vIdx[1]], _vertexes[vIdx[2]], GetMaterial(), true);
		}
	}
	
	return true;
}

bool TriMesh::Hit2(const Ray& r, float t_min, float t_max, HitRecord& rec, bool debugRay /*= false*/)
{
	HitRecord tempRec;
	bool hitAnything = false;
	double closestSoFar = t_max;
	
	for (int i = 0; i < _trisCnt; ++i)
	{
		if (_tris[i]->Hit2(r, t_min, closestSoFar, tempRec, debugRay))
		{
			hitAnything = true;
			closestSoFar = tempRec.t;
			rec = tempRec;
		}
	}
	return hitAnything;
}
