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
	Matrix(int row = 4, int col = 4)
	{
		_row = row;
		_col = col;
		_m = new double*[row];
		for (int i = 0; i < _row; ++i)
		{
			_m[i] = new double[col];
			for (int j = 0; j < _col; j++)
			{
				if ( i == j)
					_m[i][j] = 1;
				else
					_m[i][j] = 0;
			}
		}
	}
	
	~Matrix()
	{
		for (int i = 0; i < _row; ++i)
		{
			delete[] _m[i];
			_m[i] = nullptr;
		}
	}
	
	double** GetElements() const { return _m; }
	
	int GetCol() const { return _col; }
	
	int GetRow() const { return _row; }
	
	Matrix& SetElements (int n, ...)
	{
		va_list vl;
		va_start(vl, n);
		
		int c;
		double val;
		int maxAllowed = this->_row * this->_col;
		
		for(c = 0; c < n; c++)
		{
			if (c > (maxAllowed - 1))
				continue;
			
			val = va_arg(vl, double);
			int a = int (c / this->_row);
			int b = int (c % this->_row);
			this->_m[a][b] = val;
		}
		
		va_end(vl);
		return *this;
	}
	
	Matrix& SetElement (int i, int j, double val)
	{
		if (i < this->_row && j < this->_col)
			this->_m[i][j] = val;
		return *this;
	}
	
	inline double* operator[] (int i) const	{ return _m[i]; }
	
	inline double*& operator[] (int i) { return _m[i]; }
	
	friend std::ostream& operator<<(std::ostream &os, const Matrix &m)
	{
		for (int i = 0; i < m.GetRow(); ++i)
		{
			for (int j = 0; j < m.GetCol(); ++j)
			{
				os << m.GetElements()[i][j] << " ";
			}
			os << "\n";
		}
		os << "\n";
		return os;
	}
	
	inline bool operator== (Matrix m)
	{
		for(int i = 0; i < _row; i++){
			for(int j = 0; j < _col; j++){
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
	
	template<class S> Matrix& operator= (S x)
	{
		for(int i = 0; i < _row; i++)
		{
			for(int j = 0; j < _col; j++)
			{
				(*this)[i][j] = (double)x;
			}
		}
		return (*this);
	}
	
	Matrix& operator= (const Matrix& m)
	{
		for(int i = 0; i < _row; i++)
		{
			for(int j = 0; j < _col; j++)
			{
				_m[i][j] = m.GetElements()[i][j];
			}
		}
		return *this;
	}
	
	template<class S> Matrix operator+ (S x)
	{
		Matrix result;
		for(int i = 0; i < _row; i++)
		{
			for(int j = 0; j < _col; j++)
			{
				result[i][j] = (*this)[i][j] + (double)x;
			}
		}
		return result;
	}
	
	inline	Matrix operator+ (Matrix m)
	{
		Matrix result;
		for(int i = 0; i < _row; i++)
		{
			for(int j = 0; j < _col; j++)
			{
				result[i][j] = (*this)[i][j] + m[i][j];
			}
		}
		return result;
	}
	
	template<class S> Matrix operator* (S x)
	{
		Matrix result;
		for(int i = 0; i < _row; i++)
		{
			for(int j = 0; j < _col; j++)
			{
				result[i][j] = (*this)[i][j] * x;
			}
		}
		return result;
	}
	
	inline Matrix operator* (const Matrix& m)
	{
		if(this->_col == m.GetRow())
		{
			Matrix result(this->_row, m.GetCol());
			result = 0.0;
			for(int i = 0; i < this->_row; i++)
			{
				for(int j = 0; j < m.GetCol(); j++)
				{
					for(int k = 0; k < this->_col; k++)
					{
						double tempVal = (*this)[i][k] * m[k][j];
						result[i][j] += tempVal;
					}
				}
			}
			return result;
		}
		return Matrix(this->_row, this->_col);
	}
	
	inline Vec3 operator* (Vec3 v)
	{
		if (this->_col == 3)
		{
			Vec3 result;
			result[0] = _m[0][0] * v[0] + _m[0][1] * v[1] + _m[0][2] * v[2];
			result[1] = _m[1][0] * v[0] + _m[1][1] * v[1] + _m[1][2] * v[2];
			result[2] = _m[2][0] * v[0] + _m[2][1] * v[1] + _m[2][2] * v[2];
			return result;
		}
		if (this->_col == 4)
		{
			Vec3 result;
			result[0] = _m[0][0] * v[0] + _m[0][1] * v[1] + _m[0][2] * v[2] + _m[0][3] * 1;
			result[1] = _m[1][0] * v[0] + _m[1][1] * v[1] + _m[1][2] * v[2] + _m[1][3] * 1;
			result[2] = _m[2][0] * v[0] + _m[2][1] * v[1] + _m[2][2] * v[2] + _m[2][3] * 1;
			return result;
		}
		
		return Vec3(0,0,0);
	}
	
	Matrix& AddOffset (Vec3 offset)
	{
		this->_m[0][3] += offset[0];
		this->_m[1][3] += offset[1];
		this->_m[2][3] += offset[2];
		return *this;
	}
	
	Matrix& AddRotationX (float angle)
	{
		Matrix rotX;
		rotX.GetElements()[1][1] = cos(angle);
		rotX.GetElements()[1][2] = -sin(angle);
		rotX.GetElements()[2][1] = sin(angle);
		rotX.GetElements()[2][2] = cos(angle);
		*this = rotX * *this;
		return *this;
	}
	
	Matrix& AddRotationY (float angle)
	{
		Matrix rotY;
		rotY.GetElements()[0][0] = cos(angle);
		rotY.GetElements()[0][2] = sin(angle);
		rotY.GetElements()[2][0] = -sin(angle);
		rotY.GetElements()[2][2] = cos(angle);
		*this = rotY * *this;
		return *this;
	}
	
	Matrix& AddRotationZ (float angle)
	{
		Matrix rotZ;
		rotZ.GetElements()[0][0] = cos(angle);
		rotZ.GetElements()[0][1] = -sin(angle);
		rotZ.GetElements()[1][0] = sin(angle);
		rotZ.GetElements()[1][1] = cos(angle);
		*this = rotZ * *this;
		return *this;
	}
	
	Matrix& AddScaleNU (Vec3 nu)
	{
		Matrix scaleNU;
		scaleNU.GetElements()[0][0] *= nu[0];
		scaleNU.GetElements()[1][1] *= nu[1];
		scaleNU.GetElements()[2][2] *= nu[2];
		*this = scaleNU * *this;
		return *this;
	}
	
	Matrix& AddScale (double s)
	{
		Matrix scaleU;
		scaleU.GetElements()[0][0] *= s;
		scaleU.GetElements()[1][1] *= s;
		scaleU.GetElements()[2][2] *= s;
		*this = scaleU * *this;
		return *this;
	}
	
	Matrix& Transpose()
	{
		Matrix tmp = *this;
		for(int i = 0; i < 4; i++)
		{
			for(int j = 0; j < 4; j++)
			{
				_m[i][j] = tmp.GetElements()[j][i];
			}
		}
		return *this;
	}
	
	
	
	
	
	
private:
	double** _m;
	int _row, _col;
};

#endif /* matrix_hpp */
