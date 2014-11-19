#include <rt\groups\simplegroup.h>
#include <rt\intersection.h>

namespace rt{

	Intersection SimpleGroup::intersect(const Ray& ray, float previousBestDistance) const
	{
		Intersection ret=Intersection::failure();
		Intersection temp;
		//std::cout<<sgPrimitives.size()<<endl;


		for(int i=0;i<(int)sgPrimitives.size();i++)
		{
			temp=sgPrimitives[i]->intersect(ray,previousBestDistance);

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
	  void SimpleGroup:: add(Primitive* p)
	  {
		sgPrimitives.push_back(p);
		sgbbox.extend(p->getBounds());

	  }
	  void SimpleGroup::setMaterial(Material* m)
	  {
		sgm=m;
		for each (Primitive *p in sgPrimitives)
		{
			p->setMaterial(sgm);
		}
	  }
	   void SimpleGroup::setCoordMapper(CoordMapper* cm){
		sgcm=cm;
	  }
	   BBox SimpleGroup::getBounds() const
	   {
		  /* Point bmin(FLT_MAX);
		   Point bmax(FLT_MIN);
		   for (int i = 0; i < (int)sgPrimitives.size(); i++)
		   {
			   bmin = min(bmin, sgPrimitives[i]->getBounds.getBounds.min);
			   bmax = max(bmax, sgPrimitives[i]->getBounds.getBounds.max);
		   }
		   return BBox(bmin, bmax);*/
		   return sgbbox;

	   }
}