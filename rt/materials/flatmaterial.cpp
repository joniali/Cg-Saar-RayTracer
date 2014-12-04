#include <rt\materials\flatmaterial.h>

namespace rt {
	FlatMaterial::FlatMaterial(Texture* texture)
	{
		fTexture = texture;
	}
	RGBColor FlatMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const
	{
		return RGBColor::rep(0.0f);
	}
	RGBColor FlatMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const
	{
		return RGBColor(fTexture->getColor(texPoint));
	}
	Material::SampleReflectance FlatMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const
	{
		SampleReflectance *ret = new SampleReflectance();

		return *ret;
	
	}

}