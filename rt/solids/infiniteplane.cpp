#include <rt\solids\infiniteplane.h>

namespace rt{

	InfinitePlane::InfinitePlane(const Point& origin, const Vector& normal, CoordMapper* texMapper, Material* material)
	{
		iporigin=origin;
		ipnormal=normal.normalize();
		iptexMapper=texMapper;
		ipmaterial=material;
	
	}
	Intersection InfinitePlane::intersect(const Ray& ray, float previousBestDistance) const
	{
		float factor= dot(ray.d.normalize(),ipnormal);

		if(factor==0.0) return Intersection::failure();

		float t= dot((iporigin-ray.o),ipnormal)/factor;

		if(t>previousBestDistance || t<0) return Intersection::failure();

		Point p=ray.getPoint(t);

		return Intersection(t,ray,this,ipnormal,p);


	}
	Point InfinitePlane::sample() const
	{
		return Point(0,0,0);
	}
	float InfinitePlane::getArea() const
	{
		return FLT_MAX;
	} 
}