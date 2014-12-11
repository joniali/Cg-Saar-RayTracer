#include <core\float4.h>

namespace rt
{
	Float4::Float4(float x, float y, float z, float w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	
	}
	Float4::Float4(const Point& p)
	{
		x = p.x;
		y = p.y;
		z = p.z;
		w = 1;

	}
	Float4::Float4(const Vector& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		w = 0;

	}
	float& Float4::operator[](int idx)
	{
		switch (idx)
		{
		case 0:
			return x;
			break;
		case 1:
			return y;
			break;
		case 2:
			return z;
			break;
		case 3:
			return w;
			break;
		default:
			break;
		}
	}
	float Float4::operator[](int idx) const
	{
		switch (idx)
		{
		case 0:
			return x;
			break;
		case 1:
			return y;
			break;
		case 2:
			return z;
			break;
		case 3:
			return w;
			break;
		default:
			break;
		}
	}
	Float4 Float4::operator + (const Float4& b) const
	{
		return Float4(this->x + b.x, this->y + b.y, this->z + b.z,this->w+b.w);
	}
	Float4 Float4::operator-(const Float4& b) const
	{
		return Float4(this->x - b.x, this->y - b.y, this->z - b.z, this->w - b.w);
	}
	Float4 Float4::operator*(const Float4& b) const
	{
		return Float4(this->x * b.x, this->y * b.y, this->z * b.z, this->w * b.w);
	}
	Float4  Float4::operator/(const Float4& b) const
	{
		return Float4(this->x / b.x, this->y / b.y, this->z / b.z, this->w / b.w);
	}
	Float4 Float4::operator - () const
	{
		return Float4(this->x*-1.0f, this->y*-1.0f, this->z*-1.0f,this->w*-1.0f);
	}

	bool Float4::operator==(const Float4& b) const
	{
		return (b.x == this->x && b.y == this->y && b.z == this->z && this->w == b.w) ? true : false;
	
	}
	bool Float4::operator!=(const Float4& b) const
	{
		return !(* this == b);
	}
	Float4 operator*(float scalar, const Float4& b)
	{
		return Float4(scalar*b.x, scalar*b.y, scalar*b.z,scalar*b.w);
	}
	Float4 operator*(const Float4& a, float scalar)
	{
		return scalar*a;
	}

	Float4 operator/(const Float4& a, float scalar)
	{	
		return a *(1 / scalar);
	}

	float dot(const Float4& a, const Float4& b)
	{
	
		return a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w;
	}

	Float4 min(const Float4& a, const Float4& b)
	{
		return Float4(std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z),std::min(a.w,b.w));
	}
	Float4 max(const Float4& a, const Float4& b)
	{
		return  Float4(std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z),std::max(a.w,b.w));
	}
}