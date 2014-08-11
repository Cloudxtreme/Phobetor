/* Copyright 2014 Lasse Dissing
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef __RENDERER_SHADER_H__
#define __RENDERER_SHADER_H__

#include <Phobetor.h>
#include <math/Math.h>

class Shader {

public:
	
						~Shader();

	bool				SetupShader(const char* vertexLocation, const char* fragmentLocation);

	GLint				GetAttributeLocation(const char* attribute);

	void				UseShader(const Mat4& projectionMatrix);

	void				SetModelMatrix(const Mat4& modelMatrix);

private:

	bool				CheckCompileStatus(GLuint id, const char* filename);

	char*				LoadString(const char* filename);
	

	GLuint				vertexShader;
	GLuint				fragmentShader;
	GLuint				program;

	GLuint				projectionMatrixLocation;
	GLuint				modelMatrixLocation;

};

#endif // __RENDERER_SHADER_H__
