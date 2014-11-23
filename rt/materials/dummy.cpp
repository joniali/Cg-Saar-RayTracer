#include <rt\materials\dummy.h>


namespace rt 

{
	DummyMaterial::DummyMaterial()
	{}

	RGBColor DummyMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const
	{
	
		float cosineterm = std::abs(dot(normal, inDir));
		return RGBColor(cosineterm, cosineterm, cosineterm);
		
	}
	RGBColor DummyMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const
	{
		return RGBColor::rep(0.0f);
		
	
	}

	Material::SampleReflectance DummyMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const
	{
		SampleReflectance *ret= new SampleReflectance();

		return *ret;
	}
	
}