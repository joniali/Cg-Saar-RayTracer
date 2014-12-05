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
}
#endif