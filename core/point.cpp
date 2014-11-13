#include <core\point.h>
#include <iostream>
#include <core\vector.h>
#include <algorithm>

namespace rt{ 

	Point::Point(const Vector& v) {
		x = v.x;
		y = v.y;
		z = v.z;
	}

	Point Point::operator+(const Point& b) const
	{
	
		return Point(this->x+b.x,this->y+b.y,this->z+b.z);
	}

	Vector Point::operator-(const Point& b) const
	{
	
		return Vector(this->x-b.x,this->y-b.y,this->z-b.z);
	}
	bool Point::operator==(const Point& b) const
	{
	
		return (b.x==this->x && b.y== this->y && b.z==this->z)? true : false;
	}
	bool Point::operator!=(const Point& b) const
	{
	
		return (b.x!=this->x || b.y!= this->y || b.z!=this->z)? true : false;
	}
	Point operator*(float scalar, const Point& b){
		
		return Point(scalar*b.x,scalar*b.y,scalar*b.z);
	
	}
	Point operator*(const Point& b,float scalar){
		
		return Point(scalar*b.x,scalar*b.y,scalar*b.z);
	
	}
	Point min(const Point& a, const Point& b)
	{
		return Point(std::min(a.x,b.x),std::min(a.y,b.y),std::min(a.z,b.z));
	}
	Point max(const Point& a, const Point& b){
		return  Point(std::max(a.x,b.x),std::max(a.y,b.y),std::max(a.z,b.z));
	}


}