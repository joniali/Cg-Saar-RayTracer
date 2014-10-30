#include <rt/ray.h>
#include <core\point.h>



namespace rt{

	
	Ray::Ray(const Point& o, const Vector& d){
	
	this->o=o;
	this->d=d.normalize();
	
	}
	Point Ray::getPoint(float distance) const
	{
		return Point(o + distance*d);//d.x,o.y+distance*d.y,o.z+distance*d.z);
	}
}