/* Copyright 2014 Lasse Dissing
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "Renderer.h"

Renderer::Renderer() : camera(), rootNode() {

}

void Renderer::Init(const bool offscreen) {
	shader.SetupShader("shaders/simple.vertex","shaders/simple.fragment");
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

}

void Renderer::Destroy() {

}

Node& Renderer::GetRootNode() {
	return rootNode;
}

Camera& Renderer::GetCamera() {
	return camera;
}
