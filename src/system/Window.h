/* Copyright 2014 Lasse Dissing
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef __SYSTEM_WINDOW_H__
#define __SYSTEM_WINDOW_H__

#include <Phobetor.h>

class Window {

public:

						explicit Window() {};

	bool				Create(const int width, const int height, const std::string &title);
	bool				CreateOffscreen();
	void				Destroy();

	void				ActivateContext();

	void				SwapBuffers();
	void				PollEvents();

	bool				ShouldClose() const;
	bool				IsFocused() const;
	bool				IsDecorated() const;

	bool				IsVisible() const;
	void				SetVisibility(const bool visible);
	bool				IsMinimised() const;
	void				SetMinimised(const bool minimised);

	void				SetTitle(const std::string& title);

	int					GetWidth() const;
	int					GetHeight() const;
	void				SetSize(const int width, const int height);

	int					GetPosX() const;
	int					GetPosY() const;
	void				SetPosition(const int width, const int height);

	GLFWwindow*			GetWindowPointer() const;

private:
	GLFWwindow* window;


};

#endif // __SYSTEM_WINDOW_H__
