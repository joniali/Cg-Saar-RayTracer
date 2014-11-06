#include <rt\solids\quad.h>

namespace rt{

Quad:: Quad(const Point& v1, const Vector& span1, const Vector& span2, CoordMapper* texMapper, Material* material)
	{
		qv1=v1;
		qspan1=span1;
		qspan2=span2;
		//qtexMapper=texMapper;
		//qmaterial=material;
		qv2=v1+span1;
		qv3=v1+span2;
		qv4=v1+span1+span2;
		qnormal=cross(qspan1,qspan2).normalize();
	
	}
	Intersection Quad::intersect(const Ray& ray, float previousBestDistance) const
	{
		float factor= dot(ray.d,qnormal);

		if(factor==0.0) return Intersection::failure();

		float t= dot((qv1-ray.o),qnormal)/factor;

		if(t>previousBestDistance || t<0) return Intersection::failure();

		Point p=ray.getPoint(t);

		/****** n = -det(PA, PQ)/det(PQ, PR)
				m = det(PA, PR)/det(PQ, PR)
				det(PA, PQ) = PA.x*PQ.y-PQ.x*PA.y
		******/
		

		float n = (qspan1.x * ( p.y - qv1.y) - p.x*qspan1.y + qv1.x*qspan1.y) / (qspan2.y * qspan1.x - qspan2.x*qspan1.y);
		if (n < 0 || n > 1) return Intersection::failure();
		float m = (p.x - qv1.x - n *qspan2.x) / qspan1.x;
		if (m < 0 || m > 1) return Intersection::failure(); 
		
		return Intersection(t,ray,this,qnormal,p);


	}
	Point Quad::sample() const
	{
		return Point(0,0,0);
	}
	float Quad::getArea() const
	{
		return FLT_MAX;
	} 
}

