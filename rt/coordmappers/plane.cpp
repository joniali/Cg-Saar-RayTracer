#include <rt\coordmappers\plane.h>

namespace rt
{
	PlaneCoordMapper::PlaneCoordMapper(const Vector& e1, const Vector& e2)
	{
		pe1 = e1;
		pe2 = e2;
		pnormal = cross(e1, e2).normalize();
	}

	Point PlaneCoordMapper::getCoords(const Intersection& hit) const
	{
	
		Vector hitvector = hit.hitPoint()-Vector::rep(0.0f);
		Vector projectionVector = hitvector - (dot(hitvector, pnormal) * pnormal);
		return Point(projectionVector.x,projectionVector.y,0);
	
	}
}