#include <rt\materials\lambertian.h>
namespace rt
{

	LambertianMaterial::LambertianMaterial(Texture* emission, Texture* diffuse)
	{
		lEmissioin = emission;
		lDiffuse = diffuse;

	}
	RGBColor LambertianMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const
	{

		float refValue = 1 / pi;

		return lDiffuse->getColor(texPoint)*refValue;
	}
	RGBColor LambertianMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const
	{
		return lEmissioin->getColor(texPoint);
	}
	Material::Sampling LambertianMaterial::useSampling() const
	{
		return Material::SAMPLING_NOT_NEEDED;

	}
	Material::SampleReflectance LambertianMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const
	{
		SampleReflectance *ret = new SampleReflectance();

		return *ret;
	}


}