/* Copyright 2014 Lasse Dissing
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */


#include "Camera.h"

Camera::Camera() 
	: projectionMatrix(),viewTransform(),yaw(0),pitch(0),roll(0){

		float near = 0.5;
		float far = 5;

		float aspect = 1280.0f / 720.0f;
		float fov = 30;
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

}

Mat4 Camera::GetProjectionView() const {

	return projectionMatrix*viewTransform.ToMatrix();
}

void Camera::MoveCamera(const float x, const float y, const float z) {
	viewTransform.translation += Vec3(x,y,z);
}

void Camera::MoveCameraForward(const float speed) {
	viewTransform.translation += Vec3(-std::sin(pitch),0,std::cos(pitch)) * speed;
}

void Camera::MoveCameraLeft(const float speed) {
	viewTransform.translation += Vec3(std::cos(pitch),0,std::sin(pitch)) * speed;
}

void Camera::RotateCamera(const float y, const float p, const float r) {

	yaw += y;
	pitch += p;
	roll += r;

	Quaternion qroll(std::sin(roll/2.0f),0,0,std::cos(roll/2.0f));
	Quaternion qpitch(0,std::sin(pitch/2.0f),0,std::cos(pitch/2.0f));
	Quaternion qyaw(0,0,std::sin(yaw/2.0f),std::cos(yaw/2.0f));

	viewTransform.rotation = qroll * qpitch * qyaw;

}
