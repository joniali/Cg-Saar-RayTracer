#include <rt/textures/perlin.h>
#include <core/point.h>
#include <core/interpolate.h>
#include <core/scalar.h>

namespace rt {
	namespace {


		/* returns a value in range -1 to 1 */
		float noise(int x, int y, int z) {
			int n = x + y * 57 + z * 997;
			n = (n << 13) ^ n;
			return (1.0f - ((n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0f);
		}

	}
	PerlinTexture::PerlinTexture(const RGBColor& white, const RGBColor& black)
	{
		pWhite = white;
		pBlack = black;
	}
	void PerlinTexture::addOctave(float amplitude, float frequency)
	{
		Octave *o=new Octave();
		
		o->oAmplitude=amplitude;
		o->ofrequency = frequency;
		pOctaves.push_back(o);
	}
	RGBColor PerlinTexture::getColor(const Point& coord)
	{
		int interpValue = 0.0;
		for each (Octave *o in pOctaves)
		{
			interpValue += o->oAmplitude * getNoise(coord * o->ofrequency);
		}
		interpValue = (interpValue + 1.0f) / 2.0f;
		return lerp(pBlack, pWhite, interpValue);
	}
	RGBColor PerlinTexture::getColorDX(const Point& coord)
	{
		NOT_IMPLEMENTED;
	}
	RGBColor PerlinTexture::getColorDY(const Point& coord)
	{
		NOT_IMPLEMENTED;
	}
	float PerlinTexture::getNoise(Point& p)
	{
		int x0 = floor(p.x);
		int y0 = floor(p.y);
		int z0 = floor(p.z);

		int x1 = x0 + 1;
		int y1 = y0 + 1;
		int z1 = z0 + 1;

		float diffX = p.x - x0;
		float diffY = p.y - y0;
		float diffZ = p.z - z0;

		float noise000 = noise(x0, y0, z0);
		float noise001 = noise(x0, y0, z1);
		float noise010 = noise(x0, y1, z0);
		float noise011 = noise(x0, y1, z1);
		float noise100 = noise(x1, y0, z0);
		float noise101 = noise(x1, y0, z1);
		float noise110 = noise(x1, y1, z0);
		float noise111 = noise(x1, y1, z1);

		 

		return lerp3d(noise000, noise100, noise010, noise110, noise001, noise101, noise011, noise111, diffX, diffY, diffZ);
	
	}


}
