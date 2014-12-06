#ifndef CG1RAYTRACER_MATRIX_HEADER
#define CG1RAYTRACER_MATRIX_HEADER
#include <core/float4.h>
#include <core/vector.h>
#include <math.h>
namespace rt {
	class Matrix {
	public:
		Matrix() {}
		Matrix(const Float4& r1, const Float4& r2, const Float4& r3, const Float4& r4);
		Matrix invert() const;
		Float4 Matrix::operator[](int idx) const;
		Matrix Matrix::zero() const;
		Float4 Matrix::operator*(const Float4& b) const;
		
		Float4 r1, r2, r3, r4;
	};
	Matrix operator*(const Matrix& a, float scalar);
	Matrix operator*(float scalar, const Matrix& a);
	class CoordinateFrame
	{
	public:
		CoordinateFrame()
		{
			mX = Vector(1, 0, 0);
			mY = Vector(0, 1, 0);
			mZ = Vector(0, 0, 1);
		};
		CoordinateFrame(const Vector & x, const Vector & y, const Vector & z) : mX(x), mY(y), mZ(z) { }
		
		void SetFromZ(const Vector & z)
		{
			mZ = z.normalize();
			Vector tmpX = Vector(1, 0, 0);
			if (abs(mZ.x) >= 1) tmpX = Vector(0, 1, 0);
			mY = cross(mZ, tmpX).normalize();
			mX = cross(mY, mZ).normalize();
		}
		Vector ToWorld(const Vector & a) const
		{
			return mX * a.x + mY * a.y + mZ * a.z;
		}
		Vector ToLocal(const Vector & a) const
		{
			return Vector(dot(a, mX), dot(a, mY), dot(a, mZ));
		}
	public:
		Vector mX, mY, mZ;
	};

}
#endif