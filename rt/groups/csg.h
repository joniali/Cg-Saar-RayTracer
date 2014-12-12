#include <rt\intersection.h>
#include <rt\primitive.h>
#include <rt\solids\solid.h>
#include <rt\bbox.h>

//baseclass for CSG
using namespace std;
namespace rt {
	
	struct Insider :public Solid
	{
		virtual bool inside(const Point &p)const { return false; }
	};
	class base : public Insider
	{
	private:
		struct CSGBaseHit 
		{
			Intersection intRet;
			Solid* innerPrimitive;
		};

		Intersection pack(Intersection &bestRet, Solid* bestPrimitive) const
		{
			CSGBaseHit* hp = new CSGBaseHit;
			hp->intRet = bestRet;
			hp->innerPrimitive = bestPrimitive;
			bestRet.solid = bestPrimitive;
			bestRet.ray = hp->intRet.ray;
			bestRet.distance = hp->intRet.distance;
			volatile Intersection pp = bestRet;// whyever
			return bestRet;
		}


	public:
		Insider *first, *second;
		virtual bool inside(const Point &p)const { return false; };
		virtual bool isValidHit(const Point &p, bool isfirst)const = 0;
		//virtual SmartPtr<Shader> getShader(Intersection _intData) const;
		virtual Intersection intersect(const Ray& _ray, float _previousBestDistance) const;
		virtual BBox getBbox() const{};

		//Rebuilds the BVH and updated m_nonIdxPrimitives
		void rebuildIndex();
	};


	class substract :public base
	{
		virtual bool inside(const Point &p)const;
		virtual bool isValidHit(const Point &p, bool isfirst)const;
		virtual BBox getBbox() const;
	};

	class add :public base
	{
		virtual bool inside(const Point &p)const;
		virtual bool isValidHit(const Point &p, bool isfirst)const;
		virtual BBox getBbox() const;
	};

	class intersect :public base
	{
		virtual bool inside(const Point &p)const;
		virtual bool isValidHit(const Point &p, bool isfirst)const;
		virtual BBox getBbox() const;
	};

	class difference :public base
	{
		virtual bool inside(const Point &p)const;
		virtual bool isValidHit(const Point &p, bool isfirst)const;
		virtual BBox getBbox() const;
	};
}