#include <rt/cameras/perspective.h>
#include <rt/ray.h>
#include <math.h> 
namespace rt{

	
	PerspectiveCamera::PerspectiveCamera( const Point& center,
        const Vector& forward,
        const Vector& up,
        float verticalOpeningAngle,
        float horizonalOpeningAngle) : pcenter(center),pforward(forward),
		pup(up),
		pverticalOpeningAngle(verticalOpeningAngle),
		phorizontalOpeningAngle(horizonalOpeningAngle)
	{
		
		pZ=pforward.normalize();
		pX=cross(pforward,pup).normalize();
		pY=cross(pX,pZ).normalize();
		oppositeSide=1.0/(tan(horizonalOpeningAngle/2.0));

	}
	 Ray PerspectiveCamera::getPrimaryRay(float x,float y)const 
	{
	Vector d = (x * pX + y * pY +  oppositeSide* pZ);

		return Ray(pcenter, d);
	}
}
