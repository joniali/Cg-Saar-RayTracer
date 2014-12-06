#include <rt\coordmappers\Environmentmapper.h>
namespace rt {
	EnvironmentMapper::EnvironmentMapper(Vector & zenith, Vector & referenceAzimuth)
	{
		eFrame.SetFromZ(zenith);
		eLocalZenith = eFrame.ToLocal(zenith);
		eLocalReferenceAzimuth = eFrame.ToLocal(referenceAzimuth).normalize();
		eInitialPhasePhi = atan2(eLocalReferenceAzimuth.y, eLocalReferenceAzimuth.x);
		if (eInitialPhasePhi < 0) eInitialPhasePhi = eInitialPhasePhi + 2 * pi;
	}
	Point EnvironmentMapper::getCoords(const Intersection& hit) const
	{
		Vector localOrigToHit = eFrame.ToLocal(hit.ray.d).normalize();
		float phi = atan2(localOrigToHit.y, localOrigToHit.x) + eInitialPhasePhi;
		if (phi > 2 * pi) phi = phi - 2 * pi;
		float cosTheta = dot(localOrigToHit.normalize(), eLocalZenith.normalize());
		float theta = acos(cosTheta);
		return Point(phi / (2 * pi), theta / (pi), 0);
	}
}