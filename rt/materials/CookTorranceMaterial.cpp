#include <rt\materials\CookTorranceMaterial.h>



namespace rt

{
	CookTorranceMaterial::CookTorranceMaterial(Texture* specular, float eta, float kappa, float roughnessx,  float roughnessy)
	{
		pSpecular = specular;
		mEta = eta;
		mKappa = kappa;
		ex = roughnessx;
		ey = roughnessy;

	}
	RGBColor CookTorranceMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const
	{
		Vector H = ((-1 * inDir) + outDir).normalize();

		
		//float G = Geometry(normal,outDir,inDir,H);

		float e = (ex * H.x * H.x + ey * H.y * H.y) / (1 - dot(H, normal.normalize())*dot(H, normal.normalize()));
		float D = sqrt((ex + 2.0f) * (ey + 2.0f))*powf(dot(H, normal.normalize()), ex) / (2 * pi);

		//float D = (ex + 2)*pow(dot(H, normal.normalize()), ex) / (2 * pi);//isotropic

		float term1 = mEta*mEta + mKappa *mKappa;
		float costerm = dot((inDir.normalize()), normal.normalize());
		float tempTerm = 2 * mEta * costerm;
		float polarizedLighParallell = (term1* costerm *costerm - tempTerm + 1) / (term1* costerm *costerm + tempTerm + 1);
		float polarizedLightPerperndicular = (term1 - tempTerm + costerm *costerm) / (term1 + tempTerm + costerm *costerm);
		float Fr = (polarizedLighParallell + polarizedLightPerperndicular) * 0.5;
		if (Fr > 1.0)
			Fr = 1.0;
		if (Fr < 0.0)
			Fr = 0.0;

		float Rs = (D*Fr) / (pi*dot(normal.normalize(), outDir.normalize())*dot(normal.normalize(), (-1 * inDir).normalize()));
		//RGBColor ret = RGBColor::rep(Rs);
		RGBColor ret = pSpecular->getColor(texPoint)*Rs;
		return ret;

	}
	float CookTorranceMaterial::Geometry(const Vector& normal, const Vector& outDir, const Vector& inDir, const Vector& H)
	{
		float Shadowing = 2 * dot(H, normal.normalize())*dot(normal.normalize(), (-1 * inDir).normalize()) / dot(outDir.normalize(), H);
		float Masking = 2 * dot(H, normal.normalize())*dot(normal.normalize(), outDir.normalize()) / dot(outDir.normalize(), H);
		return  min(1.0f, min(Shadowing, Masking));
	}
	RGBColor CookTorranceMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const
	{
		return RGBColor::rep(0.0f);
	}
	Material::SampleReflectance CookTorranceMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const
	{
		SampleReflectance *ret = new SampleReflectance();

		return *ret;
	}

	Material::Sampling CookTorranceMaterial::useSampling() const
	{
		return Material::SAMPLING_NOT_NEEDED;
	}
}