#ifndef CG1RAYTRACER_CAMERAS_FISHEYE_HEADER
#define CG1RAYTRACER_CAMERAS_FISHEYE_HEADER

#include <rt/cameras/camera.h>
#include <core/vector.h>
#include <core/point.h>
 
namespace rt {
class FishEyeCamera : public Camera {
public:
    FishEyeCamera(
        const Point& center,
        const Vector& forward,
        const Vector& up,
        float verticalOpeningAngle,
        float horizonalOpeningAngle
        );

	  virtual Ray getPrimaryRay(float x, float y) const;
private:
	const Point & fcenter;
	const Vector &fforward,&fup;
	float fverticalOpeningAngle,fhorizontalOpeningAngle;
	Vector fX,fY,fZ,sx,sy;
};
}

#endif