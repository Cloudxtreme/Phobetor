/* Copyright 2014 Lasse Dissing
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef __MATH_MATRIX_H__
#define __MATH_MATRIX_H__

#include <Phobetor.h>

#include "Vector.h"

/*
===============================================================================

	Mat3 -- 3x3 Matrix

===============================================================================
*/

class Mat4; //Forward declare for Mat3.ToMat4 function

class Mat3 {
public:

	union {
		float data[9];

		struct {
			float m00,m01,m02;
			float m10,m11,m12;
			float m20,m21,m22;
		};
	};

							Mat3();
							explicit Mat3(const Vec3& m0, const Vec3& m1, const Vec3& m2);

							explicit Mat3(const float m00, const float m01, const float m02,
										const float m10, const float m11, const float m12,
										const float m20, const float m21, const float m22);

	Vec3					operator[](int index) const;
	Mat3					operator-() const;

	Vec3					operator*(const Vec3& a) const;
	Mat3					operator*(const float a) const;
	Mat3					operator*(const Mat3& a) const;
	Mat3					operator+(const Mat3& a) const;
	Mat3					operator-(const Mat3& a) const;

	Mat3&					operator+=(const Mat3& a);
	Mat3&					operator-=(const Mat3& a);
	Mat3&					operator*=(const float a);
	//Mat3&					operator*=(const Mat3& a);

	//friend Mat3				operator*(const float a, const Mat3& mat);
	//friend Mat3				operator*(const Vec3& a, const Mat3& mat);

	bool					operator==(const Mat3& a) const;
	bool					operator!=(const Mat3& a) const;


	const float*			GetRaw() const;

	float					Trace() const;
	float					Determinant() const;

	void					SetZero();
	void					SetIdentity();

	Mat3					Transpose() const;
	Mat3&					TransposeSelf();

	//Quaternion				ToQuaternion();
	Mat4					ToMat4() const;

	const char*				ToString(int precision = 2) const;
};


/*
===============================================================================

	Mat4 -- 4x4 Matrix

===============================================================================
*/

class Mat4 {
public:

	union {
		float data[16];

		struct {
			float m00,m01,m02,m03;
			float m10,m11,m12,m13;
			float m20,m21,m22,m23;
			float m30,m31,m32,m33;
		};
	};
							Mat4();
							explicit Mat4(const Vec4& m0, const Vec4& m1, 
									const Vec4& m2, const Vec4& m3);

							explicit Mat4(const float m00, const float m01, const float m02, 
										const float m03, const float m10, const float m11, 
										const float m12, const float m13, const float m20,
										const float m21, const float m22, const float m23,
										const float m30, const float m31, const float m32,
										const float m33);

	Vec4					operator[](int index) const;
	Mat4					operator-() const;

	Vec4					operator*(const Vec4& a) const;
	Mat4					operator*(const float a) const;
	Mat4					operator*(const Mat4& a) const;
	Mat4					operator+(const Mat4& a) const;
	Mat4					operator-(const Mat4& a) const;
	
	Mat4&					operator+=(const Mat4& a);
	Mat4&					operator-=(const Mat4& a);
	Mat4&					operator*=(const float a);
	Mat4&					operator*=(const Mat4& a);

	friend Mat4				operator*(const float a, const Mat4& m);
	friend Vec4				operator*(const Vec4& a, const Mat4& m);

	bool					operator==(const Mat4& a) const;
	bool					operator!=(const Mat4& a) const;

	const float*			GetRaw() const;

	float					Trace() const;

	void					SetZero();
	void					SetIdentity();

	Mat4					Transpose() const;
	Mat4&					TransposeSelf();

	const char*				ToString(int precision = 2) const;

};


/*
========================
	Mat3 Implementation
========================
*/

inline Mat3::Mat3() {
	m00 = 1;
	m01 = 0;
	m02 = 0;

	m10 = 0;
	m11 = 1;
	m12 = 0;

	m20 = 0;
	m21 = 0;
	m22 = 0;
}

inline Mat3::Mat3(const Vec3& m0, const Vec3& m1, const Vec3& m2) {
	m00 = m0.x;
	m01 = m0.y;
	m02 = m0.z;

	m10 = m1.x;
	m11 = m1.y;
	m12 = m1.z;

	m20 = m2.x;
	m21 = m2.y;
	m22 = m2.z;
}

inline Mat3::Mat3(const float m00, const float m01, const float m02,
					const float m10, const float m11, const float m12,
					const float m20, const float m21, const float m22) {
	this->m00 = m00;
	this->m01 = m01;
	this->m02 = m02;
	
	this->m10 = m10;
	this->m11 = m11;
	this->m12 = m12;
	
	this->m20 = m20;
	this->m21 = m21;
	this->m22 = m22;
}

inline Vec3 Mat3::operator[](int index) const {
	assert(index < 3 && index >= 0);
	int i = index * 3;
	return Vec3(data[i],data[i+1],data[i+2]);
}

inline Mat3 Mat3::operator-() const {
	return Mat3(-m00,-m01,-m02,-m10,-m11,-m12,-m20,-m21,-m22);
}

inline Vec3 Mat3::operator*(const Vec3& a) const {
	return Vec3(m00 * a.x + m01 * a.y + m02 * a.z,
			m10 * a.x + m11 * a.y + m12 * a.z,
			m20 * a.x + m21 * a.y + m22 * a.z);
}

inline Mat3 Mat3::operator*(const float a) const {
	return Mat3(m00*a,m01*a,m02*a,
				m10*a,m11*a,m12*a,
				m20*a,m21*a,m22*a);
}

inline Mat3 Mat3::operator*(const Mat3& a) const {
	return Mat3(m00 * a.m00 + m01 * a.m10 + m02 * a.m20,
				m00 * a.m01 + m01 * a.m11 + m02 * a.m21,
				m00 * a.m02 + m01 * a.m12 + m02 * a.m22,

				m10 * a.m00 + m11 * a.m10 + m12 * a.m20,
				m10 * a.m01 + m11 * a.m11 + m12 * a.m21,
				m10 * a.m02 + m11 * a.m12 + m12 * a.m22,

				m20 * a.m00 + m21 * a.m10 + m22 * a.m20,
				m20 * a.m01 + m21 * a.m11 + m22 * a.m21,
				m20 * a.m02 + m21 * a.m12 + m22 * a.m22);
}

inline Mat3 Mat3::operator+(const Mat3& a) const {
	return Mat3(m00+a.m00, m01+a.m01, m02+a.m02,
				m10+a.m10, m11+a.m11, m12+a.m12,
				m20+a.m20, m21+a.m21, m22+a.m22);
}

inline Mat3 Mat3::operator-(const Mat3& a) const {
	return Mat3(m00-a.m00, m01-a.m01, m02-a.m02,
				m10-a.m10, m11-a.m11, m12-a.m12,
				m20-a.m20, m21-a.m21, m22-a.m22);

}

inline Mat3& Mat3::operator+=(const Mat3& a) {

//	(*this) = (*this)+a;

	return *this;
}

inline Mat3& Mat3::operator-=(const Mat3& a) {

	return *this;
}

inline Mat3& Mat3::operator*=(const float a) {
	
	return *this;
}

//TODO PURE LAZYNESS

/*inline Mat3 & Mat3::operator*=(const Mat3 &a) {
	
}

Vec3 operator*(const Vec3& v, const Mat3& m) {
	return m * v;
}

Mat3 operator*(const float a, const Mat3& m) {
	return m * a;
}*/

inline bool Mat3::operator==(const Mat3& a) const {
	return( m00 == a.m00 && m01 == a.m01 && m02 == a.m02 &&
			m10 == a.m10 && m11 == a.m11 && m12 == a.m12 &&
			m20 == a.m20 && m21 == a.m21 && m22 == a.m22);
}

inline bool Mat3::operator!=(const Mat3& a) const {
	return( m00 != a.m00 || m01 != a.m01 || m02 != a.m02 ||
			m10 != a.m10 || m11 != a.m11 || m12 != a.m12 ||
			m20 != a.m20 || m21 != a.m21 || m22 != a.m22);
}

inline const float* Mat3::GetRaw() const {
	return data;
}

inline float Mat3::Trace() const {
	return (m00+m11+m22);
}

inline float Mat3::Determinant() const {
	return (m00*m11*m22 + m01*m12*m20 + m02*m10*m21 - m02*m11*m20 - m01*m10*m22 - m00*m12*m21);
}

inline void Mat3::SetZero() {
	for (int i = 0; i < 9; i++)
		data[i] = 0;
}

inline void Mat3::SetIdentity() {
	SetZero();
	m00 = m11 = m22 = 1;
}

inline Mat3 Mat3::Transpose() const {
	return Mat3(m00,m10,m20,
				m01,m11,m21,
				m02,m12,m22);
}

inline Mat3& Mat3::TransposeSelf() {
	float tm01 = m01;
	float tm02 = m02;
	float tm12 = m12;

	m01 = m10;
	m02 = m20;
	m12 = m21;

	m10 = tm01;
	m20 = tm02;
	m21 = tm12;

	return *this;
}

inline Mat4 Mat3::ToMat4() const {
	Mat4 mat4;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			mat4.data[i*4+j] = data[i*3+j];
		}
	}
	return mat4;
}


/*
========================
	Mat4 implementation
========================
*/

inline Mat4::Mat4() {

	m00 = 1;
	m01 = 0;
	m02 = 0;
	m03 = 0;

	m10 = 0;
	m11 = 1;
	m12 = 0;
	m13 = 0;

	m20 = 0;
	m21 = 0;
	m22 = 1;
	m23 = 0;

	m30 = 0;
	m31 = 0;
	m32 = 0;
	m33 = 1;
}

inline Mat4::Mat4(const Vec4& m0, const Vec4& m1, const Vec4& m2, const Vec4& m3) {
	m00 = m0.x;
	m01 = m0.y;
	m02 = m0.z;
	m03 = m0.w;

	m10 = m1.x;
	m11 = m1.y;
	m12 = m1.z;
	m13 = m1.w;

	m20 = m2.x;
	m21 = m2.y;
	m22 = m2.z;
	m23 = m2.w;

	m30 = m3.x;
	m31 = m3.y;
	m32 = m3.z;
	m33 = m3.w;
}

inline Mat4::Mat4(const float m00, const float m01, const float m02, const float m03,
					const float m10, const float m11, const float m12, const float m13,
					const float m20, const float m21, const float m22, const float m23,
					const float m30, const float m31, const float m32, const float m33) {
	this->m00 = m00;
	this->m01 = m01;
	this->m02 = m02;
	this->m03 = m03;
	
	this->m10 = m10;
	this->m11 = m11;
	this->m12 = m12;
	this->m13 = m13;
	
	this->m20 = m20;
	this->m21 = m21;
	this->m22 = m22;
	this->m23 = m23;

	this->m30 = m30;
	this->m31 = m31;
	this->m32 = m32;
	this->m33 = m33;
}

inline Vec4 Mat4::operator[](int index) const {
	assert(index < 4 && index >= 0);
	int i = index * 4;
	return Vec4(data[i],data[i+1],data[i+2],data[i+3]);
}

inline Mat4 Mat4::operator-() const {
	return Mat4(-m00,-m01,-m02,-m03,-m10,-m11,-m12,-m13,-m20,-m21,-m22,-m23,-m30,-m31,-m32,-m33);
}

inline Vec4 Mat4::operator*(const Vec4& a) const {
	return Vec4(m00 * a.x + m01 * a.y + m02 * a.z + m03 * a.w,
			    m10 * a.x + m11 * a.y + m12 * a.z + m13 * a.w,
			    m20 * a.x + m21 * a.y + m22 * a.z + m23 * a.w,
				m30 * a.x + m31 * a.y + m32 * a.z + m33 * a.w);
}

inline Mat4 Mat4::operator*(const float a) const {
	return Mat4(m00*a,m01*a,m02*a,m03*a,
				m10*a,m11*a,m12*a,m13*a,
				m20*a,m21*a,m22*a,m23*a,
				m30*a,m31*a,m32*a,m33*a);
}

inline Mat4 Mat4::operator*(const Mat4& a) const {
	return Mat4(m00 * a.m00  +  m01 * a.m10  +  m02 * a.m20  +  m03 * a.m30,
				m00 * a.m01  +  m01 * a.m11  +  m02 * a.m21  +  m03 * a.m31,
				m00 * a.m02  +  m01 * a.m12  +  m02 * a.m22  +  m03 * a.m32,
				m00 * a.m03  +  m01 * a.m13  +  m02 * a.m23  +  m03 * a.m33,

				m10 * a.m00  +  m11 * a.m10  +  m12 * a.m20  +  m13 * a.m30,
				m10 * a.m01  +  m11 * a.m11  +  m12 * a.m21  +  m13 * a.m31,
				m10 * a.m02  +  m11 * a.m12  +  m12 * a.m22  +  m13 * a.m32,
				m10 * a.m03  +  m11 * a.m13  +  m12 * a.m23  +  m13 * a.m33,

				m20 * a.m00  +  m21 * a.m10  +  m22 * a.m20  +  m23 * a.m30,
				m20 * a.m01  +  m21 * a.m11  +  m22 * a.m21  +  m23 * a.m31,
				m20 * a.m02  +  m21 * a.m12  +  m22 * a.m22  +  m23 * a.m32,
				m20 * a.m03  +  m21 * a.m13  +  m22 * a.m23  +  m23 * a.m33,
				
				m30 * a.m00  +  m31 * a.m10  +  m32 * a.m20  +  m33 * a.m30,
				m30 * a.m01  +  m31 * a.m11  +  m32 * a.m21  +  m33 * a.m31,
				m30 * a.m02  +  m31 * a.m12  +  m32 * a.m22  +  m33 * a.m32,
				m30 * a.m03  +  m31 * a.m13  +  m32 * a.m23  +  m33 * a.m33);
}

inline Mat4 Mat4::operator+(const Mat4& a) const {
	return Mat4(m00+a.m00, m01+a.m01, m02+a.m02, m03+a.m03,
				m10+a.m10, m11+a.m11, m12+a.m12, m13+a.m13,
				m20+a.m20, m21+a.m21, m22+a.m22, m23+a.m23,
				m30+a.m30, m31+a.m31, m32+a.m32, m33+a.m33);
}

inline Mat4 Mat4::operator-(const Mat4& a) const {
	return Mat4(m00-a.m00, m01-a.m01, m02-a.m02, m03-a.m03,
				m10-a.m10, m11-a.m11, m12-a.m12, m13-a.m13,
				m20-a.m20, m21-a.m21, m22-a.m22, m23-a.m23,
				m30-a.m30, m31-a.m31, m32-a.m32, m33-a.m33);

}

inline Mat4& Mat4::operator+=(const Mat4& a) {

//	(*this) = (*this)+a;

	return *this;
}

inline Mat4& Mat4::operator-=(const Mat4& a) {

	return *this;
}

inline Mat4& Mat4::operator*=(const float a) {
	
	return *this;
}

//TODO PURE LAZYNESS

/*inline Mat3 & Mat3::operator*=(const Mat3 &a) {
	
}

Vec3 operator*(const Vec3& v, const Mat3& m) {
	return m * v;
}

Mat3 operator*(const float a, const Mat3& m) {
	return m * a;
}*/

inline bool Mat4::operator==(const Mat4& a) const {
	return( m00 == a.m00 && m01 == a.m01 && m02 == a.m02 && m03 == a.m03 &&
			m10 == a.m10 && m11 == a.m11 && m12 == a.m12 && m13 == a.m13 &&
			m20 == a.m20 && m21 == a.m21 && m22 == a.m22 && m23 == a.m23 &&
			m30 == a.m30 && m31 == a.m31 && m32 == a.m32 && m33 == a.m33);
}

inline bool Mat4::operator!=(const Mat4& a) const {
	return( m00 != a.m00 || m01 != a.m01 || m02 != a.m02 || m03 != a.m03 ||
			m10 != a.m10 || m11 != a.m11 || m12 != a.m12 || m13 != a.m13 ||
			m20 != a.m20 || m21 != a.m21 || m22 != a.m22 || m23 != a.m23 ||
			m30 != a.m30 || m31 != a.m31 || m32 != a.m32 || m33 != a.m33);
}

inline const float* Mat4::GetRaw() const {
	return data;
}


inline float Mat4::Trace() const {
	return (m00+m11+m22+m33);
}

inline void Mat4::SetZero() {
	for (int i = 0; i < 16; i++)
		data[i] = 0;
}

inline void Mat4::SetIdentity() {
	SetZero();
	m00 = m11 = m22 = m33 = 1;
}

inline Mat4 Mat4::Transpose() const {
	return Mat4(m00,m10,m20,m30,
				m01,m11,m21,m31,
				m02,m12,m22,m32,
				m03,m13,m23,m33);
}

inline Mat4& Mat4::TransposeSelf() {
	float tm01 = m01;
	float tm02 = m02;
	float tm03 = m03;
	float tm12 = m12;
	float tm13 = m13;
	float tm23 = m23;

	m01 = m10;
	m02 = m20;
	m03 = m30;
	m12 = m21;
	m13 = m31;
	m23 = m32;

	m10 = tm01;
	m20 = tm02;
	m30 = tm03;
	m21 = tm12;
	m31 = tm13;
	m32 = tm23;

	return *this;
}
#endif // __MATH_MATRIX_H__
