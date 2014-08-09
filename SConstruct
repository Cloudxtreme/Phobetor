# Copyright 2014 Lasse Dissing
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/. */

import sys
import os
import glob


#Create common env

env = Environment()

env.Append(CPPPATH = ['../../libs','../../src'])
env.Append(LIBPATH = ['../../libs'])
env.Append(LIBS = ['GLEW'])
env.Append(CPPFLAGS = ['-Wall', '-Werror','--std=c++11'])

sources = []

#Add platform specific stuff

platform = sys.platform

if platform.startswith('linux'):
    env.Replace(CXX = "clang++")
    env['ENV']['TERM'] = os.environ['TERM'] #Adds color to clang output. No idea why it works
    env.ParseConfig('pkg-config --cflags glfw3')
    env.ParseConfig('pkg-config --static --libs glfw3')
else:
    print ("Platform not supported yet. Aborting.")
    Exit(-1)

#Recursivly find ind all sources

sources = SConscript('src/SConscript')

Export('env','sources')

SConscript('scons/debug',variant_dir='build/debug', duplicate=0)
SConscript('scons/testing',variant_dir='build/testing', duplicate=0)
SConscript('scons/release',variant_dir='build/release', duplicate=0)
