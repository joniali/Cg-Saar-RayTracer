#include <rt\solids\infiniteplane.h>

namespace rt{

	InfinitePlane::InfinitePlane(const Point& origin, const Vector& normal, CoordMapper* texMapper, Material* material) : Solid(texMapper, material)
	{
		iporigin=origin;
		ipnormal=normal.normalize();
		//iptexMapper=texMapper;
		//ipmaterial=material;
		
	
	}
	Intersection InfinitePlane::intersect(const Ray& ray, float previousBestDistance) const
	{
		float factor= dot(ray.d.normalize(),ipnormal);

		if(factor==0.0) return Intersection::failure();

		float t= dot((iporigin-ray.o),ipnormal)/factor;

		if(t>previousBestDistance || t<0) return Intersection::failure();

		Point p=ray.getPoint(t);
		/*Vector vectFromOrigToSurfPoint = p - iporigin;
		Vector LocalVectFromOrigToSurfPoint = getLocal(vectFromOrigToSurfPoint); 
		Point uv(LocalVectFromOrigToSurfPoint.x, LocalVectFromOrigToSurfPoint.y, 0);*/
		return Intersection(t,ray,this,ipnormal,p);


	}
	Vector InfinitePlane::getLocal( Vector & a) const
	{
		Vector mZ = ipnormal.normalize();

		Vector tmpX = Vector(1, 0, 0);
		if (abs(mZ.x) >= 1) tmpX = Vector(0, 1, 0); 

		Vector mY = cross(mZ, tmpX).normalize();
		Vector mX = cross(mY, mZ).normalize();
		return mX * a.x + mY * a.y + mZ * a.z;
	}
	Point InfinitePlane::sample() const
	{
		return Point(0,0,0);
	}
	float InfinitePlane::getArea() const
	{
		return FLT_MAX;
	} 
	BBox InfinitePlane::getBounds() const
	{
		
		return BBox();

	}
}