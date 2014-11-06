#include <rt/cameras/environment.h>
#include <rt/ray.h>
#include <math.h> 


namespace rt{

	EnvironmentCamera::EnvironmentCamera(  const Point& center,
        const Vector& forward,
        const Vector& up,
        float verticalOpeningAngle,
        float horizonalOpeningAngle
        ): ecenter(center),eforward(forward),
		eup(up),
		everticalOpeningAngle(verticalOpeningAngle),
		ehorizontalOpeningAngle(horizonalOpeningAngle)
	{
		eZ=eforward.normalize();
		eX=cross(eforward,eup).normalize();
		eY=cross(eX,eZ).normalize();
	}
	  Ray EnvironmentCamera::getPrimaryRay(float x, float y) const{
		  float eTheta,ePhi,ex,ey,ez;
		  ePhi=x*(ehorizontalOpeningAngle/2.0);
		  eTheta=y*(everticalOpeningAngle/2.0);
		  ex=sin(eTheta)*cos(ePhi);
		  ey=sin(eTheta)*sin(ePhi);
		  ez=cos(eTheta);
		 Vector d = (ex *eX  + ey *eY +  ez*eZ);

		return Ray(ecenter, d);
	 }
}