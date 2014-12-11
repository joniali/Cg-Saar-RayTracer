#ifndef CG1RAYTRACER_MATRIX_HEADER
#define CG1RAYTRACER_MATRIX_HEADER
#include <core/float4.h>
#include <core/vector.h>
#include <math.h>
namespace rt {
	class Matrix {
	public:
		Matrix(const Float4& r1, const Float4& r2, const Float4& r3, const Float4& r4);
		Matrix(){};
		Float4& operator[](int idx);
		Float4 operator[](int idx) const;

		Matrix operator+(const Matrix& b) const;
		Matrix operator-(const Matrix& b) const;

		Matrix transpose() const;
		Matrix invert() const;

		bool operator==(const Matrix& b) const;
		bool operator!=(const Matrix& b) const;


		Float4 operator*(const Float4& b) const;
		Vector operator*(const Vector& b) const;
		Point operator*(const Point& b) const;

		float det() const;

		static Matrix zero();
		static Matrix identity();

		static Matrix system(const Vector& e1, const Vector& e2, const Vector& e3);
		
		Float4 r1, r2, r3, r4;
	};
	Matrix product(const Matrix& a, const Matrix& b);
	Matrix operator*(const Matrix& a, float scalar);
	Matrix operator*(float scalar, const Matrix& a);
	/*class CoordinateFrame
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
	};*/

}
#endif