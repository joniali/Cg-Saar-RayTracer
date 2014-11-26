#include <rt\materials\combine.h>

namespace rt
{
	CombineMaterial::CombineMaterial()
	{
	}
	void CombineMaterial::add(Material* material, float weight)
	{
		cmaterials.push_back(material);
		cweights.push_back(weight);
	}
	RGBColor CombineMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const
	{
		int i = 0;
		RGBColor reflectance = RGBColor::rep(0.0);
		for each (Material * m in cmaterials)
		{
			// as if sampling is not implemented only getreflectance matters
			// if it is combination we still get contribution from the materials which are not sampling all
			//this essentially gives reflections of all materials inside materials inside materials 
			//which are of type samping_not_needed
			if (m->useSampling() != Material::SAMPLING_ALL)
				reflectance = reflectance + (cweights[i] * m->getReflectance(texPoint, normal, outDir, inDir));


			i++;
		}
		return reflectance;
	}
	RGBColor CombineMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const
	{
		int i = 0;
		RGBColor emmision = RGBColor::rep(0.0);
		for each (Material * m in cmaterials)
		{

			emmision = emmision + (cweights[i] * m->getEmission(texPoint, normal, outDir));
			i++;
		}
		return emmision;
	}
	Material::SampleReflectance CombineMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const
	{
		SampleReflectance retSampleReflectance = SampleReflectance();
		int i = 0;
		// 
		for each (Material * m in cmaterials)
		{
			if (m->useSampling() != SAMPLING_NOT_NEEDED)

			{
				SampleReflectance temp = m->getSampleReflectance(texPoint, normal, outDir);

				retSampleReflectance.reflectance = temp.reflectance  *cweights[i];
				retSampleReflectance.direction = temp.direction;
				//return temp;

			}
			i++;
		}
		return retSampleReflectance;
	}
	Material::Sampling CombineMaterial::useSampling() const
	{
		// As we have to assume only one material, at most, which required sampling
		// it can either be sample_all or another combine material i.e sample_secondary
		// this just return mirror if all are mirro if it has both kind of jus combo then return secondary
		bool hascombo = false, hasMirror = false, haslambertian = false;

		for each (Material * m in cmaterials)
		{
			switch (m->useSampling())
			{
			case SAMPLING_NOT_NEEDED:
				haslambertian = true;
				break;
			case SAMPLING_ALL:
				hasMirror = true;
				break;
			case SAMPLING_SECONDARY:
				hascombo = true;
				break;
			default:
				break;
			}

		}
		if (!haslambertian && !hascombo && hasMirror)

			return SAMPLING_ALL;
		if ((haslambertian && hasMirror) || hascombo)
			return  SAMPLING_SECONDARY;
			
		return SAMPLING_NOT_NEEDED;
	}


}