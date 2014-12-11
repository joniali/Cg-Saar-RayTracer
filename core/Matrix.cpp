#include <core\Matrix.h>

namespace rt

{
	Matrix::Matrix(const Float4& r1, const Float4& r2, const Float4& r3, const Float4& r4)
	{
		this->r1 = r1;
		this->r2 = r2;
		this->r3 = r3;
		this->r4 = r4;
	}
	Float4 Matrix::operator[](int idx) const
	{
		switch (idx)
		{
		case 0:
			return r1;
			break;
		case 1:
			return r2;
			break;
		case 2:
			return r3;
			break;
		case 3:
			return r4;
			break;
		}
		
	}
	Float4& Matrix::operator[](int idx) 
	{
		switch (idx)
		{
		case 0:
			return r1;
			break;
		case 1:
			return r2;
			break;
		case 2:
			return r3;
			break;
		case 3:
			return r4;
			break;
		}
	}
	Matrix Matrix::invert() const {
		Matrix result;
		const Matrix& m = *this;

		//Taken and modified from http://stackoverflow.com/questions/1148309/inverting-a-4x4-matrix
		result[0][0] = m[1][1] * m[2][2] * m[3][3] - m[1][1] * m[2][3] * m[3][2] - m[2][1] * m[1][2] * m[3][3] + m[2][1] * m[1][3] * m[3][2] + m[3][1] * m[1][2] * m[2][3] - m[3][1] * m[1][3] * m[2][2];
		result[1][0] = -m[1][0] * m[2][2] * m[3][3] + m[1][0] * m[2][3] * m[3][2] + m[2][0] * m[1][2] * m[3][3] - m[2][0] * m[1][3] * m[3][2] - m[3][0] * m[1][2] * m[2][3] + m[3][0] * m[1][3] * m[2][2];
		result[2][0] = m[1][0] * m[2][1] * m[3][3] - m[1][0] * m[2][3] * m[3][1] - m[2][0] * m[1][1] * m[3][3] + m[2][0] * m[1][3] * m[3][1] + m[3][0] * m[1][1] * m[2][3] - m[3][0] * m[1][3] * m[2][1];
		result[3][0] = -m[1][0] * m[2][1] * m[3][2] + m[1][0] * m[2][2] * m[3][1] + m[2][0] * m[1][1] * m[3][2] - m[2][0] * m[1][2] * m[3][1] - m[3][0] * m[1][1] * m[2][2] + m[3][0] * m[1][2] * m[2][1];

		float det = m[0][0] * result[0][0] + m[0][1] * result[1][0] + m[0][2] * result[2][0] + m[0][3] * result[3][0];
		if (det == 0)
			return Matrix::zero();

		result[0][1] = -m[0][1] * m[2][2] * m[3][3] + m[0][1] * m[2][3] * m[3][2] + m[2][1] * m[0][2] * m[3][3] - m[2][1] * m[0][3] * m[3][2] - m[3][1] * m[0][2] * m[2][3] + m[3][1] * m[0][3] * m[2][2];
		result[1][1] = m[0][0] * m[2][2] * m[3][3] - m[0][0] * m[2][3] * m[3][2] - m[2][0] * m[0][2] * m[3][3] + m[2][0] * m[0][3] * m[3][2] + m[3][0] * m[0][2] * m[2][3] - m[3][0] * m[0][3] * m[2][2];
		result[2][1] = -m[0][0] * m[2][1] * m[3][3] + m[0][0] * m[2][3] * m[3][1] + m[2][0] * m[0][1] * m[3][3] - m[2][0] * m[0][3] * m[3][1] - m[3][0] * m[0][1] * m[2][3] + m[3][0] * m[0][3] * m[2][1];
		result[3][1] = m[0][0] * m[2][1] * m[3][2] - m[0][0] * m[2][2] * m[3][1] - m[2][0] * m[0][1] * m[3][2] + m[2][0] * m[0][2] * m[3][1] + m[3][0] * m[0][1] * m[2][2] - m[3][0] * m[0][2] * m[2][1];
		result[0][2] = m[0][1] * m[1][2] * m[3][3] - m[0][1] * m[1][3] * m[3][2] - m[1][1] * m[0][2] * m[3][3] + m[1][1] * m[0][3] * m[3][2] + m[3][1] * m[0][2] * m[1][3] - m[3][1] * m[0][3] * m[1][2];
		result[1][2] = -m[0][0] * m[1][2] * m[3][3] + m[0][0] * m[1][3] * m[3][2] + m[1][0] * m[0][2] * m[3][3] - m[1][0] * m[0][3] * m[3][2] - m[3][0] * m[0][2] * m[1][3] + m[3][0] * m[0][3] * m[1][2];
		result[2][2] = m[0][0] * m[1][1] * m[3][3] - m[0][0] * m[1][3] * m[3][1] - m[1][0] * m[0][1] * m[3][3] + m[1][0] * m[0][3] * m[3][1] + m[3][0] * m[0][1] * m[1][3] - m[3][0] * m[0][3] * m[1][1];
		result[3][2] = -m[0][0] * m[1][1] * m[3][2] + m[0][0] * m[1][2] * m[3][1] + m[1][0] * m[0][1] * m[3][2] - m[1][0] * m[0][2] * m[3][1] - m[3][0] * m[0][1] * m[1][2] + m[3][0] * m[0][2] * m[1][1];
		result[0][3] = -m[0][1] * m[1][2] * m[2][3] + m[0][1] * m[1][3] * m[2][2] + m[1][1] * m[0][2] * m[2][3] - m[1][1] * m[0][3] * m[2][2] - m[2][1] * m[0][2] * m[1][3] + m[2][1] * m[0][3] * m[1][2];
		result[1][3] = m[0][0] * m[1][2] * m[2][3] - m[0][0] * m[1][3] * m[2][2] - m[1][0] * m[0][2] * m[2][3] + m[1][0] * m[0][3] * m[2][2] + m[2][0] * m[0][2] * m[1][3] - m[2][0] * m[0][3] * m[1][2];
		result[2][3] = -m[0][0] * m[1][1] * m[2][3] + m[0][0] * m[1][3] * m[2][1] + m[1][0] * m[0][1] * m[2][3] - m[1][0] * m[0][3] * m[2][1] - m[2][0] * m[0][1] * m[1][3] + m[2][0] * m[0][3] * m[1][1];
		result[3][3] = m[0][0] * m[1][1] * m[2][2] - m[0][0] * m[1][2] * m[2][1] - m[1][0] * m[0][1] * m[2][2] + m[1][0] * m[0][2] * m[2][1] + m[2][0] * m[0][1] * m[1][2] - m[2][0] * m[0][2] * m[1][1];

		result = result*(1.0f / det);
		return result;
	}
	  Matrix Matrix::zero() 
	{
		
		return Matrix(Float4::rep(0.0), Float4::rep(0.0), Float4::rep(0.0), Float4::rep(0.0));
	}
	Matrix Matrix::operator + (const Matrix& b) const
	{
		
		return Matrix(r1 + b.r1, r2 + b.r2, r3 + b.r3, r4 + b.r4);
			
	}
	Matrix Matrix::operator - (const Matrix& b) const
	{
		return (*this + (-1 * b));
	}
	Matrix Matrix::transpose() const
	{
		Float4 r1_new(r1.x, r2.x, r3.x, r4.x);
		Float4 r2_new(r1.y, r2.y, r3.y, r4.y);
		Float4 r3_new(r1.z, r2.z, r3.z, r4.z);
		Float4 r4_new(r1.w, r2.w, r3.w, r4.w);

		return Matrix(r1_new, r2_new, r3_new, r4_new);

	}
	bool Matrix::operator == (const Matrix& b) const
	{
		return (r1 == b.r1 && r2==b.r2 && r3 ==  b.r3 && r4==b.r4);

	}
	bool Matrix::operator!=(const Matrix& b) const
	{
		return !(*this == b);
	}
	Float4 Matrix::operator*(const Float4& b) const
	{
		return Float4(dot(r1,b) , dot(r2,b) , dot(r3 ,b) , dot(r4,b));
		
	}
	Vector Matrix::operator*(const Vector& b) const
	{
		Float4 newb(b);
		return Vector((*this) * newb);
	}
	Point Matrix::operator*(const Point& b) const
	{
		Float4 newb(b);
		return Point((*this) * newb);
	}
	float Matrix::det() const
	{
		Matrix result;
		const Matrix &m = *this;
		result[0][0] = m[1][1] * m[2][2] * m[3][3] - m[1][1] * m[2][3] * m[3][2] - m[2][1] * m[1][2] * m[3][3] + m[2][1] * m[1][3] * m[3][2] + m[3][1] * m[1][2] * m[2][3] - m[3][1] * m[1][3] * m[2][2];
		result[1][0] = -m[1][0] * m[2][2] * m[3][3] + m[1][0] * m[2][3] * m[3][2] + m[2][0] * m[1][2] * m[3][3] - m[2][0] * m[1][3] * m[3][2] - m[3][0] * m[1][2] * m[2][3] + m[3][0] * m[1][3] * m[2][2];
		result[2][0] = m[1][0] * m[2][1] * m[3][3] - m[1][0] * m[2][3] * m[3][1] - m[2][0] * m[1][1] * m[3][3] + m[2][0] * m[1][3] * m[3][1] + m[3][0] * m[1][1] * m[2][3] - m[3][0] * m[1][3] * m[2][1];
		result[3][0] = -m[1][0] * m[2][1] * m[3][2] + m[1][0] * m[2][2] * m[3][1] + m[2][0] * m[1][1] * m[3][2] - m[2][0] * m[1][2] * m[3][1] - m[3][0] * m[1][1] * m[2][2] + m[3][0] * m[1][2] * m[2][1];
		float det = m[0][0] * result[0][0] + m[0][1] * result[1][0] + m[0][2] * result[2][0] + m[0][3] * result[3][0];
		return det;
	}
	 Matrix Matrix::identity()
	{
		Float4 r1_new(1.0, 0.0, 0.0, 0.0);
		Float4 r2_new(0.0, 1.0, 0.0, 0.0);
		Float4 r3_new(0.0, 0.0, 1.0, 0.0);
		Float4 r4_new(0.0, 0.0, 0.0, 1.0);
		return Matrix(r1_new, r2_new, r3_new, r4_new);

	}
	 Matrix Matrix::system(const Vector& e1, const Vector& e2, const Vector& e3)
	{
		Float4 r1_new = Float4(e1);
		Float4 r2_new = Float4(e2);
		Float4 r3_new = Float4(e3);
		Float4 r4_new = Float4(0.0, 0.0, 0.0, 1.0);
		return Matrix(r1_new, r2_new, r3_new, r4_new).transpose();
	}
	Matrix product(const Matrix& a, const Matrix& b)
	{
		/*Matrix first = a.transpose();
		Matrix second = b.transpose();
		Vector v1 = cross(Vector(first.r1), Vector(second.r1));
		Vector v2 = cross(Vector(first.r2), Vector(second.r2));
		Vector v3 = cross(Vector(first.r3), Vector(second.r3));
		Vector v4 = cross(Vector(first.r4), Vector(second.r4));
		return Matrix(Float4(v1), Float4(v2), Float4(v3), Float4(v4));*/
		Matrix result;
		for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
		{
			result[i][j] = 0;
			for (int k = 0; k < 4; ++k)
				result[i][j] += a[i][k] * b[k][j];
		}
		return result;


	}
	Matrix operator*(const Matrix& a, float scalar)
	{
		return Matrix(scalar * a.r1, scalar * a.r2, scalar * a.r3, scalar * a.r4);
	}
	Matrix operator*(float scalar, const Matrix& a)
	{
		return Matrix(scalar * a.r1, scalar * a.r2, scalar * a.r3, scalar * a.r4);
	}
	
	
}