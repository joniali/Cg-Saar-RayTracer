#include <rt\intersection.h>

namespace rt{

	 Intersection Intersection::failure(){
		Intersection ret;
		ret.intersected=false;
		return ret;
	
	}
	 Intersection::Intersection(float distance, const Ray& ray, const Solid* solid, const Vector& normal, const Point& uv)
	 {
		 this->distance=distance;
		 this->ray=ray;
		 this->solid=solid;
		 this->inormal=normal;
		 this->iuv=uv;
	 
	 }
	 Point Intersection::hitPoint() const
	 {
		 return ray.getPoint(distance);
	 
	 }

	  Vector Intersection::normal() const{
		  return inormal;
	  }
	  Point Intersection::local() const
	  {
		return ray.getPoint(distance);
	  }
	 Intersection::operator bool()
	 {
		return intersected;
	 } 
}
