#include <core/vector.h>
#include <math.h> 
#include <iostream>
#include <core/point.h>


namespace rt{

float Vector::length() const 
{
	return sqrt (pow (this->x,2.0f)+pow (this->y,2.0f)+pow (this->z,2.0f));

}
float Vector::lensqr() const 
{
	return (pow (this->x,2.0f)+pow (this->y,2.0f)+pow (this->z,2.0f));

}
Vector Vector::normalize() const{
	float l= this->length();
	return Vector(this->x/l,this->y/l,this->z/l);

}
 Vector Vector::operator-() const
 {
	return Vector(this->x*-1.0f,this->y*-1.0f,this->z*-1.0f);
 }
 Vector Vector::operator-(const Vector& b) const
	{
	
		return Vector(this->x-b.x,this->y-b.y,this->z-b.z);
	}
  Vector Vector::operator+(const Vector& b) const
	{
	
		return Vector(this->x+b.x,this->y+b.y,this->z+b.z);
	}
Vector min(const Vector& a, const Vector& b)
{
	return Vector(std::min(a.x,b.x),std::min(a.y,b.y),std::min(a.z,b.z));//a.length()<b.length() ? a : b; so they want to return compwise 
}
Vector max(const Vector& a, const Vector& b)
{
	 return  Vector(std::max(a.x,b.x),std::max(a.y,b.y),std::max(a.z,b.z));
}
float dot(const Vector& a, const Vector& b)
{

	return a.x*b.x+a.y*b.y+a.z*b.z;
}
Vector cross(const Vector& a, const Vector& b)
{

	return Vector(a.y*b.z - b.y*a.z, a.z*b.x-a.x*b.z, a.x*b.y-a.y*b.x);
}

Point operator+(const Point& a, const Vector& b){
	return Point(a.x+b.x,a.y+b.y,a.z+b.z);
}
Point operator+(const Vector& b,const Point& a){
	return Point(a.x+b.x,a.y+b.y,a.z+b.z);
}
Point operator-(const Point& a, const Vector& b)
{
	return Point(a.x-b.x,a.y-b.y,a.z-b.z);
}
Vector operator*(float scalar, const Vector& b)
{
	return Vector(scalar*b.x,scalar*b.y,scalar*b.z);
}
Vector operator*(const Vector& a, float scalar){
	return Vector(scalar*a.x,scalar*a.y,scalar*a.z);
}
Vector operator/(const Vector& a, float scalar)
{
	return a*(1/scalar);
}
}