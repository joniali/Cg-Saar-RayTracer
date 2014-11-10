#include <rt\bbox.h>

namespace rt {

	BBox BBox::empty()
	{	
		BBox b=BBox();
		b.bbEmpty=true;
		 return b;
	}
	BBox BBox::full()
	{
		Point mint=Point(FLT_MIN,FLT_MIN,FLT_MIN);
		Point maxt=Point(FLT_MAX,FLT_MAX,FLT_MAX);
		return BBox(mint,maxt);
	}
	bool BBox::isUnbound()
	{	
		Point testmin= rt::min(min,max);
		Point testmax=rt::max(min,max);
		return (testmin.x==FLT_MIN ||testmin.y==FLT_MIN ||testmin.z==FLT_MIN ||testmax.x==FLT_MAX ||testmax.y==FLT_MAX ||testmax.z==FLT_MAX) ? true : false;	
	}
	void BBox::extend(const Point& point)
	{
		min=rt::min(min,point);
		max=rt::max(max,point);
		
	}
	void BBox::extend(const BBox& bbox)
	{
		min=rt::min(min,bbox.min);
		max=rt::max(max,bbox.max);
	}
	std::pair<float,float> BBox::intersect(const Ray& ray) const
	{
		if (bbEmpty||ray.d.x==0||ray.d.y==0||ray.d.z==0) return std::pair<float,float> (10.0f,0.0f);
	
		
		float t0x = (min.x - ray.o.x) / ray.d.x;
		float t1x = (max.x - ray.o.x) / ray.d.x;
		
		float t0y = (min.y - ray.o.y) / ray.d.y;
		float t1y = (max.y - ray.o.y) / ray.d.y;

		float t0z = (min.z - ray.o.z) / ray.d.z;
		float t1z = (max.z - ray.o.z) / ray.d.z;
		
		float t0 = std::max(std::max(t0x, t0y), t0z);

		float t1 = std::min(std::min(t1x, t1y), t1z);

	return std::pair<float,float>(t0,t1);
	}
}