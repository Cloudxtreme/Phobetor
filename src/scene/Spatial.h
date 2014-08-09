/* Copyright 2014 Lasse Dissing
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef __SCENE_SPATIAL_H__
#define __SCENE_SPATIAL_H__

#include <Phobetor.h>
#include <math/Math.h>

class Node;

class Spatial {
public:
						Spatial();
						explicit Spatial(const Transform& transform);

	const Quaternion&	GetWorldRotation() const;
	const Vec3&			GetWorldTranslation() const;
	float				GetWorldScale() const;
	const Transform&	GetWorldTransform() const;

	const Quaternion&	GetLocalRotation() const;
	void				SetLocalRotation(const Mat3& matrix);
	void				SetLocalRotation(const Quaternion& quaternion);

	const Vec3&			GetLocalTranslation() const;
	void				SetLocalTranslation(const Vec3& vector);
	void				SetLocalTranslation(float x, float y, float z);

	float				GetLocalScale() const;
	void				SetLocalScale(float scale);

	const Transform&	GetLocalTransform() const;
	void				SetLocalTransform(const Transform& transform);

	Spatial&			Move(float x, float y, float z);
	Spatial&			Move(const Vec3& vector);
	Spatial&			Scale(float scale);
	Spatial&			Rotate(float xAngle, float yAngle, float zAngle);


	const Node*			GetParent() const;

	virtual void		Render() = 0;
					

protected:

	Node*				SetParent(Node* parent);

	Transform 		 	localTransform;
	Transform			worldTransform;

	Node*			 	parent; 

private:

};


#endif // __SCENE_SPATIAL_H__
