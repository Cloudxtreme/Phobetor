/* Copyright 2014 Lasse Dissing
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "Spatial.h"

Spatial::Spatial()
	: localTransform() {

}

Spatial::Spatial(const Transform& transform)
	: localTransform(transform) {

}

const Quaternion& Spatial::GetWorldRotation() const {
	return worldTransform.GetRotation();
}

const Vec3& Spatial::GetWorldTranslation() const {
	return worldTransform.GetTranslation();
}

const Transform& Spatial::GetWorldTransform() const {
	return worldTransform;
}

float Spatial::GetWorldScale() const {
	return worldTransform.GetScale();
}

const Quaternion& Spatial::GetLocalRotation() const {
	return localTransform.GetRotation();
}

void Spatial::SetLocalRotation(const Mat3& matrix) {
	Quaternion rot;
	rot.SetFromRotationMatrix(matrix);
	localTransform.SetRotation(rot);
}

void Spatial::SetLocalRotation(const Quaternion& rot) {
	localTransform.SetRotation(rot);
}

const Vec3& Spatial::GetLocalTranslation() const {
	return localTransform.GetTranslation();
}

void Spatial::SetLocalTranslation(const Vec3& vector) {
	localTransform.SetTranslation(vector);
}

void Spatial::SetLocalTranslation(float x, float y, float z) {
	Vec3 vector(x,y,z);
	localTransform.SetTranslation(vector);
}

float Spatial::GetLocalScale() const {
	return localTransform.GetScale();
}

void Spatial::SetLocalScale(float scale) {
	localTransform.SetScale(scale);
}

const Transform& Spatial::GetLocalTransform() const {
	return localTransform;
}

void Spatial::SetLocalTransform(const Transform& transform) {
	localTransform = transform;
}

Spatial& Spatial::Move(float x, float y, float z) {
	localTransform.translation.Add(x,y,z);	
	return *this;
}

Spatial& Spatial::Move(const Vec3& vector) {
	localTransform.translation += vector;
	return *this;
}

Spatial& Spatial::Scale(float scale) {
	localTransform.scale *= scale;
	return *this;
}

Spatial& Spatial::Rotate(float xAngle, float yAngle, float zAngle) {
	Quaternion rot;
	rot.SetFromAngles(xAngle,yAngle,zAngle);
	localTransform.rotation = localTransform.rotation * rot;

	return *this;
}

const Spatial* Spatial::GetParent() const {
	return parent;
}

void Spatial::UpdateState() {
	UpdateWorldData();
}

Spatial* Spatial::SetParent(Spatial* newParent) {
	Spatial* former = parent;
	parent = newParent;
	return former;
}

void Spatial::UpdateWorldData() {
	if (parent) {
		worldTransform = parent->worldTransform.Combine(localTransform);
	} else {
		worldTransform = localTransform;
	}
}
