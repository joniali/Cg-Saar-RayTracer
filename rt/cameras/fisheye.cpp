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
		fZ=fforward;
		fX=cross(fforward,fup);
		fY=cross(fX,fZ);
	}
	  Ray FishEyeCamera::getPrimaryRay(float x, float y) const{
		  float fTheta,fPhi,fr,fx,fy,fz;
		  fr=sqrtf(pow(x,2.0f)+pow(y,2.0f));
		  fPhi=atan2f(y,x);
		  fTheta=fr*(fverticalOpeningAngle/2.0);
		  fx=sin(fTheta)*cos(fPhi);
		  fy=sin(fTheta)*sin(fPhi);
		  fz=cos(fTheta);
		 Vector d = (fx *fX  + fy *fY +  fz*fforward);

		return Ray(fcenter, d);
	 }
}