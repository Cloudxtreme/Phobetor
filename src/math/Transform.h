/* Copyright 2014 Lasse Dissing
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef __MATH_TRANSFORM_H__
#define __MATH_TRANSFORM_H__

#include <Phobetor.h>

#include "Vector.h"
#include "Matrix.h"
#include "Quaternion.h"

class Transform {

public:
						Transform(const Vec3& translation, const Quaternion& rotation);
						Transform(const Vec3& translation, const Quaternion& rotation, float scale);
						explicit Transform(const Vec3& translation);
						explicit Transform(const Quaternion& rot);
						Transform();

	void				SetTranslation(const Vec3& translation);
	void				SetRotation(const Quaternion& rotation);
	void				SetScale(float scale);

	const Vec3&			GetTranslation() const;
	const Quaternion&	GetRotation() const;
	float				GetScale() const;

	void				SetIdentity();
	Transform			Combine(const Transform& trans) const;

	Vec3				Apply(const Vec3& vector) const;
	Vec3				ApplyInverse(const Vec3& vector) const;

	bool				IsIdentity();

	Mat4				ToMatrix() const;

	Quaternion			rotation;
	Vec3				translation;
	float				scale;

private:

	bool				isIdentityHint;
};

inline Transform::Transform(const Vec3& trans, const Quaternion& rot)
	: rotation(rot), translation(trans), scale(1.0f), isIdentityHint(false) {
	

	IsIdentity();
}

inline Transform::Transform(const Vec3& trans, const Quaternion& rot, float s)
	: rotation(rot), translation(trans), scale(s), isIdentityHint(false) {

	IsIdentity();
}

inline Transform::Transform(const Vec3& trans) 
	: rotation(Quaternion(0,0,0,1)), translation(trans), scale(1.0f), isIdentityHint(false) {

	IsIdentity();
}

inline Transform::Transform(const Quaternion& rot) 
	: rotation(rot), translation(Vec3(0,0,0)), scale(1.0f), isIdentityHint(false) {

	IsIdentity();
}

inline Transform::Transform() 
	: rotation(Quaternion(0,0,0,1)), translation(Vec3(0,0,0)), scale(1.0f), isIdentityHint(true) {

}

inline void Transform::SetTranslation(const Vec3& trans) {
	translation = trans;
	isIdentityHint = false;
}

inline void Transform::SetRotation(const Quaternion& rot) {
	rotation = rot;
	isIdentityHint = false;
}

inline void Transform::SetScale(float s) {
	scale = s;
	isIdentityHint = false;
}

inline const Vec3& Transform::GetTranslation() const {
	return translation;
}

inline const Quaternion& Transform::GetRotation() const {
	return rotation;
}

inline float Transform::GetScale() const {
	return scale;
}

inline void Transform::SetIdentity() {
	translation.x = 0;
	translation.y = 0;
	translation.z = 0;

	rotation.SetIdentity();

	scale = 1;
	isIdentityHint = true;
}

inline Transform Transform::Combine(const Transform& t) const {
	float s = scale * t.scale;
	Vec3 m = translation + t.translation;
	Quaternion q = rotation * t.rotation;
	return Transform(m,q,s);
}

inline Vec3 Transform::Apply(const Vec3& vector) const {
	if (isIdentityHint) {
		return vector;
	}
	return (rotation * (vector * scale)) + translation;
 
}

inline Vec3 Transform::ApplyInverse(const Vec3& vector) const {
	if (isIdentityHint) {
		return vector;
	}
	return (rotation * (vector - translation)) / scale;
}

inline bool Transform::IsIdentity() {

	if (isIdentityHint) 
		return true;

	if(translation.IsIdentity() && rotation.IsIdentity() && scale == 1.0f) {
		isIdentityHint = true;
		return true;
	}
	
	return false;
}

inline Mat4 Transform::ToMatrix() const {
	Mat4 res;
	Mat3 rot = rotation.ToRotationMatrix();
	res.m00 = rot.m00;
	res.m01 = rot.m01;
	res.m02 = rot.m02;
	res.m10 = rot.m10;
	res.m11 = rot.m11;
	res.m12 = rot.m12;
	res.m20 = rot.m20;
	res.m21 = rot.m21;
	res.m22 = rot.m22;

	res.m03 = translation.x;
	res.m13 = translation.y;
	res.m23 = translation.z;
	res.m33 = 1.0f;

	return res * scale;

}

#endif //__MATH_TRANSFORM_H__


