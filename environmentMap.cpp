#include <rt\coordmappers\EnvironmentMapper.h>

namespace rt
{
	EnvironmentCoordMapper::EnvironmentCoordMapper()
	{
		wScale = Float4::rep(1.0);
	}
	EnvironmentCoordMapper::EnvironmentCoordMapper(const Float4& scale)
	{
		wScale = scale;
	}
	Point EnvironmentCoordMapper::getCoords(const Intersection& hit) const
	{
		return Point(Float4(hit.ray.d.normalize() - (2 * hit.normal()*(dot(hit.normal(),hit.ray.d.normalize())))) * wScale);
	}
	
}