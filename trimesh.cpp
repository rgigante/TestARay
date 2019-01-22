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

TriMesh::TriMesh(char const* name, int trisCnt, Material* mat) : _name(name), _trisCnt(trisCnt), _mat(mat), _evalMatrixStackOnInit(false)
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

bool TriMesh::Init(bool evaluateMatrixes)
{
	if (!_vertexes || _vertexesCnt < 1 || !_triIndexes)
		return false;
	
	// create global trf matrixes
	for (int i = 0; i < _mtrs.size(); ++i)
	{
		_gm = _gm * _mtrs[i];
		std::cout << "_mtrs[" << i <<"]\n" << _mtrs[i];
		_invmtrs.push_back(_mtrs[i].GetInverse());
		std::cout << "_invmtrs[" << i <<"]\n" << _invmtrs[i];
//		_gim = _gim * _invmtrs[i];
	}
	_gim = _gm.GetInverse();
	std::cout << "_gm\n" << _gm;
	std::cout << "_gim\n" << _gim;
	
	_evalMatrixStackOnInit = evaluateMatrixes;
	
	for (int i = 0; i < _trisCnt; ++i)
	{
		const int vIdx[3] = {_triIndexes[3 * i + 0], _triIndexes[3 * i + 1], _triIndexes[3 * i + 2]};
		if (_evalMatrixStackOnInit)
		{
			_tris[i] = new Triangle(nullptr, _gm * _vertexes[vIdx[0]],_gm * _vertexes[vIdx[1]],_gm * _vertexes[vIdx[2]], _mat, true);
		}
		else
		{
		_tris[i] = new Triangle(nullptr, _vertexes[vIdx[0]], _vertexes[vIdx[1]], _vertexes[vIdx[2]], _mat, true);
		}
	}
	
	return true;
}

bool TriMesh::Hit(const Ray& r, float t_min, float t_max, HitRecord& rec, bool isInstance) const
{	
	bool hasHit = false;
	float min_t = MAXFLOAT;
	HitRecord currentRec;
	
	if (!_evalMatrixStackOnInit)
	{
		Matrix gm = _gm;
		Matrix gim = _gim;
		Vec3 rpos = gim * r.GetOrigin();
		Vec3 rdir = gim.Get3x3() * r.GetDirection();
		
		for (int i = 0; i < _trisCnt; ++i)
		{
			bool isHit = _tris[i]->Hit(Ray(rpos, rdir), t_min, t_max, currentRec);
			if (isHit)
			{
				std::cout << "\ttriangle [" << i  << "]\n"
				<< "\t\tray pos: " << r.GetOrigin() << " / " << rpos << "\n"
				<< "\t\tray dir: " << r.GetDirection() << " / " << rdir << "\n"
				<< "\t\tcurrentRec.t: " << currentRec.t << "\n"
				<< "\t\tcurrentRec.p: " << currentRec.p << " / " << gm * currentRec.p <<"\n"
				<< "\t\tcurrentRec.n: " << currentRec.n << " / " << (gm.Get3x3() * currentRec.n).GetNormalized() <<"\n";
				hasHit = true;
				if (currentRec.t < min_t)
				{
					min_t = currentRec.t;
					rec = currentRec;
					rec.p = (gm * currentRec.p);
					rec.n = (gm.Get3x3() * currentRec.n).GetNormalized();
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
				std::cout << "\ttriangle [" << i  << "]\n"
				<< "\t\trpos: " << r.GetOrigin() << "\n"
				<< "\t\trdir: " << r.GetDirection() << "\n"
				<< "\t\tcurrentRec.t: " << currentRec.t << "\n"
				<< "\t\tcurrentRec.p: " << currentRec.p << "\n"
				<< "\t\tcurrentRec.n: " << currentRec.n.GetNormalized() << "\n";
				hasHit = true;
				if (currentRec.t < min_t)
				{
					min_t = currentRec.t;
					rec = currentRec;
					rec.p = (currentRec.p);
					rec.n = (currentRec.n).GetNormalized();
				}
			}
		}
	}
	std::cout << "\trec.t: " << rec.t << "\n"
	<< "\trec.p: " << rec.p << "\n"
	<< "\trec.n: " << rec.n << "\n";
	return hasHit;
}
