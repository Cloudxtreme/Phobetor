/* Copyright 2014 Lasse Dissing
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */


#include "Camera.h"

Camera::Camera() 
	: projectionMatrix(),viewMatrix() {

		float near = 0.5;
		float far = 5;

		float aspect = 1280.0f / 720.0f;
		float fov = 40;
		float scale = std::tan(fov * PI/180) * near;

		float right = aspect * scale;
		float left = -right;
		float top = scale;
		float bottom = -top;

		projectionMatrix.m00 = 2 * near / (right - left);
		projectionMatrix.m10 = 0; 
		projectionMatrix.m20 = 0; 
		projectionMatrix.m30 = 0; 

		projectionMatrix.m01 = 0; 
		projectionMatrix.m11 = 2 * near / (top - bottom); 
		projectionMatrix.m21 = 0; 
		projectionMatrix.m31 = 0; 

		projectionMatrix.m02 = (right + left) / (right - left); 
		projectionMatrix.m12 = (top + bottom) / (top - bottom); 
		projectionMatrix.m22 = -(far + near) / (far - near); 
		projectionMatrix.m32 = -1; 

		projectionMatrix.m03 = 0; 
		projectionMatrix.m13 = 0; 
		projectionMatrix.m23 = -2 * far * near / (far - near); 
		projectionMatrix.m33 = 0; 

		for (int i = 0; i < 16; i++) {
			std::cout << projectionMatrix.data[i];
			if ((i+1) % 4 == 0) {
				std::cout << '\n';
			} else {
				std::cout << ',';
			}
		}
}

Mat4 Camera::GetProjectionView() const {
	return projectionMatrix * viewMatrix;
}

void Camera::MoveCamera(const float x, const float y, const float z) {
	viewMatrix.m03 += x;
	viewMatrix.m13 += y;
	viewMatrix.m23 += z;	
}

void Camera::RotateCameraEuler(const float yaw, const float pitch, const float roll) {

	Mat4 yawMatrix;
	Mat4 pitchMatrix;
	Mat4 rollMatrix;

	yawMatrix.m00 = std::cos(yaw);
	yawMatrix.m02 = std::sin(yaw);
	yawMatrix.m20 = -std::sin(yaw);
	yawMatrix.m22 = std::cos(yaw);

	pitchMatrix.m11 = std::cos(pitch);
	pitchMatrix.m12 = -std::sin(pitch);
	pitchMatrix.m21 = std::sin(pitch);
	pitchMatrix.m22 = std::cos(pitch);

	rollMatrix.m00 = std::cos(roll);
	rollMatrix.m01 = -std::sin(roll);
	rollMatrix.m10 = std::sin(roll);
	rollMatrix.m11 = std::cos(roll);

	viewMatrix = yawMatrix*pitchMatrix*rollMatrix;
}
