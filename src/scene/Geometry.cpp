/* Copyright 2014 Lasse Dissing
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "Geometry.h"

void Geometry::SetMesh(Mesh* mesh) {
	this->mesh = mesh;
}

Mesh* Geometry::GetMesh() const {
	return mesh;
}

void Geometry::Render() {
	mesh->Render();
}
