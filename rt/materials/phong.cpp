#include <rt\materials\phong.h>

namespace rt

{
	PhongMaterial::PhongMaterial(Texture* specular, float exponent)
	{
		pSpecular = specular;
		pExponent = exponent;

	}
	RGBColor PhongMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const
	{
		Vector perfectReflection = 2.0 * dot((-1 * inDir).normalize(), normal.normalize())*normal.normalize() + inDir.normalize();
		float cosineterm = abs(dot(perfectReflection.normalize(), outDir.normalize()));
		if (cosineterm < 0) return RGBColor::rep(0.0f);

		RGBColor ret = pSpecular->getColor(texPoint) * powf(cosineterm,pExponent)*(pExponent + 2) / (2 * pi);
		return ret;
		
	}
	RGBColor PhongMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const
	{
		return RGBColor::rep(0.0f);
	}
	Material::SampleReflectance PhongMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const
	{
		SampleReflectance *ret = new SampleReflectance();

		return *ret;
	}

	Material::Sampling PhongMaterial::useSampling() const
	{
		return Material::SAMPLING_NOT_NEEDED;
	}
}