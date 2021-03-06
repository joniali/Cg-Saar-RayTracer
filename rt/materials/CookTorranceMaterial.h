#ifndef CG1RAYTRACER_MATERIALS_COOKTORRANCE_HEADER
#define CG1RAYTRACER_MATERIALS_COOKTORRANCE_HEADER

#include <rt/materials/material.h>
#include <rt/textures/texture.h>
#include <algorithm>
#include <core\scalar.h>
namespace rt {

	class CookTorranceMaterial : public Material {
	public:
		CookTorranceMaterial(Texture* specular, float eta, float kappa, float roughnessx, float roughnessy);
		virtual RGBColor getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const;
		virtual RGBColor getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const;
		virtual SampleReflectance getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const;
		virtual Sampling useSampling() const;
		virtual float Geometry(const Vector& normal, const Vector& outDir, const Vector& inDi, const Vector& half);
	private:
		Texture *pSpecular;
		float pExponent,mEta, mKappa,ex,ey;
	};

}

#endif
