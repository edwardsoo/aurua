/*
 * Vec3.h
 * Copied from 2013 CS314 P2
 */

#ifndef VEC3_H_
#define VEC3_H_
#include <math.h>
#include <stdio.h>

class Vec3 {
public:

	Vec3() {
		x = 0;
		y = 0;
		z = 0;
	}

	// constructor
	Vec3(double _x, double _y, double _z) {
		x = _x;
		y = _y;
		z = _z;
	}

	// destructor
	~Vec3() {
	}

	// assign other vector components to self
	Vec3 operator=(const Vec3 rhs) {
		if (this == &rhs)
			return *this;
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		return *this;
	}

	bool operator==(const Vec3 other) {
		return (x == other.x && y == other.y && z == other.z);
	}

	bool operator!=(const Vec3 other) {
		return !(x == other.x && y == other.y && z == other.z);
	}

	Vec3 operator+=(const Vec3 rhs) {
		if (this == &rhs)
			return *this;
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
	}

	Vec3 operator-=(const Vec3 rhs) {
		if (this == &rhs)
			return *this;
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		return *this;
	}

	Vec3 operator*=(double scalar) {
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return *this;
	}

	Vec3 operator/=(double scalar) {
		x /= scalar;
		y /= scalar;
		z /= scalar;
		return *this;
	}

	// return sum of 2 vectors
	Vec3 operator+(Vec3 other) {
		return Vec3(x + other.x, y + other.y, z + other.z);
	}

	// return difference of 2 vectors
	Vec3 operator-(Vec3 other) {
		return Vec3(x - other.x, y - other.y, z - other.z);
	}

	// return scaled vector
	Vec3 operator*(double scalar) {
		return Vec3(x * scalar, y * scalar, z * scalar);
	}

	// return scaled vector
	Vec3 operator/(double scalar) {
		return Vec3(x / scalar, y / scalar, z / scalar);
	}

	// dot product with other vector
	double dot(Vec3 other) {
		return x * other.x + y * other.y + z * other.z;
	}

	// cross product with other vector
	Vec3 cross(Vec3 other) {
		return Vec3(y * other.z - z * other.y, z * other.x - x * other.z,
				x * other.y - y * other.x);
	}

	// magnitude/length of this vector
	double length() {
		return sqrt(x * x + y * y + z * z);
	}

	// normalized vector
	void normalize() {
		double l = length();
		x /= l;
		y /= l;
		z /= l;
	}

	void positive() {
		x = fabs(x);
		y = fabs(y);
		z = fabs(z);
	}
	// access to individual elements
	double& operator[] (int i) {
		switch (i)
		{
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
		default:
			return x;
		}
	}

	void print()
	{
		printf("%f,%f,%f", x, y, z);
	}

	double x, y, z;

};

#endif /* VEC3_H_ */
