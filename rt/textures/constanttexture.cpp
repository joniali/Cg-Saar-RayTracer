#include <rt/textures/constant.h>

namespace rt 

{

	ConstantTexture::ConstantTexture()
	{}
	ConstantTexture::ConstantTexture(const RGBColor& color)
	{
		constColor = color.clamp();
		
	}
	RGBColor ConstantTexture::getColor(const Point& coord)
	{
		return constColor;
	}
	RGBColor ConstantTexture::getColorDX(const Point& coord)
	{
		//color at x+1 and x-1
		return (getColor(Point(coord.x + 1, coord.y, coord.z))-
			getColor(Point(coord.x - 1, coord.y, coord.z)))/2;
	}
	RGBColor ConstantTexture::getColorDY(const Point& coord)
	{
		//color at y+1 and y-1 /2
		return (getColor(Point(coord.x, coord.y +1, coord.z)) -
			getColor(Point(coord.x , coord.y-1, coord.z))) / 2;
	}
}