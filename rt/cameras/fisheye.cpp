#include <rt/cameras/fisheye.h>
#include <rt/ray.h>
#include <math.h> 

namespace rt{

	FishEyeCamera::FishEyeCamera(  const Point& center,
        const Vector& forward,
        const Vector& up,
        float verticalOpeningAngle,
        float horizonalOpeningAngle
        ): fcenter(center),fforward(forward),
		fup(up),
		fverticalOpeningAngle(verticalOpeningAngle),
		fhorizontalOpeningAngle(horizonalOpeningAngle)
	{
		fZ=fforward.normalize();
		fX=cross(fforward,fup).normalize();
		fY=cross(fX,fZ).normalize();
	}
	  Ray FishEyeCamera::getPrimaryRay(float x, float y) const{
		  float fTheta,fPhi,fr,fx,fy,fz;
		  fr=sqrtf(x*x+y*y);
		  fPhi=atan2f(y,x);
		  fTheta=fr*(fverticalOpeningAngle/2.0f);
		  fx=sin(fTheta)*cos(fPhi);
		  fy=sin(fTheta)*sin(fPhi);
		  fz=cos(fTheta);
		 Vector d = (fx *fX  + fy *fY +  fz*fZ);

		return Ray(fcenter, d);
	 }
}