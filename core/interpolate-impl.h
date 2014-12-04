#include "interpolate.h"
#include "assert.h"

namespace rt {

	template <typename T>
	T lerp(const T& px0, const T& px1, float xPoint) {

		return px0*(1 - xPoint) + px1*(xPoint);
	}

	template <typename T>
	T lerpbar(const T& a, const T& b, const T& c, float aWeight, float bWeight) {

		return (a*aWeight + b*bWeight + c * (1 - aWeight - bWeight));

	}

	template <typename T>
	T lerp2d(const T& px0y0, const T& px1y0, const T& px0y1, const T& px1y1, float xWeight, float yWeight) {

		return (px0y0 * (1 - xWeight) *(1 - yWeight) + px0y1* (1 - xWeight) * yWeight + px1y0*(1 - yWeight) *xWeight + px1y1 *xWeight *yWeight);
	}

	template <typename T>
	T lerp3d(const T& px0y0z0, const T& px1y0z0, const T& px0y1z0, const T& px1y1z0,
		const T& px0y0z1, const T& px1y0z1, const T& px0y1z1, const T& px1y1z1,
		float xPoint, float yPoint, float zPoint) {

		return (px0y0z0 * (1 - xPoint) *(1 - yPoint) *(1 - zPoint) 
			+ px0y0z1* (1 - xPoint) * (1 - yPoint) *  zPoint
			+ px0y1z0* (1 - xPoint) * yPoint * (1 - zPoint)
			+ px0y1z1* (1 - xPoint) * yPoint * zPoint
			+ px1y0z0*(1 - yPoint) *xPoint *(1 - zPoint) 
			+ px1y0z1*xPoint * (1 - yPoint) * zPoint
			+ px1y1z0 *xPoint *yPoint * (1 - zPoint)
			+ px1y1z1*  yPoint *xPoint * zPoint);

	}

}

