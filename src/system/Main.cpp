/* Copyright 2014 Lasse Dissing
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <Phobetor.h>
#include "Window.h"
#include "Timer.h"
#include "../renderer/Mesh.h"
#include "../renderer/Shader.h"
#include "../renderer/Camera.h"
#include "../scene/Node.h"
#include "../scene/Spatial.h"
#include "../scene/Geometry.h"
#include "../asset/OBJLoader.h"

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
		camera.MoveCamera(0.0f, 0.0f, 0.01f);
	} else if (glfwGetKey(windowPtr, GLFW_KEY_S)) {
		camera.MoveCamera(0.0f, 0.0f, -0.01f);
	}

	if (glfwGetKey(windowPtr, GLFW_KEY_A)) {
		camera.MoveCamera(0.01f, 0.0f ,0.0f);
	} else if (glfwGetKey(windowPtr, GLFW_KEY_D)) {
		camera.MoveCamera(-0.01f, 0.0f, 0.0f);
	}

	if (glfwGetKey(windowPtr, GLFW_KEY_LEFT)) {
		camera.RotateCameraEuler(0.001f, 0.0f, 0.0f);
	} else if (glfwGetKey(windowPtr, GLFW_KEY_RIGHT)) {
		camera.RotateCameraEuler(-0.001f, 0.0f, 0.0f);
	}

	if (glfwGetKey(windowPtr, GLFW_KEY_ESCAPE)) {
		glfwSetWindowShouldClose(windowPtr,1);
	}

}

void walkSceneGraph(Node* rootNode, Shader& shader) {
	for (Spatial* child : rootNode->GetChildren()) {
		switch (child->GetSpatialType()) {
			case Spatial::Geometry: {
				Geometry* geom = static_cast<Geometry*>(child);
				shader.SetModelMatrix(geom->GetWorldTransform().ToMatrix());
				geom->GetMesh()->Render();
				break;
			}
			case Spatial::Node: {
				walkSceneGraph(static_cast<Node*>(child), shader);
				break;						
			}
		}
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

	Camera camera;
	camera.MoveCamera(0,0,-2);

	Shader shader;


	shader.SetupShader("shaders/simple.vertex","shaders/simple.fragment");
	

	OBJLoader loader;

	Node* rootNode = new Node();

	Node* modelNode = loader.Load("assets/Cube.obj");
	rootNode->AttachChild(modelNode);
	modelNode->UpdateState();

	Timer timer;
	
	//DO NOT PUT ANY TIME CONSUMING CODE BETWEEN TIMER INITIALISATION AND LOOP!!!


	while (!window.ShouldClose()) {
	
		/* Update as long as realtime is ahead of simulationTime*/
		while (timer.ShouldTick()) {
			timer.OnTick(); //Advances simulationtime with 16 milliseconds
		}

		timer.OnRender();

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);

		glClearColor(1.0f,1.0f,1.0f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		Mat4 projectionView = camera.GetProjectionView();
		shader.UseShader(projectionView);
		////shader.SetModelMatrix(rootNode->)
		error("Shader");

		processInput(window.GetWindowPointer(),camera);

		walkSceneGraph(rootNode, shader);
		

		window.SwapBuffers();
		window.PollEvents();
	}


	window.Destroy();
}
