#include <rt\coordmappers\plane.h>

namespace rt
{
	PlaneCoordMapper::PlaneCoordMapper(const Vector& e1, const Vector& e2)
	{
		
		pnormal = cross(e1, e2);
		/*Float4 r1(e1.x, e2.x, pnormal.x, 0);
		Float4 r2(e1.y, e2.y, pnormal.y, 0);
		Float4 r3(e1.z, e2.z, pnormal.z, 0);
		Float4 r4(0, 0, 0, 1);*/
		Float4 r1(e1.x, 0, pnormal.x, 0);
		Float4 r2(0, 1, pnormal.y, 0);
		Float4 r3(0, 0, pnormal.z, 0);
		Float4 r4(0, 0, 0, 1);
		Matrix mat = Matrix(r1, r2, r3, r4);
		transition = mat.invert();
		
	}

	Point PlaneCoordMapper::getCoords(const Intersection& hit) const
	{
	
		Vector hitvector = hit.local()-Point::rep(0.0f);
		Vector projectionVector = hitvector-2*(dot(hitvector, pnormal) * pnormal);
	//	if (projectionVector.z!=0)

		//	return Point(projectionVector.x / projectionVector.z, projectionVector.y / projectionVector.z, 0);
		Float4 r1(1 - pnormal.x *pnormal.x, -pnormal.x *pnormal.y, -pnormal.x*pnormal.z, 0);
		Float4 r2(-pnormal.y*pnormal.x, 1 - pnormal.y *pnormal.y, pnormal.y*pnormal.z, 0);
		Float4 r3(-pnormal.z*pnormal.x, -pnormal.z*pnormal.y, 1 - pnormal.z*pnormal.z, 0);
		Float4 r4(0, 0, 0, 1);
		Matrix transition1 = (Matrix(r1, r2, r3, r4));

		Float4 projection = transition1 * Float4(hit.hitPoint());
		return Point(projection.x, projection.y, 0);
		//return Point(projectionVector.x, projectionVector.y, 0);
		//return projectionVector;
		
	
	}
	
}