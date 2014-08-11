/* Copyright 2014 Lasse Dissing
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */


#ifndef __RENDERER_CAMERA_H__
#define __RENDERER_CAMERA_H__

#include <Phobetor.h>
#include <math/Math.h>

class Camera {

public:

						Camera();

	Mat4				GetProjectionView() const;
	void				MoveCamera(const float x, const float y, const float z);
	void				MoveCameraForward(const float speed);
	void				MoveCameraLeft(const float speed);
	void				RotateCamera(const float yaw, const float pitch, const float roll);

private:
	Mat4				projectionMatrix;
	Transform			viewTransform;

	float				yaw;
	float				pitch;
	float				roll;
};


#endif // __RENDERER_CAMERA_H__

