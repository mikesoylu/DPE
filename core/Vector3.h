#ifndef VECTOR3_H
#define VECTOR3_H

#include <iostream>
#include <cmath>

using std::cout;
using std::endl;

class Vector3
{
public:
	double x, y, z, w;

	Vector3(double x = 0, double y = 0, double z = 0)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Vector3& Set(double x = 0, double y = 0, double z = 0)
	{
		this->x = x;
		this->y = y;
		this->z = z;

		return *this;
	}

	/** get mag */
	double Magnitude() const
	{
		return sqrt(x*x + y*y + z*z);
	}

	/** normalize to 1 */
	Vector3& Normalize()
	{
		double mag = Magnitude();

		x /= mag;
		y /= mag;
		z /= mag;

		return *this;
	}

	/** negate */
	Vector3& Negate()
	{
		x = -x;
		y = -y;
		z = -z;

		return *this;
	}

	/** scale by */
	Vector3 operator*(double scale) const
	{
		Vector3 ret = *this;

		ret.x *= scale;
		ret.y *= scale;
		ret.z *= scale;

		return ret;
	}

	/** scale by */
	Vector3& operator*=(double scale)
	{
		x *= scale;
		y *= scale;
		z *= scale;

		return *this;
	}

	/** dot product */
	double operator*(const Vector3& vec) const
	{
		return x*vec.x + y*vec.y + z*vec.z;
	}

	/** cross product */
	Vector3 operator%(const Vector3& vec) const
	{
		Vector3 ret;

		ret.x = (y*vec.z)-(vec.y*z);
		ret.y = -(x*vec.z)+(vec.x*z);
		ret.z = (x*vec.y)-(y*vec.x);

		return ret;
	}

	/** cross product */
	Vector3& operator%=(const Vector3& vec)
	{
		Vector3 ret;

		ret.x = (y*vec.z)-(vec.y*z);
		ret.y = -(x*vec.z)+(vec.x*z);
		ret.z = (x*vec.y)-(y*vec.x);

		this->x = ret.x;
		this->y = ret.y;
		this->z = ret.z;

		return *this;
	}

	/** sub */
	Vector3 operator-(const Vector3& vec) const
	{
		Vector3 ret = *this;

		ret.x -= vec.x;
		ret.y -= vec.y;
		ret.z -= vec.z;

		return ret;
	}

	/** add */
	Vector3 operator+(const Vector3& vec) const
	{
		Vector3 ret = *this;

		ret.x += vec.x;
		ret.y += vec.y;
		ret.z += vec.z;

		return ret;
	}

	/** add */
	Vector3& operator+=(const Vector3& vec)
	{
		x += vec.x;
		y += vec.y;
		z += vec.z;

		return *this;
	}

	/** print */
	void Print() const
	{
		cout << '(' << x << ',' << y << ',' << z << ')' << endl;
	}
};

#endif
