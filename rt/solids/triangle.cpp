#include <rt\solids\triangle.h>

namespace rt{

Triangle::Triangle(Point vertices[3], CoordMapper* texMapper, Material* material)
{
	tvertices[0]=vertices[0];
	tvertices[1]=vertices[1];
	tvertices[2]=vertices[2];
	//ttexMapper=texMapper;
	//tmaterial=material;

}
 Triangle::Triangle(const Point& v1, const Point& v2, const Point& v3, CoordMapper* texMapper, Material* material)
 {
	tvertices[0]=v1;
	tvertices[1]=v2;
	tvertices[2]=v3;
 }
  Intersection Triangle::intersect(const Ray& ray, float previousBestDistance) const
  {
  Vector a,b,c,rayO;
  a=tvertices[0]-Point(0,0,0);
  b=tvertices[1]-Point(0,0,0);
  c=tvertices[2]-Point(0,0,0);
  rayO=ray.o-Point(0,0,0);
  /*Vector nab=cross(tvertices[1]-ray.o,tvertices[0]-ray.o);
  Vector nbc=cross(tvertices[2]-ray.o,tvertices[1]-ray.o);
  Vector nca=cross(tvertices[0]-ray.o,tvertices[2]-ray.o);*/
  Vector nab=cross(b-rayO,a-rayO);
  Vector nbc=cross(c-rayO,b-rayO);
  Vector nca=cross(a-rayO,c-rayO);
  if(dot(nab,ray.d)>0 && dot(nbc,ray.d)>0 &&dot(nca,ray.d)>0)
  {
	Vector vect0 = (b - a).normalize();
	Vector vect1 = (c - a).normalize();

	Vector tnormal = cross(vect0, vect1).normalize(); // triangle normal or vertix a
	
	float factor= dot(ray.d,tnormal);
	if(factor==0.0) return Intersection::failure();
		float t= dot((tvertices[0]-ray.o),tnormal)/factor;

		if(t>previousBestDistance || t<0) return Intersection::failure();

		Point p=ray.getPoint(t);
		// here instead of p i can also give barycentric coordinates but why should I
	return Intersection(t,ray,this,tnormal,p);
  }
  return Intersection::failure();
  }
  Point Triangle::sample() const
	{
		
		return Point(0,0,0);
	}
	float Triangle::getArea() const
	{
		return FLT_MAX;
	} 
}