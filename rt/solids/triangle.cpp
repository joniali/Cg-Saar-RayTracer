#include <rt\solids\triangle.h>

namespace rt{

	Triangle::Triangle(Point vertices[3], CoordMapper* texMapper, Material* material) :Solid(texMapper, material)
	{
		tvertices[0]=vertices[0];
		tvertices[1]=vertices[1];
		tvertices[2]=vertices[2];
		
		//ttexMapper=texMapper;
		//tmaterial=material;

	}
	Triangle::Triangle(const Point& v1, const Point& v2, const Point& v3, CoordMapper* texMapper, Material* material) :Solid(texMapper, material)
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
		float dotab=dot(nab,ray.d);
		float dotbc=dot(nbc,ray.d);
		float dotca=dot(nca,ray.d);
		
		if((dotab>0 && dotbc>0 && dotca>0) ||(dotab<0 && dotbc<0 && dotca<0))
		{
			Vector vect0 = (b - a);
			Vector vect1 = (c - a);

			Vector tnormal = cross(vect0, vect1).normalize(); // triangle normal on vertix a

			float factor= dot(ray.d,tnormal);
			if(abs(factor-0.0)<0.00001) 
				return Intersection::failure();

			float sumIv = 1.0f / (dotab + dotbc + dotca);
			float l2 = dotab * sumIv;
			float l0 = dotbc * sumIv;
			float l1 = dotca * sumIv;

			Point pp = l0 * tvertices[0] + l1 * tvertices[1] + l2 * tvertices[2];

			Vector direction = pp - ray.o;

			float orientation = dot(direction, ray.d);
			float distance = direction.length();

			if(distance>previousBestDistance || orientation<0.000001) 
				return Intersection::failure();

			//Point p=ray.getPoint(distance);
			// here instead of p i can also give barycentric coordinates but why should I
			return Intersection(distance,ray,this,tnormal,Point(l0,l1,l2));
		}
		return Intersection::failure();
	}
	Point Triangle::sample() const
	{

		return Point(0,0,0);
	}
	float Triangle::getArea() const
	{
		return (1/2) * cross(tvertices[1]-tvertices[0],tvertices[2]-tvertices[0]).length();;
	} 
	BBox Triangle::getBounds() const{
	
	return BBox(min(min(tvertices[0],tvertices[1]),tvertices[2]),max(max(tvertices[0],tvertices[1]),tvertices[2]));
	}
}