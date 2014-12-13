#include <rt\intersection.h>
#include <rt\primitive.h>
#include <rt\solids\solid.h>
#include <rt\bbox.h>

using namespace std;
namespace rt {
	
	struct Insider 
	{
		virtual bool inside(const Point &p)const { return false; }
	};
	class csg : public Solid
	{
	private:
		struct csgHit 
		{
			Intersection intRet;
			Solid* innerSolid;
		};

		Intersection pack(Intersection &bestRet, Solid* bestSolid) const
		{
			csgHit* hp = new csgHit;
			hp->intRet = bestRet;
			hp->innerSolid = bestSolid;
			bestRet.solid = bestSolid;
			bestRet.ray = hp->intRet.ray;
			bestRet.distance = hp->intRet.distance;
			volatile Intersection pp = bestRet;
			return bestRet;
		}


	public:
		Solid *first, *second;
		virtual bool inside(const Point &p)const { return false; };
		virtual bool isValidHit(const Point &p, bool isfirst)const = 0;
		virtual Point sample() const = 0;
		virtual float getArea() const = 0;
		virtual Intersection intersect(const Ray& _ray, float _previousBestDistance) const;
		//virtual BBox getBounds() const;
		void rebuildIndex();
	};


	class substract :public csg
	{
	public:
		substract(){}
		virtual bool inside(const Point &p)const;
		virtual bool isValidHit(const Point &p, bool isfirst)const;
		virtual BBox getBounds() const;
		virtual Point sample() const;
		virtual float getArea() const;
		//virtual 
	};

	class add :public csg
	{
		virtual bool inside(const Point &p)const;
		virtual bool isValidHit(const Point &p, bool isfirst)const;
		virtual BBox getBounds() const;
	};

	class intersect :public csg
	{
		virtual bool inside(const Point &p)const;
		virtual bool isValidHit(const Point &p, bool isfirst)const;
		virtual BBox getBounds() const;
	};

	class difference :public csg
	{
		virtual bool inside(const Point &p)const;
		virtual bool isValidHit(const Point &p, bool isfirst)const;
		virtual BBox getBounds() const;
	};
}