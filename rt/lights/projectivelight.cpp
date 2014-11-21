#include <rt\lights\projectivelight.h>
#include <rt\ray.h>
rt::RGBColor a1computeColor(rt::uint x, rt::uint y, rt::uint width, rt::uint height);
rt::RGBColor a2computeColor(const rt::Ray& r);
namespace rt

{

	ProjectiveLight::ProjectiveLight(const Point& position, const Vector& direction, float angle, float exp, const RGBColor& intensity)
	{

		lDirection = direction.normalize();
		lposition = position;
		pangle = angle;
		pexp = exp;
		lIntensity = intensity;
	}
	LightHit ProjectiveLight::getLightHit(const Point& p) const
	{
		LightHit *lh = new LightHit();
		lh->direction = (p - lposition).normalize();
		lh->distance = (p - lposition).length();
		return *lh;
	}
	RGBColor ProjectiveLight::getIntensity(const LightHit& irr) const
	{
		//check if it lies outside the angle

		float angle = abs(acos(dot(irr.direction.normalize(), lDirection)));


		if (angle <= pangle)
		{
			int i, j;
			float aux, w, x, y;
			Vector pX, pY;
			Vector pZ = lDirection;
			Vector pup((lDirection*lDirection.length()).y, -(lDirection*lDirection.length()).x, 0);
			pX = cross(lDirection*lDirection.length(), pup).normalize();
			pY = cross(pX, pZ).normalize();
			Vector sx = pX*(tan(pangle / 2));
			Vector sy = pY*(tan(pangle / 2));
			//w = 2*irr.distance*tan(pangle/2 );
			aux = sy.y / sy.x;

			if (sy.x*aux + sy.y != 0)
				aux = -aux;

			x = (irr.direction.z - pZ.z) / sx.z;
			y = ((irr.direction.x - pZ.x) - (x*sx.x)) / sy.x;
			i = ((x + 1) * 400 / 2) - 0.5;
			j = ((y - 1) * 400 / -2) - 0.5;
			RGBColor inten = a1computeColor(i, j, 400, 400)*max(lIntensity.r, lIntensity.g, lIntensity.b);
			//Ray r(lposition, irr.direction.normalize());
			//RGBColor inten = a2computeColor(r)*max(lIntensity.r,lIntensity.g,lIntensity.b);

			return inten* (pow(abs(dot(irr.direction.normalize(), lDirection.normalize())), pexp)) / float(irr.distance*irr.distance);
		}
		return RGBColor::rep(0.0);

	}

}