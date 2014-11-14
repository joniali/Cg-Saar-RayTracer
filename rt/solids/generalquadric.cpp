#include <rt\solids\generalquadric.h>

namespace rt
{
	GeneralQuadric::GeneralQuadric( float params[10], CoordMapper* texMapper , Material* material ){
		
		a=params[0];
		b=params[1];
		c=params[2];
		d=params[3];
		e=params[4];
		f=params[5];
		g=params[6];
		h=params[7];
		i=params[8];
		j=params[9];
	}
	 Point GeneralQuadric::sample() const
	{
		return Point(0,0,0);
	}
	float GeneralQuadric::getArea() const
	{
		return FLT_MAX;
	} 

	 Intersection GeneralQuadric::intersect(const Ray& ray, float previousBestDistance) const
	 {
		/* Compute quadratic formula components for general quadric, as computed in exercise 3 */

		 float xd=ray.d.x,yd=ray.d.y,zd=ray.d.z,xo=ray.o.x,yo=ray.o.y,zo=ray.o.z;
	

		 float sqterms = a*xd*xd + b*yd*yd + c*zd*zd + d*xd*yd +e*xd*zd +f*yd*zd;

		 float linterms=2*a*xo*xd + 2*b*yo*yd + 2*c*zo*zd +  d*xo*xd + d*yo*xd + e*xo*zd + e* zo*xd + f *(yo*zd+zo*yd) + g*xd + h*yd + i*zd;

		 float constants=a*xo*xo + b * yo*yo + c*zo*zo + d* xo*yo + e*xo*zo + f*yo*zo + g* xo + h*yo+ i*zo+ j;

		 float t;
		 
		 if(sqterms==0)
		 {
			if(linterms==0.0)
				return Intersection::failure();
			else
			 {
				 t=-constants/linterms;
			
				 if(t<0||t>previousBestDistance)
					 return Intersection::failure();
				 else {
					 Point p= ray.getPoint(t);
					 return Intersection(t,ray,this,getNormal(p),p);
				 }
			  }
		 
		 }
		 else
		 {
			 float inner=linterms*linterms- 4*sqterms*constants;
			if(inner<0)
				return Intersection::failure();
			
			float t1=(-linterms+sqrt(inner))/(2*sqterms);
			float t2=(-linterms-sqrt(inner))/(2*sqterms);

			float t=min(t1,t2);

			if(t<0)
			{
				t=max(t1,t2);
				if(t<0 ||t>previousBestDistance)
					return Intersection::failure();
				Point p= ray.getPoint(t);
				 return Intersection(t,ray,this,getNormal(p),p);
			}
			if(t>previousBestDistance)
				return Intersection::failure();
			else
			{
				Point p= ray.getPoint(t);
				return Intersection(t,ray,this,getNormal(p),p);
			}
		 
		 }

		
	 }

	 Vector GeneralQuadric::getNormal(Point& p) const
	 {
		 /* normalx = 2Ax + Ez+ Fy+ G
		 normaly= 2By+ Dz+ Fx+ H
		 normalz= 2Cz+ Dy+ Ex+ I*/
		 float normalx=2*a*p.x + e*p.z + d*p.y + g;
		 float normaly=2*b*p.y+ f*p.z + d * p.x + h;
		 float normalz= 2*c*p.z+ f*p.y+ + e*p.x+ i;

		 return Vector(normalx, normaly, normalz).normalize();

	 }
	 BBox GeneralQuadric::getBounds() const
	 {
	 
		 return BBox();
	 }
}