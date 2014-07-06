/* Copyright 2014 Lasse Dissing
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef __PHOBETOR_H__
#define __PHOBETOR_H__

//Old c-style is still nice sometimes
//NO STDIO as IOstream sync is disabled. I miss printf....
#include <cmath>
#include <cassert>

//IOstream is a bit nicer for complex stuff.
//But not on the eyes... Or the performance. Why the hell did I switch?
#include <iostream>
#include <fstream>
#include <sstream>

//STL containers
#include <vector>
#include <map>
#include <string>
#include <set>
#include <list>

//Other STL stuff
//#include <functional>

//GL libraries
#include <GL/glew.h>
#include <GLFW/glfw3.h>

//Forward declaration to reduce header imports

class Mesh;
class Shader;


//Often used stable Phobetor headers
#include "system/Logger.h"


#endif // __PHOBETOR_H__
