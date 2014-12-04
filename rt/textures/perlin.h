#ifndef CG1RAYTRACER_TEXTURES_PERLIN_HEADER
#define CG1RAYTRACER_TEXTURES_PERLIN_HEADER

#include <core/vector.h>

#include <rt/textures/texture.h>
#include <core/color.h>
#include <core/scalar.h>
#include <vector>


namespace rt {

	class Octave
	{
	public:
		float ofrequency, oAmplitude;
	};
	class PerlinTexture : public Texture {
	public:
		PerlinTexture(const RGBColor& white, const RGBColor& black);
		void addOctave(float amplitude, float frequency);
		virtual RGBColor getColor(const Point& coord);
		virtual RGBColor getColorDX(const Point& coord);
		virtual RGBColor getColorDY(const Point& coord);
		float getNoise(Point& p);
	private: 
		RGBColor pWhite, pBlack;
		float pNoise;
		std::vector <Octave *> pOctaves;
	};

}

#endif
