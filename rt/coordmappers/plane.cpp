#include <rt\coordmappers\plane.h>

namespace rt
{
	PlaneCoordMapper::PlaneCoordMapper(const Vector& e1, const Vector& e2)
	{
		pe1 = e1;
		pe2 = e2;
		pnormal = cross(e1, e2);
		Float4 r1(e1.x, e2.x, pnormal.x, 0);
		Float4 r2(e1.y, e2.y, pnormal.y, 0);
		Float4 r3(e1.z, e2.z, pnormal.z, 0);
		Float4 r4(0, 0, 0, 1);
		Matrix mat = Matrix(r1, r2, r3, r4);
		transition = mat.invert();
	}

	Point PlaneCoordMapper::getCoords(const Intersection& hit) const
	{
	
		Vector hitvector = hit.local()-Point::rep(0.0f);
		Vector projectionVector = hit.local() - (dot(hitvector, pnormal) * pnormal);
		//if (projectionVector.z!=0)

		//	return Point(projectionVector.x / projectionVector.z, projectionVector.y / projectionVector.z, 0);
		return projectionVector;
	
	}
	
}