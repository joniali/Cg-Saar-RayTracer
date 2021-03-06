#include <rt\intersection.h>

namespace rt{

	 
	 Intersection::Intersection(float distance, const Ray& ray, const Solid* solid, const Vector& normal, const Point& uv)
	 {
		 this->distance=distance;
		 this->ray=ray;
		 this->solid=solid;
		 this->inormal=normal;
		 this->iuv=uv;
		 intersected=true;
	 
	 }
	 Point Intersection::hitPoint() const
	 {
		 return ray.getPoint(distance);
	 
	 }

	 Intersection Intersection::failure(){
		Intersection ret;
		ret.intersected=false;
		
		return ret;
	
	}
	  Vector Intersection::normal() const{
		  return inormal;
	  }
	  Point Intersection::local() const
	  {
		return iuv;
	  }
	 Intersection::operator bool()
	 {
		return intersected;
	 } 
}
