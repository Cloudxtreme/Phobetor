/* Copyright 2014 Lasse Dissing
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "Quaternion.h"

/*
 * http://www.euclideanspace.com/maths/geometry/rotations/conversions/eulerToQuaternion/index.htm 
 */
void Quaternion::SetFromAngles(float x, float y, float z) {

	float cosy = std::cos(y * 0.5);
	float siny = std::sin(y * 0.5);
	float cosz = std::cos(z * 0.5);
	float sinz = std::sin(z * 0.5);
	float cosx = std::cos(x * 0.5);
	float sinx = std::sin(x * 0.5);


	x = cosy * cosz * sinx + siny * sinz * cosx;
	y = siny * cosz * cosx + cosy * sinz * sinx;
	z = cosy * sinz * cosx - siny * cosz * sinx;
	w = cosy * cosz * cosx - siny * sinz * sinx;
}

/*
 * http://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToQuaternion/index.htm
 */
void Quaternion::SetFromRotationMatrix(const float m00, const float m01, const float m02, 
 const float m10, const float m11, const float m12, const float m20, const float m21, const float m22) {

	float trace = m00 + m11 + m22;

	if (trace > 0) {

		float s = 0.5 / std::sqrt(trace+1.0f);

		x = (m21 - m12) * s;
		y = (m02 - m20) * s;
		z = (m10 - m01) * s;
		w = 0.25f / s;

	} else {
		if ( m00 > m11 && m00 > m22) {
			
			float s = 2.0f * std::sqrt(1.0f + m00 - m11 - m22);

			x = 0.25f * s;
			y = (m01 + m10) / s;
			z = (m02 + m20) / s;
			w = (m21 - m12) / s;

		} else if (m11 > m22) {
			
			float s = 2.0f * std::sqrt(1.0f + m11 - m00 - m22);

			x = (m01 + m10) / s;
			y = 0.25f * s;
			z = (m12 + m21) / s;
			w = (m02 - m20) / s;	

		} else {
			
			float s = 2.0f * std::sqrt( 1.0f + m22 - m00 - m11);

			x = (m02 + m20) / s;
			y = (m12 + m21) / s;
			z = 0.25 * s;
			w = (m10 - m01) / s;
		}
	}
}

/*
 * http://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToEuler/index.htm
 */
float* Quaternion::ToAngles(float* angles) const {
	
	if (angles == NULL) {
		angles = new float[3];
	}
	
	float sqx = x * x;
	float sqy = y * y;
	float sqz = z * z;
	float sqw = w * w;
	float correction = sqx + sqy + sqz + sqw;

	float poleTest = x * y + z * w;

	if (poleTest > 0.4999 * correction) {
		angles[0] = 0;
		angles[1] = 2 * std::atan2(x,w);
		angles[2] = HALF_PI; 
	} else if (poleTest < -0.4999 * correction) {
		angles[0] = 0;
		angles[1] = -2 * std::atan2(x,w);
		angles[2] = -HALF_PI;
	} else {
		angles[0] = std::atan2(2 * x * w - 2 * y * z, -sqx + sqy - sqz + sqw);
		angles[1] = std::atan2(2 * y * w - 2 * x * z, sqx - sqy - sqz + sqw);
		angles[2] = std::asin(2 * poleTest / correction);
	}

	return angles;

}

/*
 * http://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToMatrix/index.htm
 */

Mat3 Quaternion::ToRotationMatrix() const {
	
	float n = 2.0f / Norm();


	float xn = x * n;
	float yn = y * n;
	float zn = z * n;

	float xx = x * xn;
	float xy = x * yn;
	float xz = x * zn;
	float xw = w * xn;
	float yy = y * yn;
	float yz = y * zn;
	float yw = w * yn;
	float zz = z * zn;
	float zw = w * zn;

	return Mat3(
			1 - (yy + zz), xy - zw, xz + yw,
			xy + zw, 1 - (xx + zz), yz - xw,
			xz - yw, yz + xw, 1 - (xx + yy) );
}
