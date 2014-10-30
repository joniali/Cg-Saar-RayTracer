#include <rt/cameras/orthographic.h>
#include <rt/ray.h>
namespace rt{

	OrthographicCamera::OrthographicCamera(
        const Point& center,
        const Vector& forward,
        const Vector& up,
        float scaleX,
        float scaleY
        ) : ocenter(center),oforward(forward),
		oup(up),oscaleX(scaleX),oscaleY(scaleY)
	{
	
		oZ=oforward;
		oX=cross(oforward,oup);
		oY=cross(oX,oZ);
		sx=oX*(oscaleX/2.0);
		sy=oY*(oscaleY/2.0);
	}

	 Ray OrthographicCamera::getPrimaryRay(float x, float y) const{
		Point o = ocenter+(x *sx  + y * sy  +  oZ);

		return Ray(o, oforward);
	
	}

}