/* Copyright 2014 Lasse Dissing
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef __RENDERER_RENDERER_H__
#define __RENDERER_RENDERER_H__

#include <Phobetor.h>
#include <scene/Node.h>
#include <scene/Geometry.h>
#include <renderer/Camera.h>
#include <renderer/Shader.h>

class Renderer {

public:
						Renderer();

	void				Init(const bool offscreenRendering = false);
	void				Render();
	void				Destroy();

	Node&				GetRootNode();
	Camera&				GetCamera();

private:

	void				PrepareOffscreenRendering();

	void 				walkSceneGraph(Node& rootNode, Shader& shader);

	Camera				camera;
	Node				rootNode;
	Shader				shader; //TODO Make a hashmap for multiple shaders


	/* Offscreen OpenGL-stuff*/

	bool				offscreen;
	GLuint 				fbo;
	GLuint 				rboColor, rboDepth;
	std::vector<GLubyte> data;

};

#endif // __RENDERER_RENDERER_H__
