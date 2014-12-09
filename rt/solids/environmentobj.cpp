#include "environmentobj.h"

namespace rt {

	EnvironmentSolid::EnvironmentSolid(Vector & zenith, Vector & referenceAzimuth, CoordMapper* texMapper, Material* material)
	{
		ImageTexture* environMap = new ImageTexture("models/source.png");

		this->material = new FlatMaterial(environMap);
		this->texMapper = new EnvironmentMapper(zenith, referenceAzimuth);

		Point bmin = Point(FLT_MIN, FLT_MIN, FLT_MIN);
		Point bmax = Point(FLT_MAX, FLT_MAX, FLT_MAX);
		mBBox = BBox(bmin, bmax);

		mFrame.SetFromZ(Vector(0, 0, 1));
	}

	BBox EnvironmentSolid::getBounds() const
	{
		return mBBox;
	}

	

	Intersection EnvironmentSolid::intersect(const Ray& ray, float previousBestDistance) const
	{
		float t = FLT_MAX;

		if (t > previousBestDistance) return Intersection::failure();

		return Intersection(t, ray, this, Vector(0, 0, 0), Point(0, 0, 0));
	}

	Point EnvironmentSolid::sample() const
	{
		throw new std::string("NOT IMPLEMENTED");
	}

	float EnvironmentSolid::getArea() const
	{
		throw new std::string("NOT IMPLEMENTED");
	}

	Vector EnvironmentSolid::getNormalAtPoint(const Point &p) const
	{
		throw new std::string("NOT IMPLEMENTED");
	}
}