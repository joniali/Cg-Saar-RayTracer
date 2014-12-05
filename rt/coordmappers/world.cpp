#include <rt\coordmappers\world.h>

namespace rt
{
	WorldMapper::WorldMapper()
	{
		wScale = Float4::rep(1.0);
	}
	WorldMapper::WorldMapper(const Float4& scale)
	{
		wScale = scale;
	}
	Point WorldMapper::getCoords(const Intersection& hit) const
	{
		return Point(Float4(hit.hitPoint()) * wScale);
	}
}