#include "cylindrical.h"
namespace rt {
	CylindricalCoordMapper::CylindricalCoordMapper(const Point& origin, const Vector& longitudinalAxis, const Vector& polarAxis)
	{
		cOrigin = origin;
		
		cFrame.SetFromZ(longitudinalAxis);
		cLocalL = cFrame.ToLocal(longitudinalAxis);
		cYScale = cLocalL.length();
		cXScale = polarAxis.length();
		cLocalA = cFrame.ToLocal(polarAxis);
		cLocalA.z = 0; // project mLocalA to the local xy plane (which is the reference plane) - for the case that L and A are not perpendicular in the original setting
		cLocalA = cLocalA.normalize();
	}
	Point CylindricalCoordMapper::getCoords(const Intersection& hit) const
	{
		Point localHit = hit.local();
		Vector globalOrigToHit = localHit - cOrigin;
		Vector localOrigToHit = cFrame.ToLocal(globalOrigToHit);
		float phi = -atan2(localOrigToHit.y, localOrigToHit.x) / (2 * pi);
		return Point(phi / cXScale, localOrigToHit.z / cYScale, 0);
	}
}