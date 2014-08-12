/* Copyright 2014 Lasse Dissing
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <Phobetor.h>
#include "Window.h"
#include "Timer.h"
#include <renderer/Camera.h>
#include <renderer/Renderer.h>
#include <scene/Node.h>
#include <asset/OBJLoader.h>

float data[] = {
	-0.5f, 0.5f, 0.0f,	1.0f, 0.0f, 0.0f,
	-0.5f,-0.5f, 0.0f,	0.0f, 1.0f, 0.0f,
	 0.5f,-0.5f, 0.0f,	0.0f, 0.0f, 1.0f,
	 0.5f, 0.5f, 0.0f,	0.5f, 0.5f, 0.5f
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

	glGetError(); //Clear errors from GLEW
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

void processInput(GLFWwindow* windowPtr, Camera& camera) {

	if (glfwGetKey(windowPtr, GLFW_KEY_W)) {
		camera.MoveCameraForward(0.01f);
	} else if (glfwGetKey(windowPtr, GLFW_KEY_S)) {
		camera.MoveCameraForward(-0.01f);
	}

	if (glfwGetKey(windowPtr, GLFW_KEY_A)) {
		camera.MoveCameraLeft(0.01f);
	} else if (glfwGetKey(windowPtr, GLFW_KEY_D)) {
		camera.MoveCameraLeft(-0.01f);
	}

	if (glfwGetKey(windowPtr, GLFW_KEY_UP)) {
		camera.RotateCamera(0,0,-0.02f);
	} else if (glfwGetKey(windowPtr, GLFW_KEY_DOWN)) {
		camera.RotateCamera(0,0,0.02f);
	} else if (glfwGetKey(windowPtr, GLFW_KEY_LEFT)) {
		camera.RotateCamera(0,-0.02f,0);		
	} else if (glfwGetKey(windowPtr, GLFW_KEY_RIGHT)) {
		camera.RotateCamera(0,0.02f,0);
	} else {
		camera.RotateCamera(0,0,0);
	}

	if (glfwGetKey(windowPtr, GLFW_KEY_ESCAPE)) {
		glfwSetWindowShouldClose(windowPtr,1);
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

	Renderer renderer;

	renderer.Init();
	renderer.GetCamera().MoveCamera(1,0,-2);

	OBJLoader loader;

	Node* modelNode = loader.Load("assets/Cube.obj");
	renderer.GetRootNode().AttachChild(modelNode);
	modelNode->UpdateState();

	Timer timer;
	
	//DO NOT PUT ANY TIME CONSUMING CODE BETWEEN TIMER INITIALISATION AND LOOP!!!


	while (!window.ShouldClose()) {
	
		/* Update as long as realtime is ahead of simulationTime*/
		while (timer.ShouldTick()) {
			timer.OnTick(); //Advances simulationtime with 16 milliseconds
		}

		timer.OnRender();

		renderer.Render();

		processInput(window.GetWindowPointer(),renderer.GetCamera());


		window.SwapBuffers();
		window.PollEvents();
	}

	renderer.Destroy();
	window.Destroy();
}
