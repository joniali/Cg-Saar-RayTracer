#ifndef CG1RAYTRACER_COORDINATEFRAME_HEADER
#define CG1RAYTRACER_COORDINATEFRAME_HEADER

#include <core/float4.h>
#include <core\vector.h>
namespace rt
{

class CoordinateFrame
{
public:
	CoordinateFrame(){
		mX = Vector(1, 0, 0);
		mY = Vector(0, 1, 0);
		mZ = Vector(0, 0, 1);
	};
		CoordinateFrame::CoordinateFrame(const Vector & x, const Vector & y, const Vector & z) : mX(x), mY(y), mZ(z) { }

	void CoordinateFrame::SetFromZ(const Vector & z)
	{
		mZ = z.normalize();
		Vector tmpX = Vector(1, 0, 0);
		if (abs(mZ.x) >= 1) tmpX = Vector(0, 1, 0);
		mY = cross(mZ, tmpX).normalize();
		mX = cross(mY, mZ).normalize();
	}
	Vector CoordinateFrame::ToWorld(const Vector & a) const
	{
		return mX * a.x + mY * a.y + mZ * a.z;
	}
	Vector CoordinateFrame::ToLocal(const Vector & a) const
	{
		return Vector(dot(a, mX), dot(a, mY), dot(a, mZ));
	}
	Vector mX, mY, mZ;
};
}
#endif