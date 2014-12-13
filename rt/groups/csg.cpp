#include <rt\groups\csg.h>

using namespace std;
namespace rt {

	Intersection csg::intersect(const Ray& _ray, float _previousBestDistance)const
	{ 
		Ray ray = _ray;
		float offset = 0.f;
		float previousBestDistance = _previousBestDistance;


		enum { FIRST, SECOND, NONE } state = NONE;

		while (true)
		{
			state = NONE;
			Intersection bestRet;
			Solid* bestPrimitive = NULL;
			Intersection firstRet = first->intersect(ray, previousBestDistance);
			if (firstRet.distance < bestRet.distance && firstRet.distance > 0.0001f)
			{
				bestRet = firstRet;
				bestPrimitive = first;
				state = FIRST;
			}
			Intersection secondRet = second->intersect(ray, previousBestDistance);
			if (secondRet.distance < bestRet.distance && secondRet.distance > 0.0001f)
			{
				bestRet = secondRet;
				bestPrimitive = second;
				state = SECOND;
			}

			if (state == NONE || isValidHit(ray.d*bestRet.distance + ray.o, state == FIRST))
			{
				bestRet.distance += offset;
				return pack(bestRet, bestPrimitive);
			}

			offset += bestRet.distance;

			ray.o = ray.o + ray.d*bestRet.distance;
			if (previousBestDistance != FLT_MAX)
			{
				previousBestDistance -= bestRet.distance;
			}
		}
	}

	

	BBox substract::getBounds() const
	{
		cout << "Here again" << endl;
		return first->getBounds();
	}


	bool substract::isValidHit(const Point &p, bool isfirst)const
	{
		return !second->inside(p) && isfirst || first->inside(p) && !isfirst;
	}

	bool substract::inside(const Point &p)const
	{
		return !second->inside(p) && first->inside(p);
	}

	Point substract::sample() const
	{

		return first->sample();
	}
	float substract::getArea() const
	{
		return first->getArea();
	}
	BBox add::getBounds() const
	{

		BBox rb = first->getBounds();
		rb.extend(second->getBounds());
		return rb;
	}

	bool add::isValidHit(const Point &p, bool isfirst)const
	{
		return !second->inside(p) && isfirst || !first->inside(p) && !isfirst;
	}

	bool add::inside(const Point &p)const
	{
		return second->inside(p) || first->inside(p);
	}

	
	bool intersect::isValidHit(const Point &p, bool isfirst)const
	{
		return second->inside(p) && isfirst || first->inside(p) && !isfirst;
	}

	bool intersect::inside(const Point &p)const
	{
		return second->inside(p) && first->inside(p);
	}

	BBox intersect::getBounds() const
	{
		
		return first->getBounds();
	}
	
	bool difference::isValidHit(const Point &p, bool isfirst)const
	{
		return !second->inside(p) && isfirst || !first->inside(p) && !isfirst;
	}

	bool difference::inside(const Point &p)const
	{
		return second->inside(p) && !first->inside(p) || first->inside(p) && !second->inside(p);
	}
	BBox difference::getBounds() const
	{
		cout << "Here again" << endl;
		return first->getBounds();
	}
}