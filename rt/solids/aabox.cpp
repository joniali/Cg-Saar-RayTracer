#include <rt\solids\aabox.h>

namespace rt {

	AABox::AABox(const Point& corner1, const Point& corner2, CoordMapper* texMapper, Material* material)
	{
		aacorner1=corner1;
		aacorner2=corner2;
		//aatexMapper=texMapper;
		//aamaterial=material;


	}
	Intersection AABox::intersect(const Ray& ray, float previousBestDistance)const
	{

		float tminx, tminy, tminz,tmaxx, tmaxy, tmaxz,tmin=-100000; 

		float a = 1.0 / ray.d.x;
		if (a >= 0) {
			tminx = (aacorner1.x - ray.o.x) /ray.d.x;
			tmaxx = (aacorner2.x - ray.o.x) /ray.d.x;
		}
		else {
			tminx = (aacorner2.x - ray.o.x) /ray.d.x;
			tmaxx = (aacorner1.x - ray.o.x) /ray.d.x;
		}

		float b = 1.0 / ray.d.y;
		if (b >= 0) {
			tminy = (aacorner1.y - ray.o.y) * b;
			tmaxy = (aacorner2.y - ray.o.y) * b;
		}
		else {
			tminy = (aacorner2.y - ray.o.y) * b;
			tmaxy = (aacorner1.y - ray.o.y) * b;
		}

		float c = 1.0 / ray.d.z;
		if (c >= 0) {
			tminz = (aacorner1.z - ray.o.z) * c;
			tmaxz = (aacorner2.z - ray.o.z) * c;
		}
		else {
			tminz = (aacorner2.z - ray.o.z) * c;
			tmaxz = (aacorner1.z - ray.o.z) * c;
		}

		float t0, t1;

		int in, out;

		if (tminx > tminy) {
			t0 = tminx;
			in = (a >= 0.0) ? 0 : 3;
		}
		else {
			t0 = tminy;
			in = (b >= 0.0) ? 1 : 4;
		}

		if (tminz > t0) {
			t0 = tminz;
			in = (c >= 0.0) ? 2 : 5;
		}

		if (tmaxx < tmaxy) {
			t1 = tmaxx;
			out = (a >= 0.0) ? 3 : 0;
		}
		else {
			t1 = tmaxy;
			out = (b >= 0.0) ? 4 : 1;
		}

		if (tmaxz < t1) {
			t1 = tmaxz;
			out = (c >= 0.0) ? 5 : 2;
		}

		Vector Normal;
		if (t0 < t1 && t1 > 0.01) { 
			if (t0 > 0.01) {
				tmin = t0;  			
				Normal = normal(in);
			}
			else {
				tmin = t1;				
				Normal = normal(out);
			}


			Point p= ray.getPoint(tmin);
			return Intersection(tmin,ray,this,Normal.normalize(),p);
		}
		else
			return  Intersection::failure();

		/*float tmin, tmax, tymin, tymax, tzmin, tzmax;
		int idi=1, ido=1;
		if (ray.d.x >= 0) {
		tmin = (aacorner1.x - ray.o.x) / ray.d.x;
		tmax = (aacorner2.x - ray.o.x) / ray.d.x;
		}
		else {
		tmin = (aacorner2.x - ray.o.x) / ray.d.x;
		tmax = (aacorner1.x - ray.o.x) / ray.d.x;
		}
		if (ray.d.y >= 0) {
		tymin = (aacorner1.y - ray.o.y) / ray.d.y;
		tymax = (aacorner2.y - ray.o.y) / ray.d.y;
		}
		else {
		tymin = (aacorner2.y - ray.o.y) / ray.d.y;
		tymax = (aacorner1.y - ray.o.y) / ray.d.y;
		}

		if ( (tmin > tymax) || (tymin > tmax) )
		return  Intersection::failure();*/

	}

	Vector AABox::normal(const int in) const {
		switch (in) {
		case 0:
			return (Vector(-1, 0, 0));
		case 1:	
			return (Vector(0, -1, 0));	
		case 2:	
			return (Vector(0, 0, -1));	
		case 3:	
			return (Vector(1, 0, 0));	
		case 4:	
			return (Vector(0, 1, 0));	
		case 5:	
			return (Vector(0, 0, 1));	
		}
	}

	Point AABox::sample() const
	{
		return Point(0,0,0);
	}
	float AABox::getArea() const
	{
		return 2*((aacorner1-aacorner2).lensqr());
	} 
	BBox AABox::getBounds() const
	{
		
		return BBox (min(aacorner1,aacorner2),max(aacorner1,aacorner2));
	}
}