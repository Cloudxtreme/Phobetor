/* Copyright 2014 Lasse Dissing
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef __MATH_VECTOR_H__
#define __MATH_VECTOR_H__

#include <Phobetor.h>

/*
===============================================================================

	Vector - 2,3 and 4 dimensional float

	Threadsafe!

===============================================================================
*/


//TODO MAKE CODE MORE C++ LIKE. Clearly shows to be one of the earlier files


/*
===============================================================================

	Vec2 -- 2D Vector

===============================================================================
*/

class Vec2 {

public:
	union {
		float data[2];

		struct {
			float x,y;
		};

		struct {
			float u,v;
		};
	};
						Vec2();
						explicit Vec2(const float xy);
						Vec2(const float x, const float y);

	void				Set(const float xy);
	void				Set(const float x, const float y);
	void				Zero();

	float				operator[](int index) const;
	Vec2				operator-() const;
	float				operator*(const Vec2 &a) const;
	Vec2				operator*(const float a) const;
	Vec2				operator/(const float a) const;
	Vec2				operator+(const Vec2 &a) const;
	Vec2				operator-(const Vec2 &a) const;
	Vec2 &				operator+=(const Vec2 &a);
	Vec2 &				operator-=(const Vec2 &a);
	Vec2 &				operator/=(const float a);
	Vec2 &				operator*=(const float a);

	bool				operator==(const Vec2 &a) const;
	bool				operator!=(const Vec2 &a) const;

	void				Add(float x, float y);
	void				Sub(float x, float y);
	void				Scale(float a);

	float				Length() const;
	float				LengthSquare() const;
	float				Normalise();

	bool				IsIdentity() const;
	
	const char *		ToString(int precision = 2) const;

};

		

/*
===============================================================================

	Vec3 -- 3D Vector

===============================================================================
*/


class Vec3 {

public:

	union {

		float data[3];

		struct {
			float x,y,z;
		};

		struct {
			float r,g,b;
		};
	};

						Vec3();
						explicit Vec3(const float xyz);
						Vec3(const float x, const float y, const float z);
	
	void				Set(const float xyz);
	void				Set(const float x, const float y, const float z);


	float				operator[](const int index) const;
	Vec3				operator-() const;
	float				operator*(const Vec3 &a) const;
	Vec3				operator*(const float a) const;
	Vec3				operator/(const float a) const;
	Vec3				operator+(const Vec3 &a) const;
	Vec3				operator-(const Vec3 &a) const;
	Vec3 &				operator+=(const Vec3 &a);
	Vec3 &				operator-=(const Vec3 &a);
	Vec3 &				operator/=(const float a);
	Vec3 &				operator*=(const float a);

	bool 				operator==(const Vec3 &a) const;
	bool				operator!=(const Vec3 &a) const;

	void				Add(float x, float y, float z);
	void				Sub(float x, float y, float z);
	void				Scale(float a);

	Vec3				Cross(const Vec3 &a) const;
	float				Length() const;
	float				LengthSquared() const;
	float				Normalise();

	bool				IsIdentity() const;

	const char *		ToString(int precision = 2) const;

};



/*
===============================================================================

	Vec4 -- 4D Vector

===============================================================================
*/


class Vec4 {

public:

	union {

		float data[4];

		struct {
			float x,y,z,w;
		};

		struct {
			float r,g,b,a;
		};
	};

						Vec4();
						explicit Vec4(const float xyzw);
						Vec4(const float x, const float y, const float z, const float w);

	void				Set(const float xyzw);
	void				Set(const float x, const float y, const float z, const float w);

	float				operator[](const int index) const;
	Vec4				operator-() const;
	float				operator*(const Vec4 &a) const;
	Vec4				operator*(const float a) const;
	Vec4				operator/(const float a) const;
	Vec4				operator+(const Vec4 &a) const;
	Vec4				operator-(const Vec4 &a) const;
	Vec4 &				operator+=(const Vec4 &a);
	Vec4 &				operator-=(const Vec4 &a);
	Vec4 &				operator/=(const float a);
	Vec4 &				operator*=(const float a);

	bool				operator==(const Vec4 &a) const;
	bool				operator!=(const Vec4 &a) const;

	void				Add(float x, float y, float z, float w);
	void				Sub(float x, float y, float z, float w);
	void				Scale(float a);

	float				Length() const;
	float				LengthSquared() const;
	float				Normalise();

	bool				IsIdentity() const;

	const char *		ToString(int precision = 2) const;

};


/*
========================
	Vec2 Implementation
========================
*/

inline Vec2::Vec2()
	: x(0), y(0) {}

inline Vec2::Vec2(const float xy)
	: x(xy), y(xy) {}

inline Vec2::Vec2(const float x, const float y) {
	this->x = x;
	this->y = y;
}

inline void Vec2::Set(const float xy) {
	x = xy;
	y = xy;
}

inline void Vec2::Set(const float x, const float y) {
	this->x = x;
	this->y = y;
}

inline void Vec2::Zero() {
	x = y = 0;
}

inline float Vec2::operator[](const int index) const {
	assert(index < 2 && index >= 0);
	return *(data+index);
}

inline Vec2 Vec2::operator-() const {
	return Vec2(-x,-y);
}

inline float Vec2::operator*(const Vec2 &a) const {
	return x * a.x + y * a.y;
}

inline Vec2 Vec2::operator*(const float a) const {
	return Vec2(x * a, y * a);
}

inline Vec2 Vec2::operator/(const float a) const {
	return Vec2(x / a, y / a);
}

inline Vec2 Vec2::operator+(const Vec2 &a) const {
	return Vec2(x + a.x, y + a.y);
}

inline Vec2 Vec2::operator-(const Vec2 &a) const {
	return Vec2(x - a.x, y - a.y);
}

inline Vec2 & Vec2::operator+=(const Vec2 &a) {
	x += a.x;
	y += a.y;

	return *this;
}

inline Vec2 & Vec2::operator-=(const Vec2 &a) {
	x -= a.x;
	y -= a.y;

	return *this;
}

inline Vec2 & Vec2::operator/=(const float a) {
	x /= a;
	y /= a;
	
	return *this;
}

inline Vec2 & Vec2::operator*=(const float a) {
	x *= a;
	y *= a;

	return *this;
}

inline bool Vec2::operator==(const Vec2 &a) const {
	return (x == a.x && y == a.y);
}

inline bool Vec2::operator!=(const Vec2 &a) const {
	return (x != a.x || y != a.y);
}

inline void Vec2::Add(float x, float y) {
	this->x += x;
	this->y += y;
}

inline void Vec2::Sub(float x, float y) {
	this->x -= x;
	this->y -= y;
}

inline void Vec2::Scale(float a) {
	this->x *= a;
	this->y *= a;
}

inline float Vec2::Length() const {
	return std::sqrt(x * x + y * y);
}

inline float Vec2::LengthSquare() const {
	return x * x + y * y;
}

inline float Vec2::Normalise() {

	float length;
	float inverseLength;

	length = this->Length();
	inverseLength = 1/length;
	x *= inverseLength;
	y *= inverseLength;

	return this->Length();
}

inline bool Vec2::IsIdentity() const {
	return (x == 0 && y == 0); 
}

#define VEC2_FORMAT_TEMPLATE "%%.%df,%%.%df"
#define VEC2_TEMPLATE_LENGTH 14

inline const char * Vec2::ToString(int precision) const {

	int totalChars = 4; //Two char for point, One char for commas and one for "\0"
	for (int i = 0; i < 2; ++i)
		totalChars += (int)(std::log10(*(data+i))+1.0) + precision;
	
	char *buffer = new char[totalChars];
	char format[VEC2_TEMPLATE_LENGTH];


	std::sprintf(format, VEC2_FORMAT_TEMPLATE, precision, precision);
	std::snprintf(buffer, totalChars, format, x, y);

	return buffer;
}



/*
========================
	Vec3 Implementation
========================
*/

inline Vec3::Vec3() 
	: x(0), y(0), z(0) {}

inline Vec3::Vec3(const float xyz) {
	x = xyz;
	y = xyz;
	z = xyz;
}

inline Vec3::Vec3(const float x, const float y, const float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

inline void Vec3::Set(const float xyz) {
	x = xyz;
	y = xyz;
	z = xyz;
}

inline void Vec3::Set(const float x, const float y, const float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}


inline float Vec3::operator[](const int index) const {
	return *(data+index);
}

inline Vec3 Vec3::operator-() const {
	return Vec3(-x, -y, -z);
}

inline float Vec3::operator*(const Vec3 &a) const {
	return x * a.x + y * a.y + z * a.z;
}

inline Vec3 Vec3::operator*(const float a) const {
	return Vec3(x * a, y * a, z * a);
}

inline Vec3 Vec3::operator/(const float a) const {
	return Vec3(x / a, y / a, z / a);
}

inline Vec3 Vec3::operator+(const Vec3 &a) const {
	return Vec3(x + a.x, y + a.y, z + a.z);
}

inline Vec3 Vec3::operator-(const Vec3 &a) const {
   return Vec3(x - a.x, y - a.y, z - a.z);
}

inline Vec3 & Vec3::operator+=(const Vec3 &a) {
	x += a.x;
	y += a.y;
	z += a.z;

	return *this;
}

inline Vec3 & Vec3::operator-=(const Vec3 &a) {
	x -= a.x;
	y -= a.y;
	z -= a.z;

	return *this;
}

inline Vec3 & Vec3::operator/=(const float a) {
	x /= a;
	y /= a;
	z /= a;

	return *this;
}

inline Vec3 & Vec3::operator*=(const float a) {
	x *= a;
	y *= a;
	z *= a;

	return *this;
}

inline bool Vec3::operator==(const Vec3 &a) const {
	return (x == a.x && y == a.y && z == a.z);
}

inline bool Vec3::operator!=(const Vec3 &a) const {
	return (x != a.x || y != a.y || z != a.z);
}

inline void Vec3::Add(float x, float y, float z) {
	this->x += x;
	this->y += y;
	this->z += z;
}

inline void Vec3::Sub(float x, float y, float z) {
	this->x -= x;
	this->y -= y;
	this->z -= z;
}

inline void Vec3::Scale(float a) {
	this->x *= a;
	this->y *= a;
	this->z *= a;
}

inline Vec3 Vec3::Cross(const Vec3 &a) const {
	return Vec3(y*a.z - z*a.y, z*a.x - x*a.z, x*a.y - y*a.x);
}

inline float Vec3::Length() const {
	return std::sqrt(x * x + y * y + z * z);
}

inline float Vec3::LengthSquared() const {
	return x * x + y * y + z * z;
}

inline float Vec3::Normalise() {
	float length;
	float inverseLength;

	length = this->Length();
	inverseLength = 1/length;
	x *= inverseLength;
	y *= inverseLength;
	z *= inverseLength;

	return this->Length();
}

inline bool Vec3::IsIdentity() const {
	return (x == 0 && y == 0 && z == 0); 
}

#define VEC3_FORMAT_TEMPLATE "%%.%df,%%.%df,%%.%df"
#define VEC3_TEMPLATE_LENGTH 21

inline const char * Vec3::ToString(int precision) const {

	int totalChars = 6; //Three chars for point, Two chars for commas and one for "\0"
	for (int i = 0; i < 3; ++i)
		totalChars += (int)(std::log10(*(data+i))+1.0) + precision;
	
	char *buffer = new char[totalChars];
	char format[VEC3_TEMPLATE_LENGTH];

	std::sprintf(format, VEC3_FORMAT_TEMPLATE, precision, precision, precision);
	std::snprintf(buffer, totalChars, format, x, y, z);

	return buffer;
}



/*
========================
	Vec4 Implementation
========================
*/


inline Vec4::Vec4() 
	: x(0), y(0), z(0), w(0) {}

inline Vec4::Vec4(const float xyzw) {
	x = xyzw;
	y = xyzw;
	z = xyzw;
	w = xyzw;
}

inline Vec4::Vec4(const float x, const float y, const float z, const float w) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

inline void Vec4::Set(const float xyzw) {
	x = xyzw;
	y = xyzw;
	z = xyzw;
	w = xyzw;
}

inline void Vec4::Set(const float x, const float y, const float z, const float w) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

inline float Vec4::operator[](const int index) const {
   return *(data + index);
}

inline Vec4 Vec4::operator-() const {
	return Vec4(-x, -y, -z, -w);
}

inline float Vec4::operator*(const Vec4 &a) const {
	return x * x + y * y + z * z + w * w;
}

inline Vec4 Vec4::operator*(const float a) const {
	return Vec4(x * a, y * a, z * a, w * a);
}

inline Vec4 Vec4::operator/(const float a) const {
	return Vec4(x / a, y / a, z / a, w / a);
}

inline Vec4 Vec4::operator+(const Vec4 &a) const {
	return Vec4(x + a.x, y + a.y, z + a.z, w + a.w);
}

inline Vec4 Vec4::operator-(const Vec4 &a) const {
	return Vec4(x - a.x, y - a.y, z - a.z, w - a.w);
}

inline Vec4 & Vec4::operator+=(const Vec4 &a) {
	x += a.x;
	y += a.y;
	z += a.z;
	w += a.w;

	return *this;
}

inline Vec4 & Vec4::operator-=(const Vec4 &a) {
	x -= a.x;
	y -= a.y;
	z -= a.z;
	w -= a.w;

	return *this;
}

inline Vec4 & Vec4::operator/=(const float a) {
	x /= a;
	y /= a;
	z /= a;
	w /= a;

	return *this;
}

inline Vec4 & Vec4::operator*=(const float a){
	x *= a;
	y *= a;
	z *= a;
	w *= a;

	return *this;
}

inline bool Vec4::operator==(const Vec4 &a) const {
	return (x == a.x && y == a.x && z == a.z && w == a.w);
}

inline bool Vec4::operator!=(const Vec4 &a) const {
	return (x != a.x || y != a.y || z != a.z || w != a.w);
}

inline void Vec4::Add(float x, float y, float z, float w) {
	this->x += x;
	this->y += y;
	this->z += z;
	this->w += w;
}

inline void Vec4::Sub(float x, float y, float z, float w) {
	this->x -= x;
	this->y -= y;
	this->z -= z;
	this->w -= w;
}

inline void Vec4::Scale(float a) {
	this->x *= a;
	this->y *= a;
	this->z *= a;
	this->w *= a;
}

inline float Vec4::Length() const {
	return std::sqrt(x * x + y * y + z * z + w * w);
}

inline float Vec4::LengthSquared() const {
	return x * x + y * y + z * z + w * w;
}

inline float Vec4::Normalise() {
	float length;
	float inverseLength;

	length = this->Length();
	inverseLength = 1/length;

	x *= inverseLength;
	y *= inverseLength;

	return this->Length();
}

inline bool Vec4::IsIdentity() const {
	return (x == 0 && y == 0 && z == 0 && w == 0); 
}

#define VEC4_FORMAT_TEMPLATE "%%.%df,%%.%df,%%.%df,%%.%df"
#define VEC4_TEMPLATE_LENGTH 28

inline const char * Vec4::ToString(int precision) const {

	int totalChars = 8; //Four chars for point, Three chars for commas and one for "\0"
	for (int i = 0; i < 4; ++i)
		totalChars += (int)(std::log10(*(data+i))+1.0)+precision;
	
	char *buffer = new char[totalChars];
	char format[VEC4_TEMPLATE_LENGTH];

	std::sprintf(format, VEC4_FORMAT_TEMPLATE, precision, precision, precision, precision);
	std::snprintf(buffer, totalChars, format, x, y, z, w);

	return buffer;
}
						
#endif // __MATH_VECTOR_H__
