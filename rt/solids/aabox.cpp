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
	 
		return Intersection::failure();
	 }
	 Point AABox::sample() const
	{
		return Point(0,0,0);
	}
	float AABox::getArea() const
	{
		return FLT_MAX;
	} 
}