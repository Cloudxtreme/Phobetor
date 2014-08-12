/* Copyright 2014 Lasse Dissing
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "OBJLoader.h"
#include <stdlib.h>


void OBJLoader::TriangulateQuad(const Face& face, std::array<Face,2>& store) const {
	store[0].vertices[0] = face.vertices[0];
	store[0].vertices[1] = face.vertices[1];
	store[0].vertices[2] = face.vertices[2];
	store[1].vertices[0] = face.vertices[0];
	store[1].vertices[1] = face.vertices[2];
	store[1].vertices[2] = face.vertices[3];
}

Vec3 OBJLoader::ReadVec3(std::istringstream& reader) {
	float x,y,z;
	reader >> x;
	reader >> y;
	reader >> z;
	return Vec3(x,y,z);
}

Vec2 OBJLoader::ReadVec2(std::istringstream& reader) {
	float u,v;
	reader >> u;
	reader >> v;
	return Vec2(u,v);
}

OBJLoader::Face OBJLoader::ReadFace(std::istringstream& reader) {
	Face face;
	std::string token;
	int numberOfVertices = 0;
	while (!reader.eof()) {
		Vertex vert;
		reader >> token;
		std::stringstream stream(token);
		int split[3];
		int splitCount = 0;
		while(std::getline(stream,token,'/')) {
			if (!token.empty()) {
				split[splitCount++] = stoi(token);
			} else {
				split[splitCount++] = -1;
			}
		}
	
		vert.pos = vertices[split[0]-1];

		if (splitCount > 1 && split[1] != -1) {
			vert.tex = texCoords[split[1]-1];
		}
		if (splitCount > 2) {
			vert.normal = normals[split[2]-1];
		}
		face.vertices[numberOfVertices++] = vert;
	}

	face.count = numberOfVertices;

	return face;	
}

void OBJLoader::ReadLine(const std::string& line) {

	std::istringstream reader(line);

	std::string lineType;

	reader >> lineType;

	if (lineType == "v") {
		vertices.push_back(ReadVec3(reader));
	} else if (lineType == "vn") {
		normals.push_back(ReadVec3(reader));
	} else if (lineType == "vt") {
		texCoords.push_back(ReadVec2(reader));
	} else if (lineType == "f") {
		Face face = ReadFace(reader);
		if (face.count == 3) {
			faces.push_back(face);
		} else {
			std::array<Face,2> store;
			TriangulateQuad(face,store);
			faces.push_back(store[0]);
			faces.push_back(store[1]);
		}
	} else if (lineType == "g") {

	} else if (lineType == "usemtl") {
		
	} else if (lineType == "mtllib") {
	}
}

Mesh* OBJLoader::CreateMesh() const {
	int dataSize = 6 * faces.size() * 3;
	int indexSize = 3 * faces.size();
	float* data = new float[dataSize];
	unsigned int* indices = new unsigned int[indexSize];

	int index = 0;
	for (Face face : faces) {
		for (int i = 0; i < 3; i++) {
			data[6*index] = face.vertices[i].pos.x;
			data[6*index+1] = face.vertices[i].pos.y;
			data[6*index+2] = face.vertices[i].pos.z;
			data[6*index+3] = face.vertices[i].normal.x;
			data[6*index+4] = face.vertices[i].normal.y;
			data[6*index+5] = face.vertices[i].normal.z;

			indices[index] = index;
			index++;
		}
	}

	Mesh* mesh = new Mesh();
	mesh->SetData(data,dataSize*sizeof(float),6*sizeof(float));
	mesh->SetIndices(indices,indexSize*sizeof(unsigned int));
	mesh->UploadToGPU();

	return mesh;

}

Node* OBJLoader::Load(const std::string& filename) {

	Reset();
	
	std::ifstream file;

	file.open(filename.c_str());

	if (!file.is_open()) {
		WARN("Failed to open ",filename.c_str());
		return NULL;
	}

	root = new Node();

	for (std::string line; std::getline(file,line);) {
		ReadLine(line);
	}
	Geometry* geo = new Geometry();
	geo->SetMesh(CreateMesh());

	root->AttachChild(geo);

	return root;
}


void OBJLoader::Reset() {
	vertices.clear();
	texCoords.clear();
	normals.clear();
	faces.clear();
	
}
