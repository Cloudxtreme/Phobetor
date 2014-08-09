/* Copyright 2014 Lasse Dissing
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef __ASSET_OBJLOADER_H__
#define __ASSET_OBJLOADER_H__

#include <Phobetor.h>

#include <math/Math.h>
#include <scene/Node.h>
#include <scene/Geometry.h>
#include <renderer/Mesh.h>


class OBJLoader {

public:
	
	Node*				Load(const std::string& file);

protected:

	typedef struct Vertex {

		Vec3 pos;
		Vec3 normal;
		Vec2 tex;

	} Vertex;

	typedef struct Face {

		std::array<Vertex,4> vertices;
		int count;

	} Face;



	Mesh*				CreateMesh() const;

	void				ReadLine(const std::string& line);

	Face				ReadFace(std::istringstream& reader);
	Vec2				ReadVec2(std::istringstream& reader);
	Vec3				ReadVec3(std::istringstream& reader);

	void				TriangulateQuad(const Face& face, std::array<Face,2>& store) const;

	void				Reset();


	std::vector<Vec3> 	vertices;
	std::vector<Vec2> 	texCoords;
	std::vector<Vec3> 	normals;

	std::vector<Face> 	faces;

	Node*				root;



};

#endif // __ASSET_OBJLOADER_H__
