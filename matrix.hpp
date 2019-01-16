//
//  matrix.hpp
//  TraceARay01
//
//  Created by Riccardo Gigante on 16/01/2019.
//

#ifndef matrix_hpp
#define matrix_hpp

#include "vec3.hpp"

class Matrix
{
public:
	Matrix(){
		_m = new double*[4];
		_m[0] = new double[4];
		_m[1] = new double[4];
		_m[2] = new double[4];
		_m[3] = new double[4];
		_m[0][0] = _m[1][1] = _m[2][2] = _m[3][3] = 1.0;
		_m[0][1] = _m[0][2] = _m[0][3] = 0.0;
		_m[1][0] = _m[1][2] = _m[1][3] = 0.0;
		_m[2][0] = _m[2][1] = _m[2][3] = 0.0;
		_m[3][0] = _m[3][1] = _m[3][2] = 0.0;
	}
	
	~Matrix()
	{
		delete[] _m[0];
		delete[] _m[1];
		delete[] _m[2];
		delete[] _m[3];
		_m[0] = _m[1] = _m[2] = _m[3] = nullptr;
	}
	
	double** GetMatrix() { return _m; }
	
	inline void SetMatrix(double a00, double a01, double a02, double a03,
												double a10, double a11, double a12, double a13,
												double a20, double a21, double a22, double a23,
												double a30, double o31, double a32, double a33)
	{
		_m[0][0] = a00; _m[0][1] = a01; _m[0][2] = a02; _m[0][3] = a03;
		_m[1][1] = a10; _m[0][1] = a11; _m[0][2] = a12; _m[0][3] = a13;
		_m[2][1] = a20; _m[0][1] = a21; _m[0][2] = a22; _m[0][3] = a23;
		_m[3][0] = 0; _m[0][0] = 0; _m[0][0] = 0; _m[0][2] = 1;
	}
	
	inline double* operator[] (int i) const	{ return _m[i]; }
	inline double*& operator[] (int i)	{ return _m[i]; }
	
	void Dump()
	{
		std::cout <<
		"a00 ["<< _m[0][0] <<"] a01 ["<< _m[0][1] <<"] a02 ["<< _m[0][2] <<"] a03 ["<< _m[0][3] <<"]\n" <<
		"a10 ["<< _m[1][0] <<"] a11 ["<< _m[1][1] <<"] a12 ["<< _m[1][2] <<"] a13 ["<< _m[1][3] <<"]\n" <<
		"a20 ["<< _m[2][0] <<"] a21 ["<< _m[2][1] <<"] a22 ["<< _m[2][2] <<"] a23 ["<< _m[2][3] <<"]\n" <<
		"a30 ["<< _m[3][0] <<"] a31 ["<< _m[3][1] <<"] a32 ["<< _m[3][2] <<"] a33 ["<< _m[3][3] <<"]\n";
	}
	
	inline bool operator== (Matrix m)
	{
		for(int i = 0; i < 4; i++){
			for(int j = 0; j < 4; j++){
				if((*this)[i][j] != m[i][j])
					return false;
			}
		}
		return true;
	}
	
	inline bool operator!= (Matrix m)
	{
		return !((*this) == m);
	}
	
	template<class S> Matrix operator= (S x){
		for(int i = 0; i < 4; i++){
			for(int j = 0; j < 4; j++){
				if(x == 1 && i != j)
					continue;
				(*this)[i][j] = (double)x;
			}
		}
		return (*this);
	}
	
	Matrix operator= (Matrix m)
	{
		this->_m[0][0] = m._m[0][0];
		this->_m[0][1] = m._m[0][1];
		this->_m[0][2] = m._m[0][2];
		this->_m[0][3] = m._m[0][3];
		this->_m[1][0] = m._m[1][0];
		this->_m[1][1] = m._m[1][1];
		this->_m[1][2] = m._m[1][2];
		this->_m[1][3] = m._m[1][3];
		this->_m[2][0] = m._m[2][0];
		this->_m[2][1] = m._m[2][1];
		this->_m[2][2] = m._m[2][2];
		this->_m[2][3] = m._m[2][3];
		this->_m[3][0] = m._m[3][0];
		this->_m[3][1] = m._m[3][1];
		this->_m[3][2] = m._m[3][2];
		this->_m[3][3] = m._m[3][3];
		return *this;
	}
	
	template<class S> Matrix operator+ (S x)
	{
		Matrix result;
		for(int i = 0; i < 4; i++)
		{
			for(int j = 0; j < 4; j++)
			{
				result[i][j] = (*this)[i][j] + (double)x;
			}
		}
		return result;
	}
	
	inline	Matrix operator+ (Matrix m)
	{
		Matrix result;
		for(int i = 0; i < 4; i++){
			for(int j = 0; j < 4; j++){
				result[i][j] = (*this)[i][j] + m[i][j];
			}
		}
		return result;
	}
	
	template<class S> Matrix operator* (S x)
	{
		Matrix result;
		for(int i = 0; i < 4; i++)
		{
			for(int j = 0; j < 4; j++)
			{
				result[i][j] = (*this)[i][j] * x;
			}
		}
		return result;
	}
	
	inline Matrix operator* (Matrix m)
	{
			Matrix result;
			for(int i = 0; i < 4; i++)
			{
				for(int j = 0; j < 4; j++)
				{
					for(int k = 0; k < 4; k++)
					{
						result[i][j] += (*this)[i][k] * m[k][j];
					}
				}
			}
			return result;
	}
	
	inline Vec3 operator* (Vec3 v)
	{
		Vec3 result;
		result[0] = _m[0][0] * v[0] + _m[0][1] * v[1] + _m[0][2] * v[2] + _m[0][3] * 1;
		result[1] = _m[1][0] * v[0] + _m[1][1] * v[1] + _m[1][2] * v[2] + _m[1][3] * 1;
		result[2] = _m[2][0] * v[0] + _m[2][1] * v[1] + _m[2][2] * v[2] + _m[2][3] * 1;
		return result;
	}
	
	
private:
	double** _m;
};

#endif /* matrix_hpp */
