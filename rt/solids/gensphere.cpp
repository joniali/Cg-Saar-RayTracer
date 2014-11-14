#include <rt\solids\gensphere.h>


namespace rt
{
	GenSphere::GenSphere(const Point& center, float radius, CoordMapper* texMapper, Material* material)
	{
		gscenter=center;
		gsradius=radius;
		a=b=c=1;
		d=e=f=0;
		g=-2*gscenter.x;
		h=-2*gscenter.y;
		i=-2*gscenter.z;
		j=gscenter.x* gscenter.x +
		  gscenter.y* gscenter.y +
		  gscenter.z* gscenter.z -
		  gsradius*gsradius;
	
	}

	BBox GenSphere::getBounds() const
	{

		return BBox(gscenter - (gsradius* Point(1, 1, 1)*sqrt(2.0)) + Point(0, 0, 0), gscenter - (gsradius* Point(-1, -1, -1)*sqrt(2.0)) + Point(0, 0, 0));
	}




}