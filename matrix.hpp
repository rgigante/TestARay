
//  matrix.hpp
//  TraceARay01
//
//  Created by Riccardo Gigante on 16/01/2019.
//

#ifndef matrix_hpp
#define matrix_hpp

#include "vec3.hpp"
#include <vector>

const double g_M_PIon180 = M_PI/180.0;
const double g_180onM_PI = 180.0/M_PI;

class Matrix
{
public:
	Matrix(int row = 4, int col = 4)
	{
		_row = row;
		_col = col;
		_sclNU  = Vec3(1,1,1);
		_mat.resize(_row);
		for (int i = 0; i < _row; ++i)
		{
			_mat[i].resize(_col);
			for (int j = 0; j < _col; j++)
			{
				if ( i == j)
					_mat[i][j] = 1;
				else
					_mat[i][j] = 0;
			}
		}
	}
	
	~Matrix()
	{
		_mat.clear();
		_row = 0;
		_col = 0;
	}
	
	inline std::vector<double>& operator[](int i) { return _mat[i]; }
	
	inline std::vector<double> operator[](int i) const { return _mat[i]; }
	
	inline int GetCol() const { return _col; }
	
	inline int GetRow() const { return _row; }
	
	inline void SetCol(int col) { _mat.clear(); _col = col; }
	
	inline void SetRow(int row) { _mat.clear(); _row = row; }
	
	friend std::ostream& operator<<(std::ostream &os, const Matrix& m)
	{
		for (int i = 0; i < m.GetRow(); ++i)
		{
			os << "\t";
			for (int j = 0; j < m.GetCol(); ++j)
			{
				os << m[i][j] << " ";
			}
			os << "\n";
		}
		os << "\t" << m.GetScaleNU() << "\n";
		return os;
	}
	
	inline bool operator== (const Matrix& m)
	{
		if (this->_col != m.GetCol() ||	this->_row != m.GetRow())
			return false;
		
		for(int i = 0; i < _row; i++)
		{
			for(int j = 0; j < _col; j++)
			{
				if(this->_mat[i][j] != m[i][j])
					return false;
			}
		}
		return true;
	}
	
	inline bool operator!= (const Matrix& m)
	{
		return !((*this) == m);
	}
	
	template<class S> Matrix operator+ (S x)
	{
		Matrix result;
		for(int i = 0; i < _row; i++)
		{
			for(int j = 0; j < _col; j++)
			{
				result[i][j] = this->_mat[i][j] + (double)x;
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
				result[i][j] = this->_mat[i][j] * x;
			}
		}
		return result;
	}
	
	Matrix operator+ (const Matrix& m)
	{
		Matrix result;
		for(int i = 0; i < _row; i++)
		{
			for(int j = 0; j < _col; j++)
			{
				result[i][j] = this->_mat[i][j] + m[i][j];
			}
		}
		return result;
	}
	
	Matrix operator* (const Matrix& m)
	{
		assert(this->_col == m.GetRow());
		
		Matrix result(this->_row, m.GetCol());
		result.Zero();
		for(int i = 0; i < this->_row; i++)
		{
			for(int j = 0; j < m.GetCol(); j++)
			{
				for(int k = 0; k < this->_col; k++)
				{
					result[i][j] += this->_mat[i][k] * m[k][j];
				}
			}
		}
		
		result._sclNU = this->_sclNU * m._sclNU;
		
		return result;
	}
	
	Matrix Get3x3() const
	{
		Matrix res(3,3);
		res[0][0] = _mat[0][0];
		res[0][1] = _mat[0][1];
		res[0][2] = _mat[0][2];
		res[1][0] = _mat[1][0];
		res[1][1] = _mat[1][1];
		res[1][2] = _mat[1][2];
		res[2][0] = _mat[2][0];
		res[2][1] = _mat[2][1];
		res[2][2] = _mat[2][2];
		return res;
	}
	
	Vec3 GetScaleNU() const
	{
		Vec3 res;
		res = this->_sclNU;
		return res;
	}
	
	Vec3 GetOff() const
	{
		Vec3 res;
		res[0] = _mat[3][0];
		res[1] = _mat[3][1];
		res[2] = _mat[3][2];
		return res;
	}
	
	inline Vec3 operator* (Vec3 v)
	{
		if (this->_col == 3)
		{
			Vec3 result;
			result[0] = (this->_mat[0][0] * v[0] + this->_mat[0][1] * v[1] + this->_mat[0][2] * v[2]);
			result[1] = (this->_mat[1][0] * v[0] + this->_mat[1][1] * v[1] + this->_mat[1][2] * v[2]);
			result[2] = (this->_mat[2][0] * v[0] + this->_mat[2][1] * v[1] + this->_mat[2][2] * v[2]);
			return result;
		}
		
		if (this->_col == 4)
		{
			Vec3 result;
			result[0] = (this->_mat[0][0] * v[0] + this->_mat[0][1] * v[1] + this->_mat[0][2] * v[2]) + this->_mat[0][3];
			result[1] = (this->_mat[1][0] * v[0] + this->_mat[1][1] * v[1] + this->_mat[1][2] * v[2]) + this->_mat[1][3];
			result[2] = (this->_mat[2][0] * v[0] + this->_mat[2][1] * v[1] + this->_mat[2][2] * v[2]) + this->_mat[2][3];
			return result;
		}
		
		return Vec3(0,0,0);
	}
	
	Matrix& Identity()
	{
		for(int i = 0; i < _row; i++)
		{
			for(int j = 0; j < _col; j++)
			{
				if ( i == j)
					this->_mat[i][j] = 1.0;
				else
					this->_mat[i][j] = 0.0;
			}
		}
		return (*this);
	}
	
	Matrix& SetAllElements (double x)
	{
		for(int i = 0; i < _row; i++)
		{
			for(int j = 0; j < _col; j++)
			{
				this->_mat[i][j] = (double)x;
			}
		}
		return (*this);
	}
	
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
			this->_mat[a][b] = val;
		}
		
		va_end(vl);
		return (*this);
	}
	
	Matrix& SetElement (int i, int j, double val)
	{
		if (i < this->_row && j < this->_col)
		{
			this->_mat[i][j] = val;
		}
		return (*this);
	}
	
	Matrix& Zero()
	{
		return (this->SetAllElements(0));
	}
	
	Matrix& Ones()
	{
		return (this->SetAllElements(1));
	}
	
	Matrix& AddRotationX (const float angle)
	{
		assert(this->_col >= 3 && this->_row >= 3);
		Matrix rotX(_row, _col);
		const double angleRad = angle * g_M_PIon180;
		rotX[1][1] = cos(angleRad);
		rotX[1][2] = -sin(angleRad);
		rotX[2][1] = sin(angleRad);
		rotX[2][2] = cos(angleRad);
		*this = *this * rotX;
		return (*this);
	}
	
	Matrix& AddRotationY (const float angle)
	{
		assert(this->_col >= 3 && this->_row >= 3);
		Matrix rotY(_row, _col);
		const double angleRad = angle * g_M_PIon180;
		rotY[0][0] = cos(angleRad);
		rotY[0][2] = sin(angleRad);
		rotY[2][0] = -sin(angleRad);
		rotY[2][2] = cos(angleRad);
		*this = *this * rotY;
		return (*this);
	}
	
	Matrix& AddRotationZ (const float angle)
	{
		assert(this->_col >= 3 && this->_row >= 3);
		Matrix rotZ(_row, _col);
		const double angleRad = angle * g_M_PIon180;
		rotZ[0][0] = cos(angleRad);
		rotZ[0][1] = -sin(angleRad);
		rotZ[1][0] = sin(angleRad);
		rotZ[1][1] = cos(angleRad);
		*this = *this * rotZ;
		return (*this);
	}
	
	Matrix& AddOffset (const float off_x, const float off_y, const float off_z)
	{
		assert(this->_col > 3 && this->_row > 3);
		this->_mat[0][3] = off_x;
		this->_mat[1][3] = off_y;
		this->_mat[2][3] = off_z;
		return (*this);
	}
	
	Matrix& AddUniformScale (const float scale)
	{
		assert(this->_col > 3 && this->_row > 3);
		this->_mat[0][0] *= scale;
		this->_mat[1][1] *= scale;
		this->_mat[2][2] *= scale;
		return (*this);
	}
	
	Matrix& AddNonUniformScale (const float scl_x, const float scl_y, const float scl_z)
	{
		assert(this->_col > 3 && this->_row > 3);
		this->_mat[0][0] *= scl_x;
		this->_mat[1][1] *= scl_y;
		this->_mat[2][2] *= scl_z;
		return (*this);
	}
	
	Matrix& Reset()
	{
		Identity();		
		return (*this);
	}
	
	Matrix Transpose()
	{
		Matrix tmp(this->_col, this->_row);
		for(int i = 0; i < this->_row; i++)
		{
			for(int j = 0; j < this->_col; j++)
			{
				tmp[j][i] = this->_mat[i][j];
			}
		}
		return tmp;
	}
	
	double Determinant()
	{
		double value = _mat[0][3]*_mat[1][2]*_mat[2][1]*_mat[3][0] - _mat[0][2]*_mat[1][3]*_mat[2][1]*_mat[3][0] - _mat[0][3]*_mat[1][1]*_mat[2][2]*_mat[3][0] + _mat[0][1]*_mat[1][3]*_mat[2][2]*_mat[3][0] + _mat[0][2]*_mat[1][1]*_mat[2][3]*_mat[3][0] - _mat[0][1]*_mat[1][2]*_mat[2][3]*_mat[3][0] - _mat[0][3]*_mat[1][2]*_mat[2][0]*_mat[3][1] + _mat[0][2]*_mat[1][3]*_mat[2][0]*_mat[3][1]+_mat[0][3]*_mat[1][0]*_mat[2][2]*_mat[3][1] - _mat[0][0]*_mat[1][3]*_mat[2][2]*_mat[3][1] - _mat[0][2]*_mat[1][0]*_mat[2][3]*_mat[3][1] + _mat[0][0]*_mat[1][2]*_mat[2][3]*_mat[3][1]+_mat[0][3]*_mat[1][1]*_mat[2][0]*_mat[3][2] - _mat[0][1]*_mat[1][3]*_mat[2][0]*_mat[3][2] - _mat[0][3]*_mat[1][0]*_mat[2][1]*_mat[3][2] + _mat[0][0]*_mat[1][3]*_mat[2][1]*_mat[3][2]+_mat[0][1]*_mat[1][0]*_mat[2][3]*_mat[3][2] - _mat[0][0]*_mat[1][1]*_mat[2][3]*_mat[3][2] - _mat[0][2]*_mat[1][1]*_mat[2][0]*_mat[3][3] + _mat[0][1]*_mat[1][2]*_mat[2][0]*_mat[3][3]+_mat[0][2]*_mat[1][0]*_mat[2][1]*_mat[3][3] - _mat[0][0]*_mat[1][2]*_mat[2][1]*_mat[3][3] - _mat[0][1]*_mat[1][0]*_mat[2][2]*_mat[3][3] + _mat[0][0]*_mat[1][1]*_mat[2][2]*_mat[3][3];
		return value;
	}
	
	Matrix GetInverse()
	{
		Matrix res(4,4);
		double invdet = 1/Determinant();
		res[0][0] = (_mat[1][2]*_mat[2][3]*_mat[3][1] - _mat[1][3]*_mat[2][2]*_mat[3][1] + _mat[1][3]*_mat[2][1]*_mat[3][2] - _mat[1][1]*_mat[2][3]*_mat[3][2] - _mat[1][2]*_mat[2][1]*_mat[3][3] + _mat[1][1]*_mat[2][2]*_mat[3][3])*invdet;
		res[0][1] = (_mat[0][3]*_mat[2][2]*_mat[3][1] - _mat[0][2]*_mat[2][3]*_mat[3][1] - _mat[0][3]*_mat[2][1]*_mat[3][2] + _mat[0][1]*_mat[2][3]*_mat[3][2] + _mat[0][2]*_mat[2][1]*_mat[3][3] - _mat[0][1]*_mat[2][2]*_mat[3][3])*invdet;
		res[0][2] = (_mat[0][2]*_mat[1][3]*_mat[3][1] - _mat[0][3]*_mat[1][2]*_mat[3][1] + _mat[0][3]*_mat[1][1]*_mat[3][2] - _mat[0][1]*_mat[1][3]*_mat[3][2] - _mat[0][2]*_mat[1][1]*_mat[3][3] + _mat[0][1]*_mat[1][2]*_mat[3][3])*invdet;
		res[0][3] = (_mat[0][3]*_mat[1][2]*_mat[2][1] - _mat[0][2]*_mat[1][3]*_mat[2][1] - _mat[0][3]*_mat[1][1]*_mat[2][2] + _mat[0][1]*_mat[1][3]*_mat[2][2] + _mat[0][2]*_mat[1][1]*_mat[2][3] - _mat[0][1]*_mat[1][2]*_mat[2][3])*invdet;
		res[1][0] = (_mat[1][3]*_mat[2][2]*_mat[3][0] - _mat[1][2]*_mat[2][3]*_mat[3][0] - _mat[1][3]*_mat[2][0]*_mat[3][2] + _mat[1][0]*_mat[2][3]*_mat[3][2] + _mat[1][2]*_mat[2][0]*_mat[3][3] - _mat[1][0]*_mat[2][2]*_mat[3][3])*invdet;
		res[1][1] = (_mat[0][2]*_mat[2][3]*_mat[3][0] - _mat[0][3]*_mat[2][2]*_mat[3][0] + _mat[0][3]*_mat[2][0]*_mat[3][2] - _mat[0][0]*_mat[2][3]*_mat[3][2] - _mat[0][2]*_mat[2][0]*_mat[3][3] + _mat[0][0]*_mat[2][2]*_mat[3][3])*invdet;
		res[1][2] = (_mat[0][3]*_mat[1][2]*_mat[3][0] - _mat[0][2]*_mat[1][3]*_mat[3][0] - _mat[0][3]*_mat[1][0]*_mat[3][2] + _mat[0][0]*_mat[1][3]*_mat[3][2] + _mat[0][2]*_mat[1][0]*_mat[3][3] - _mat[0][0]*_mat[1][2]*_mat[3][3])*invdet;
		res[1][3] = (_mat[0][2]*_mat[1][3]*_mat[2][0] - _mat[0][3]*_mat[1][2]*_mat[2][0] + _mat[0][3]*_mat[1][0]*_mat[2][2] - _mat[0][0]*_mat[1][3]*_mat[2][2] - _mat[0][2]*_mat[1][0]*_mat[2][3] + _mat[0][0]*_mat[1][2]*_mat[2][3])*invdet;
		res[2][0] = (_mat[1][1]*_mat[2][3]*_mat[3][0] - _mat[1][3]*_mat[2][1]*_mat[3][0] + _mat[1][3]*_mat[2][0]*_mat[3][1] - _mat[1][0]*_mat[2][3]*_mat[3][1] - _mat[1][1]*_mat[2][0]*_mat[3][3] + _mat[1][0]*_mat[2][1]*_mat[3][3])*invdet;
		res[2][1] = (_mat[0][3]*_mat[2][1]*_mat[3][0] - _mat[0][1]*_mat[2][3]*_mat[3][0] - _mat[0][3]*_mat[2][0]*_mat[3][1] + _mat[0][0]*_mat[2][3]*_mat[3][1] + _mat[0][1]*_mat[2][0]*_mat[3][3] - _mat[0][0]*_mat[2][1]*_mat[3][3])*invdet;
		res[2][2] = (_mat[0][1]*_mat[1][3]*_mat[3][0] - _mat[0][3]*_mat[1][1]*_mat[3][0] + _mat[0][3]*_mat[1][0]*_mat[3][1] - _mat[0][0]*_mat[1][3]*_mat[3][1] - _mat[0][1]*_mat[1][0]*_mat[3][3] + _mat[0][0]*_mat[1][1]*_mat[3][3])*invdet;
		res[2][3] = (_mat[0][3]*_mat[1][1]*_mat[2][0] - _mat[0][1]*_mat[1][3]*_mat[2][0] - _mat[0][3]*_mat[1][0]*_mat[2][1] + _mat[0][0]*_mat[1][3]*_mat[2][1] + _mat[0][1]*_mat[1][0]*_mat[2][3] - _mat[0][0]*_mat[1][1]*_mat[2][3])*invdet;
		res[3][0] = (_mat[1][2]*_mat[2][1]*_mat[3][0] - _mat[1][1]*_mat[2][2]*_mat[3][0] - _mat[1][2]*_mat[2][0]*_mat[3][1] + _mat[1][0]*_mat[2][2]*_mat[3][1] + _mat[1][1]*_mat[2][0]*_mat[3][2] - _mat[1][0]*_mat[2][1]*_mat[3][2])*invdet;
		res[3][1] = (_mat[0][1]*_mat[2][2]*_mat[3][0] - _mat[0][2]*_mat[2][1]*_mat[3][0] + _mat[0][2]*_mat[2][0]*_mat[3][1] - _mat[0][0]*_mat[2][2]*_mat[3][1] - _mat[0][1]*_mat[2][0]*_mat[3][2] + _mat[0][0]*_mat[2][1]*_mat[3][2])*invdet;
		res[3][2] = (_mat[0][2]*_mat[1][1]*_mat[3][0] - _mat[0][1]*_mat[1][2]*_mat[3][0] - _mat[0][2]*_mat[1][0]*_mat[3][1] + _mat[0][0]*_mat[1][2]*_mat[3][1] + _mat[0][1]*_mat[1][0]*_mat[3][2] - _mat[0][0]*_mat[1][1]*_mat[3][2])*invdet;
		res[3][3] = (_mat[0][1]*_mat[1][2]*_mat[2][0] - _mat[0][2]*_mat[1][1]*_mat[2][0] + _mat[0][2]*_mat[1][0]*_mat[2][1] - _mat[0][0]*_mat[1][2]*_mat[2][1] - _mat[0][1]*_mat[1][0]*_mat[2][2] + _mat[0][0]*_mat[1][1]*_mat[2][2])*invdet;
		
		res._sclNU = Vec3(1/_sclNU[0], 1/_sclNU[1], 1/_sclNU[2]);
		
		return res;
	}
	
private:
	int _col, _row;
	std::vector<std::vector<double>> _mat;
	Vec3 _sclNU;
};

#endif /* matrix_hpp */
