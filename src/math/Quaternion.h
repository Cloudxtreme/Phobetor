/* Copyright 2014 Lasse Dissing
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef __MATH_QUATERNION_H__
#define __MATH_QUATERNION_H__

#include <Phobetor.h>

#include "Float.h"
#include "Vector.h"
#include "Matrix.h"

class Quaternion {

public:

	union {
		float data[4];

		struct {
			float x, y, z, w;
		};
	};

						Quaternion();
						Quaternion(const float x, const float y, const float z, const float w);

	void				SetFromAngles(float x, float y, float z);
	void				SetFromRotationMatrix(const Mat3& mat);
	void				SetFromRotationMatrix(const float m00, const float m01, const float m02,
												const float m10, const float m11, const float m12,
												const float m20, const float m21, const float m22);

	float*				ToAngles(float* angles) const;
	Mat3				ToRotationMatrix() const;

	Quaternion			operator-() const;
	Quaternion			operator+(const Quaternion& quaternion) const;
	Quaternion			operator-(const Quaternion& quaternion) const;
	Quaternion			operator*(const Quaternion& quaternion) const;
	Vec3				operator*(const Vec3& vec) const;

	bool				operator==(const Quaternion& quaternion) const;
	bool				operator!=(const Quaternion& quaternion) const;

	bool				IsIdentity() const;

	float				Dot(const Quaternion& quaternion) const;
	float				Norm() const;
	Quaternion			Inverse() const;

	void				SetIdentity();
	void				NormaliseSelf();
	void				InverseSelf();
	



};



inline Quaternion::Quaternion() {
	x = y = z = 0;
	w = 1;
}

inline Quaternion::Quaternion(const float x, const float y, const float z, const float w) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}


inline void Quaternion::SetFromRotationMatrix(const  Mat3& mat) {
	SetFromRotationMatrix(mat.m00, mat.m01, mat.m02, mat.m10, 
									mat.m11, mat.m12, mat.m20, mat.m21, mat.m22);
}

inline Quaternion Quaternion::operator-() const {
	return Quaternion(-x, -y, -z, -w);
}

inline Quaternion Quaternion::operator+(const Quaternion& q) const {
	return Quaternion(x + q.x, y + q.y, z + q.z, w + q.w);
}

inline Quaternion Quaternion::operator-(const Quaternion& q) const {
	return Quaternion(x - q.x, y - q.y, z - q.z, w - q.w);
}

inline Quaternion Quaternion::operator*(const Quaternion& q) const {
	return Quaternion(
			x * q.w + y * q.z - z * q.y + w * q.x,
			-x * q.z + y * q.w + z * q.x + w * q.y,
			x * q.y - y * q.x + z *q.w + w * q.z,
			-z * q.x - y * q.y - z * q.z + w * q.w);
}

inline Vec3 Quaternion::operator*(const Vec3& v) const {

	return (ToRotationMatrix() * v);
}


inline bool	Quaternion::operator==(const Quaternion& q) const {
	
	return( x == q.x && y == q.y && z == q.z && w == q.w);
}

inline bool Quaternion::operator!=(const Quaternion& q) const {

	return( x != q.x || y != q.y || z != q.z || w != q.w);
}

inline bool Quaternion::IsIdentity() const {
	return (x == 0 && y == 0 && z == 0 && w == 1);
}

inline float Quaternion::Dot(const Quaternion& q) const {
	return x * q.x + y *q.y + z * q.z + w * q.w;
}

inline float Quaternion::Norm() const {
	return x * x + y * y + z * z + w * w;
}

inline Quaternion Quaternion::Inverse() const {
	float norm = Norm();
	if (norm > 0.0) {
		float inv = 1.0f / norm;
		return Quaternion (-x * inv, -y * inv, -z * inv, w * inv);
	}

	std::printf("Quaternion::Inverse but norm > 0.0!");
	return Quaternion();
}

inline void Quaternion::SetIdentity() {
	x = y = z = 0;
	w = 1;
}

inline void Quaternion::NormaliseSelf() {
	float n = 1/std::sqrt(Norm());
	x *= n;
	y *= n;
	z *= n;
	w *= n;
}

inline void Quaternion::InverseSelf() {
	float norm = Norm();
	if (norm > 0.0) {
		float inv = 1.0f / norm;
		x *= -inv;
		y *= -inv;
		z *= -inv;
		w *= inv;
	}
}



#endif // __MATH_QUATERNION_H__
