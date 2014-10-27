#include <core\color.h>
#include <iostream>

namespace rt{

	RGBColor RGBColor::operator+(const RGBColor& c) const
	{
		return RGBColor(this->r+c.r,this->g+c.g,this->b+c.b).clamp();
	}
	RGBColor RGBColor::operator-(const RGBColor& c) const
	{
		return RGBColor(this->r-c.r,this->g-c.g,this->b-c.b).clamp();
	}
	RGBColor RGBColor::operator*(const RGBColor& c) const
	{
		return RGBColor(this->r*c.r,this->g*c.g,this->b*c.b).clamp();
	}
	bool RGBColor::operator==(const RGBColor& c) const
	{
		return (c.r==this->r && c.g== this->g && c.b==this->b)? true : false;
	}
	bool RGBColor::operator!=(const RGBColor& c) const
	{
		return (c.r!=this->r || c.g!= this->g || c.b!=this->b)? true : false;
	}
	RGBColor RGBColor::clamp() const
	{
		float r,g,b;
		r=this->r>1.0f ? 1.0f : this->r<0 ? 0.0f :this->r;
		g=this->g>1.0f ? 1.0f : this->g<0 ? 0.0f :this->g;
		b=this->b>1.0f ? 1.0f : this->b<0 ? 0.0f :this->b;
	 return RGBColor(r,g,b);
	}
	RGBColor operator*(float scalar, const RGBColor& b)
	{
		return RGBColor(scalar*b.r,scalar*b.g,scalar*b.b).clamp();
	
	}
	RGBColor operator*( const RGBColor& b,float scalar)
	{
		return RGBColor(scalar*b.r,scalar*b.g,scalar*b.b).clamp();
	
	}
	RGBColor operator/( const RGBColor& b,float scalar)
	{
		return RGBColor(b*(1/scalar));
	
	}
}