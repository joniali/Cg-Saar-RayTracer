#include <rt\solids\sphere.h>

namespace rt {
	Sphere::Sphere(const Point& center, float radius, CoordMapper* texMapper, Material* material) :Solid(texMapper, material)
	 {
		
	 scenter=center;
	 sradius=radius;
	// stexMapper=texMapper;
	// smaterial=material;
	
	 }
	 Intersection Sphere::intersect(const Ray& ray, float previousBestDistance) const{
	 
		 if(sradius==0.0)
			  return Intersection::failure();
		 // breaking down the quadratic equation we get by plugging in the ray 
		 // in sphere equation 
		 
		 float a= dot(ray.d,ray.d);
		 float b= 2*(dot (ray.d,(ray.o-scenter)));
		 float c=dot ((ray.o-scenter),(ray.o-scenter))- (sradius*sradius);
		 float t;
		 if(a==0)
		 {
			 if(b==0.0)
				return Intersection::failure();
			 else
			 {
				 t=-c/b;
			
				 if (t<0.0001 || t>previousBestDistance)
					 return Intersection::failure();
				 else {
					 Point p= ray.getPoint(t);
					 return Intersection(t,ray,this,(p-scenter).normalize(),p);
				 }
			  }

		 }
		 else
		 {
			float inner=b*b-4*a*c;
			if(inner<0)
				return Intersection::failure();
			
			float t1=(-b+sqrt(inner))/(2*a);
			float t2=(-b-sqrt(inner))/(2*a);

			float t=min(t1,t2);

			if (t<0.0001)
			{
				t=max(t1,t2);
				if (t<0.001 || t>previousBestDistance)
					return Intersection::failure();
				Point p= ray.getPoint(t);
				 return Intersection(t,ray,this,(p-scenter).normalize(),p);
			}
			if(t>previousBestDistance)
				return Intersection::failure();
			else
			{
				Point p= ray.getPoint(t);

				return Intersection(t,ray,this,(p-scenter).normalize(),p);
			}
		 
		 }
		 
		
		 
	 
	 }
	 Point Sphere::sample() const
	{
		 
		return Point(0,0,0);
	}
	float Sphere::getArea() const
	{
		return 4*pi*sradius*sradius;
	} 
	BBox Sphere::getBounds() const
	{
		
		return BBox (scenter-(sradius* Point(1,1,1)*sqrt(2.0))+Point(0,0,0),scenter-(sradius* Point(-1,-1,-1)*sqrt(2.0))+Point(0,0,0));
	}
}