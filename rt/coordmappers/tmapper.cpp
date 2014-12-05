#include <rt\coordmappers\tmapper.h>

namespace rt
{

	TriangleMapper::TriangleMapper(const Point& tv0, const Point& tv1, const Point& tv2)
	{
		tmv0 = tv0;
		tmv1 = tv1;
		tmv2 = tv2;
	}
	TriangleMapper::TriangleMapper(Point ntv[3])
	{
		tmv0 = ntv[0];
		tmv1 = ntv[1];
		tmv2 = ntv[2];
	
	}
	Point TriangleMapper::getCoords(const Intersection& hit) const
	{
		Point p = hit.local();
		Float4 fv1(tmv0);
		Float4 fv2(tmv1);
		Float4 fv3(tmv2);
		Float4 res = p.x * fv1 + p.y * fv2 + p.z * fv3;
		return Point(res.x, res.y, res.z);
	
	}
}