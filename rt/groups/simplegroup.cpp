#include <rt\groups\simplegroup.h>
#include <rt\intersection.h>

namespace rt{

	Intersection SimpleGroup::intersect(const Ray& ray, float previousBestDistance) const
	{
		Intersection ret=Intersection::failure();
		Intersection temp;
		//std::cout<<sgPrimitives.size()<<endl;
		for(int i=0;i<sgPrimitives.size();i++)
		{
			temp=sgPrimitives.at(i)->intersect(ray,previousBestDistance);

				if(temp) // as the solid will only return the intersection if it is smaller than the previous intersections
				{
					previousBestDistance=temp.distance;
					ret=temp;
				
				}
		
		}
		//if(temp)
		return ret;
		//return Intersection::failure();
	}
	  void SimpleGroup::rebuildIndex()
	 {
	 
	 
	 }
	  void SimpleGroup::add(Primitive* p)
	  {
		sgPrimitives.push_back(p);
	  }
	  void SimpleGroup::setMaterial(Material* m)
	  {
		sgm=m;
	  }
	   void SimpleGroup::setCoordMapper(CoordMapper* cm){
		sgcm=cm;
	  }
}