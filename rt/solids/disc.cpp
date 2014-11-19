#include <rt\solids\disc.h>

namespace rt{

	Disc::Disc(const Point& center, const Vector& normal, float radius, CoordMapper* texMapper, Material* material) :Solid(texMapper, material)
	{
		dcenter=center;
		dradius=radius;
		dtexMapper=texMapper;
		dmaterial=material;
		dnormal=normal.normalize();
	}
	Intersection Disc::intersect(const Ray& ray, float previousBestDistance) const
	{
	
		float denom= dot(ray.d,dnormal);

		if(denom==0.0) return Intersection::failure();

		float t= dot((dcenter-ray.o),dnormal)/denom;

		Point p=ray.getPoint(t);
		if(t>previousBestDistance ||t<0 || (p-dcenter).length()>dradius) return Intersection::failure();

		return Intersection(t,ray,this,dnormal,p);


	}
	Point Disc::sample() const
	{
		return Point(0,0,0);
	}
	float Disc::getArea() const
	{
		return pi*dradius*dradius;
	} 

	BBox Disc::getBounds() const
	{
		float ex = sqrt(dnormal.y*dnormal.y + dnormal.z + dnormal.z);
		float ey = sqrt(dnormal.x*dnormal.x + dnormal.z + dnormal.z);
		float ez = sqrt(dnormal.x*dnormal.x + dnormal.y + dnormal.y);
		Vector e(ex, ey, ez);
		return BBox(dcenter - dradius*e, dcenter - dradius*e);
	
	}
}