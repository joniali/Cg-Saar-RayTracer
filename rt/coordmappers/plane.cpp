#include <rt\coordmappers\plane.h>

namespace rt
{
	PlaneCoordMapper::PlaneCoordMapper(const Vector& e1, const Vector& e2)
	{
		pe1 = e1;
		pe2 = e2;
		pnormal = cross(e1, e2);
		
		
	}

	Point PlaneCoordMapper::getCoords(const Intersection& hit) const
	{
	
		Vector hitvector = Vector(hit.local());
		
		Vector ve1 = pe1.normalize();
		Vector ve2 = pe2.normalize();

		return Point(dot(ve1, hitvector) / pe1.length(), dot(ve2, hitvector) / pe2.length(),0 );
		
	
	}
	
}