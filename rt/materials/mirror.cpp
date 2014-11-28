#include<rt\materials\mirror.h>

namespace rt
{

	MirrorMaterial::MirrorMaterial(float eta, float kappa)
	{
		mEta = eta;
		mKappa = kappa;
	}
	RGBColor MirrorMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const

	{
		float term1 = mEta*mEta + mKappa *mKappa;
		float costerm = dot((inDir.normalize()), normal.normalize());
		
		float tempTerm = 2 * mEta * costerm;
		
		float polarizedLighParallell = (term1* costerm *costerm - tempTerm + 1) / (term1* costerm *costerm + tempTerm + 1);
		float polarizedLightPerperndicular = (term1 - tempTerm + costerm *costerm) / (term1 + tempTerm + costerm *costerm);

		float Fr = (polarizedLighParallell + polarizedLightPerperndicular) * 0.5;
		// fresnel terms should be between 0 and one
		if (Fr > 1)
			Fr = 1.0;
		if (Fr < 0)
			Fr = 0.0;
		
		return RGBColor::rep(Fr);
		
	}
	Material::Sampling MirrorMaterial::useSampling() const
	{
		return Material::SAMPLING_ALL;
	}
	Material::SampleReflectance MirrorMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const
	{
		SampleReflectance *ret = new SampleReflectance();
		ret->direction = 2 * dot(normal, outDir) * normal - outDir;
		ret->reflectance = getReflectance(texPoint, normal, outDir,ret->direction);

		return *ret;
	}
	RGBColor MirrorMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const
	{
		return RGBColor::rep(0.0f);
	}
}