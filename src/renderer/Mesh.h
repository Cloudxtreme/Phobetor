/* Copyright 2014 Lasse Dissing
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef __SCENE_MESH_H__
#define __SCENE_MESH_H__


#include <Phobetor.h> 

class Mesh {

public:

	enum Type {
		POINTS,
		LINES,
		TRIANGLES,
		FAN
	};

	
						Mesh();

	void				UploadToGPU();
	void				DeleteFromGPU();
	void				Render();

	void				SetData(float* data, unsigned int size, unsigned int vertexSize);
	void				SetIndices(unsigned int* indices, unsigned int size);



private:

	Type				type;

	float*	 			data; //In-memory caching. Dont know if this will be needed
	size_t				dataSize;
	unsigned int*		indices;

	GLuint				vbo; //VBO with interleaved data
	GLuint				vboi; //VBO with indices into the data VBO
	GLuint				vao;
	unsigned int		indexCount;
	unsigned int		vertexCount;
	unsigned int 		elementCount;
	unsigned int		vertexSize;

};

#endif // __SCENE_MESH_H__
