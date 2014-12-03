#include <rt/cameras/perspective.h>


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
		
		sx=pX*(tan(horizonalOpeningAngle/2.0));
		sy=pY*(tan(verticalOpeningAngle/2.0));


	}
	 Ray PerspectiveCamera::getPrimaryRay(float x,float y)const 
	{
		
		 Vector d = (x *sx + y * sy + pZ);

		return Ray(pcenter, d.normalize());
	}
}
