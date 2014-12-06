#include "spherical.h"
namespace rt {
	SphericalCoordMapper::SphericalCoordMapper() { }
	SphericalCoordMapper::SphericalCoordMapper(const Point& origin, const Vector& zenith, const Vector& azimuthRef)
	{
		sFrame.SetFromZ(zenith);
		sLocalZenith = sFrame.ToLocal(zenith);
		sLocalReferenceAzimuth = sFrame.ToLocal(azimuthRef);
		sXScale = azimuthRef.length();
		sYScale = zenith.length();
		sOrigin = origin;
	}
	Point SphericalCoordMapper::getCoords(const Intersection& hit) const
	{
		Point local = hit.local();
		Vector origToHit = local - sOrigin;
		Vector localOrigToHit = sFrame.ToLocal(origToHit);
		Vector projectedLocalOrigToHit = localOrigToHit;
		projectedLocalOrigToHit.z = 0;
		projectedLocalOrigToHit = projectedLocalOrigToHit.normalize();
		float phi = -atan2(localOrigToHit.y, localOrigToHit.x) / (2 * pi);
		//if (phi < 0) phi = phi + 2 * pi;
		float cosTheta = dot(localOrigToHit.normalize(), sLocalZenith.normalize());
		float theta = acos(cosTheta) / (pi);
		return Point(phi / sXScale, theta / sYScale, 0);
	}
}