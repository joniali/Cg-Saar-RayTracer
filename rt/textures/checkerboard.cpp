#include <rt\textures\checkerboard.h>

namespace rt
{
	CheckerboardTexture::CheckerboardTexture(const RGBColor& white, const RGBColor& black)
	{
		cWhite = white;
		cBlack = black;
	}
	RGBColor CheckerboardTexture::getColor(const Point& coord)
	{
		float fu = coord.x-std::floor(coord.x);
		float fv = coord.y-std::floor(coord.y);
		float fk = coord.z-std::floor(coord.z);
		
		bool bu = fu <= 0.5;
		bool bv = fv <= 0.5;
		bool bk = fk <= 0.5;

		if (bu^bv^bk)
			return cWhite;
		else
			return cBlack;


	}
	RGBColor CheckerboardTexture::getColorDX(const Point& coord)
	{
		//color at x+1 and x-1
		return (getColor(Point(coord.x + 1, coord.y, coord.z)) -
			getColor(Point(coord.x - 1, coord.y, coord.z))) / 2;
	}
	RGBColor CheckerboardTexture::getColorDY(const Point& coord)
	{
		//color at y+1 and y-1 /2
		return (getColor(Point(coord.x, coord.y + 1, coord.z)) -
			getColor(Point(coord.x, coord.y - 1, coord.z))) / 2;
	}
}