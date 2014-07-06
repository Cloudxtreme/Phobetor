/* Copyright 2014 Lasse Dissing
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "Mesh.h"

Mesh::Mesh() {
	type = this->TRIANGLES;
}

void Mesh::UploadToGPU() {

	glGenVertexArrays(1,&vao);
	glBindVertexArray(vao);


	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);

	//Position in slot 1
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexSize, 0); 
	glEnableVertexAttribArray(0);

	//Color in slot 2
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, vertexSize, (GLvoid*)(sizeof(GL_FLOAT) * 3)); 
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &vboi);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboi);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(GL_UNSIGNED_INT), indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
	glBindVertexArray(0);
}

void Mesh::DeleteFromGPU() { 
	
	glDeleteVertexArrays(1,&vao);
	glDeleteBuffers(1,&vbo);
	glDeleteBuffers(1,&vboi);
}

void Mesh::Render() {

		glBindVertexArray(vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,vboi);
		glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
		glBindVertexArray(0);
		
}


void Mesh::SetData(float* data, unsigned int size, unsigned int vertexSize) {
	this->data = data;
	dataSize = size;
	this->vertexSize = vertexSize;
	elementCount = size / vertexSize;
}

void Mesh::SetIndices(unsigned int* indices, unsigned int size) {
	this->indices = indices;
	indexCount = size / sizeof(GL_INT);
	vertexCount = indexCount / 3;
}

