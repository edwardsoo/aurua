/*
 * Vec3.h
 * Copied from 2013 CS314 P2
 */

#ifndef VEC3_H_
#define VEC3_H_
#include <math.h>

class Vec3 {
public:
	
	Vec3() {
		x = 0;
		y = 0;
		z = 0;
	};

	// constructor
	Vec3(double _x, double _y, double _z) {
		x = _x;
		y = _y;
		z = _z;
	};
	// destructor
	~Vec3() {};

	// return sum of 2 vectors
	Vec3& operator=(const Vec3 rhs) {
		if (this == &rhs)
			return *this;
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		return *this;
	}; 

	// return sum of 2 vectors
	Vec3 operator+(Vec3 other) {
		return Vec3(x+other.x, y+other.y, z+other.z);
	}; 

	// return difference of 2 vectors
	Vec3 operator-(Vec3 other) {
		return Vec3(x-other.x, y-other.y, z-other.z);
	}; 

	// dot product with other vector
	double dot(Vec3 other) {
		return x*other.x + y*other.y + z*other.z;
	};

	// cross product with other vector
	Vec3 cross(Vec3 other) {
		return Vec3(y*other.z - z*other.y,
					z*other.x - x*other.z,
					x*other.y - y*other.x );
	};

	// magnitude/length of this vector
	double length() {
		return sqrt(x*x + y*y + z*z);
	};

	// normalized vector
	void normalize() {
		double l=length();
		x /= l;
		y /= l;
		z /= l;
	};

	double x, y, z;

};


#endif /* VEC3_H_ */
