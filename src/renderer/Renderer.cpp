/* Copyright 2014 Lasse Dissing
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "Renderer.h"

Renderer::Renderer() : camera(), rootNode() {

}

void Renderer::Init(const bool offscreenRendering) {
	offscreen = offscreenRendering;
	if (offscreen) {
		PrepareOffscreenRendering();
	}
	shader.SetupShader("shaders/simple.vertex","shaders/simple.fragment");
}

void Renderer::PrepareOffscreenRendering() {

	//Setup databuffer for transfering the Framebuffer content from GPU to network
	data = std::vector<GLubyte>(3*640*480);

	//Initialise Color Renderbuffer
	glGenRenderbuffers(1, &rboColor);
	glBindRenderbuffer(GL_RENDERBUFFER, rboColor);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA4, 640,  480);

	//Initialise Depth Renderbuffer
	glGenRenderbuffers(1,&rboDepth);
	glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 640, 480);

	//Initialise Framebuffer
	glGenFramebuffers(1,&fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, rboColor);
	glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_DEPTH_TEST, GL_RENDERBUFFER, rboDepth);

	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	glReadBuffer(GL_COLOR_ATTACHMENT0);

}

void Renderer::walkSceneGraph(Node& rootNode, Shader& shader) {
	for (Spatial* child : rootNode.GetChildren()) {
		switch (child->GetSpatialType()) {
			case Spatial::Geometry: {
				Geometry* geom = static_cast<Geometry*>(child);
				shader.SetModelMatrix(geom->GetWorldTransform().ToMatrix());
				geom->GetMesh()->Render();
				break;
			}
			case Spatial::Node: {
				walkSceneGraph(*static_cast<Node*>(child), shader);
				break;						
			}
		}
	}
}

void Renderer::Render() {

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glClearColor(1.0f,1.0f,1.0f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shader.UseShader(camera.GetProjectionView());

	walkSceneGraph(rootNode,shader);

	if (offscreen) {
		glReadPixels(0, 0, 640, 480, GL_RGB, GL_UNSIGNED_BYTE, &data[0]);
		for (int i = 0; i < 3 * 640 * 480; i++) {
			std::cout << data[i];
		}
	}

}

void Renderer::Destroy() {

}

Node& Renderer::GetRootNode() {
	return rootNode;
}

Camera& Renderer::GetCamera() {
	return camera;
}
