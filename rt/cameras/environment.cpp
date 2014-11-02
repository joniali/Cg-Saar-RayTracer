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
		eZ=eforward;
		eX=cross(eforward,eup);
		eY=cross(eX,eZ);
	}
	  Ray EnvironmentCamera::getPrimaryRay(float x, float y) const{
		  float eTheta,ePhi,er,ex,ey,ez;
		  er=sqrtf(pow(x,2.0f)+pow(y,2.0f));
		  ePhi=x*(ehorizontalOpeningAngle/2.0);
		  eTheta=y*(everticalOpeningAngle/2.0);
		  ex=cos(eTheta)*cos(ePhi);
		  ey=cos(eTheta)*sin(ePhi);
		  ez=cos(eTheta);
		 Vector d = (ex *eX  + ey *eY +  ez*eforward);

		return Ray(ecenter, d);
	 }
}