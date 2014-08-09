/* Copyright 2014 Lasse Dissing
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef __SCENE_GEOMETRY_H__
#define __SCENE_GEOMETRY_H__

#include <Phobetor.h>
#include "Spatial.h"
#include <renderer/Mesh.h>

class Geometry: public Spatial {

public:


	void				SetMesh(Mesh* mesh);
	Mesh*				GetMesh() const;

	virtual void		Render();

protected:

	Mesh*				mesh;

};

#endif // __SCENE_GEOMETRY_H__
