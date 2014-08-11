/* Copyright 2014 Lasse Dissing
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "Window.h"

void error_callback(int error, const char* desc) {
	ERROR("Error %d: %s",error,desc);
}

bool Window::Create(const int width, const int height, const std::string& title) {

	glfwSetErrorCallback(error_callback);

	glfwInit();

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_DECORATED, GL_TRUE);
	glfwWindowHint(GLFW_RED_BITS, 8);
	glfwWindowHint(GLFW_GREEN_BITS, 8);
	glfwWindowHint(GLFW_BLUE_BITS, 8);
	glfwWindowHint(GLFW_DEPTH_BITS, 24);
	glfwWindowHint(GLFW_STENCIL_BITS, 8);

	glfwWindowHint(GLFW_CLIENT_API,GLFW_OPENGL_API);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef DEBUG
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#else 
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_FALSE);
#endif

	window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

	return !!window;
}

void Window::Destroy() {
	glfwDestroyWindow(window);
	glfwTerminate();
}

void Window::ActivateContext() {
	glfwMakeContextCurrent(window);
}

void Window::SwapBuffers() {
	glfwSwapBuffers(window);
}

void Window::PollEvents() {
	glfwPollEvents();
}


bool Window::ShouldClose() const {
	return glfwWindowShouldClose(window) == GL_TRUE;
}

bool Window::IsFocused() const {
	return glfwGetWindowAttrib(window, GLFW_FOCUSED) == GL_TRUE;
}

bool Window::IsDecorated() const {
	return glfwGetWindowAttrib(window, GLFW_DECORATED) == GL_TRUE;
}

bool Window::IsVisible() const {
	return glfwGetWindowAttrib(window, GLFW_VISIBLE) == GL_TRUE;
}

void Window::SetVisibility(const bool visible) {
	if (visible) {
		glfwShowWindow(window);
	} else {
		glfwHideWindow(window);
	}
}

bool Window::IsMinimised() const {
	return glfwGetWindowAttrib(window, GLFW_ICONIFIED) == GL_TRUE;
}

void Window::SetMinimised(const bool minimised) {
	if (minimised) {
		glfwIconifyWindow(window);
	} else {
		glfwRestoreWindow(window);
	}
}

void Window::SetTitle(const std::string& title) {
	glfwSetWindowTitle(window,title.c_str());
}

int Window::GetWidth() const {
	int *w = 0;
	int *h = 0;
	glfwGetWindowSize(window, w, h);
	return (*w);
}

int Window::GetHeight() const {
	int* w = 0;
	int* h = 0;
	glfwGetWindowSize(window, w, h);
	return (*h);
}

void Window::SetSize(const int width, const int height) {
	glfwSetWindowSize(window, width, height);
}

int Window::GetPosX() const {
	int* x = 0;
   	int* y = 0;
	glfwGetWindowPos(window, x, y);
	return (*x);
}

int Window::GetPosY() const {
	int* x = 0;
   	int* y = 0;
	glfwGetWindowPos(window, x, y);
	return (*y);
}

void Window::SetPosition(const int width, const int height) {
	glfwSetWindowPos(window, width, height);
}

GLFWwindow* Window::GetWindowPointer() const {
	return window;
}
