/* Copyright 2014 Lasse Dissing
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <Phobetor.h>
#include "Window.h"
#include "Timer.h"
#include "../renderer/Mesh.h"
#include "../renderer/Shader.h"

float data[] = {
	-0.5f, 0.5f, 0.0f,	1.0f, 0.0f, 0.0f, 1.0f,
	-0.5f,-0.5f, 0.0f,	0.0f, 1.0f, 0.0f, 1.0f,
	 0.5f,-0.5f, 0.0f,	0.0f, 0.0f, 1.0f, 1.0f,
	 0.5f, 0.5f, 0.0f,	1.0f, 1.0f, 1.0f, 1.0f
};

unsigned int indices[] = {
	0,1,2,
	2,3,0
};

bool initOpenGL(Window& window) {
	window.ActivateContext();
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (err != GLEW_OK) {
		FATAL("Failed to init glew: ", glewGetErrorString(err), '\n');
		window.Destroy();
		return false;
	}

	if (!GLEW_VERSION_3_2) {
		FATAL("OpenGL version 3.2 not avalible!");
		return false;
	}

	glGetError(); //Clear errors
	return true;
}

void error(const char* location) {
	GLenum glErr = glGetError();

	switch(glErr) {
		case GL_INVALID_OPERATION:	WARN("Invalid Operation\n");	break;
		case GL_INVALID_ENUM:		WARN("Invalid Enum\n"); 		break;
		case GL_INVALID_VALUE:		WARN("Invalid Value\n");		break;
		case GL_OUT_OF_MEMORY:		WARN("Out of memory\n");		break;
		case GL_INVALID_FRAMEBUFFER_OPERATION: WARN("Framebuffer\n");break;

	}

	if (glErr != GL_NO_ERROR) {
		WARN("OpenGL error in ", location, '\n');
	}
}

int main() {

	initLogger(LOG_DEBUG);

	Window window;

	if (!window.Create(1280,720, "Phobetor")) {
		FATAL("Failed to create window. Exiting!");
		return -1;
	}

	if (!initOpenGL(window)) {
		return -1;
	}

	Shader shader;

	shader.SetupShader("shaders/simple.vertex","shaders/simple.fragment");
	Mesh quad;
	
	quad.SetData(data, sizeof(data), 28);
	quad.SetIndices(indices, sizeof(indices));
	quad.UploadToGPU();


	Timer timer;
	
	//DO NOT PUT ANY TIME CONSUMING CODE BETWEEN TIMER INITIALISATION AND LOOP!!!

	while (!window.ShouldClose()) {
	
		/* Update as long as realtime is ahead of simulationTime*/
		while (timer.ShouldTick()) {
			timer.OnTick(); //Advances simulationtime with 16 milliseconds
		}

		timer.OnRender();


		glClearColor(1.0f,1.0f,1.0f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		shader.UseShader();

		quad.Render();

		window.SwapBuffers();
		window.PollEvents();
	}


	window.Destroy();
}
