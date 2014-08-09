/* Copyright 2014 Lasse Dissing
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "Shader.h"
#include <cstdlib>



Shader::~Shader() {
	glUseProgram(0);
	glDetachShader(program, vertexShader);
	glDetachShader(program, fragmentShader);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteProgram(program);
}

bool Shader::SetupShader(const char* vertex, const char* fragment) {
	
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	program = glCreateProgram();

	const char* vertexSource = LoadString(vertex);
	const char* fragmentSource = LoadString(fragment);

	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);

	GLint linkStatus = GL_FALSE;

	glCompileShader(vertexShader);
	CheckCompileStatus(vertexShader, vertex);	

	glCompileShader(fragmentShader);
	CheckCompileStatus(fragmentShader,fragment);	

	//Remembered to free memory = WIN!
	free((void*) vertexSource);
	free((void*) fragmentSource);

	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	glBindAttribLocation(program, 0, "position");
	glBindAttribLocation(program, 1, "color");

	
	glLinkProgram(program);
	glValidateProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
	if (linkStatus == 0) {
		ERROR("Error linking program");
		return false;
	}


	projectionMatrixLocation = glGetUniformLocation(program, "projectionViewMatrix");

	return true;	
}

GLint Shader::GetAttributeLocation(const char* attribute) {
	return glGetAttribLocation(program, attribute);
}

void Shader::UseShader(Mat4& projectionMatrix) {
	glUseProgram(program);
	glUniformMatrix4fv(projectionMatrixLocation, 1, true, projectionMatrix.GetRaw());
}

bool Shader::CheckCompileStatus(GLuint id, const char* filename) {
	GLint compileStatus = GL_FALSE;

	glGetShaderiv(id, GL_COMPILE_STATUS, &compileStatus);
	if (compileStatus == 0) {
		ERROR("Error compiling ",filename);
		
		int logLength = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &logLength);
		char* log = (char*) malloc(logLength * sizeof(char));

		glGetShaderInfoLog(id, logLength, &logLength, log);

		std::printf("%s\n",log);
		free(log);
		return false;
	}
	return true;
}

char* Shader::LoadString(const char* filename) {
	FILE* file = fopen(filename, "r");

	if (!file) {
		ERROR("Unable to open file ", filename);
		return NULL;
	}
	
	fseek(file, 0L, SEEK_END);
	long size = ftell(file);
	rewind(file);

	char* text = (char*) malloc(size+1);

	fread(text, size, 1, file);
	text[size] = '\0';
	fclose(file);

	return text;
}
