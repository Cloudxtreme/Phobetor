/* Copyright 2014 Lasse Dissing
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef __SYSTEM_LOGGER_H__
#define __SYSTEM_LOGGER_H__

#include<Phobetor.h>

#define LOG_OFF 99
#define LOG_DEBUG 1
#define LOG_INFO 2
#define LOG_WARN 3
#define LOG_ERROR 4
#define LOG_FATAL 5

extern int globalLogLevel;

extern bool initLogger(int level = 2);
extern void log(int level, const std::string& file, int line, int count, ...);

#define COUNT_ARGUMENTS(_1,_2,_3,_4,_5,_6,N,...) N

#if defined(LOGGING) || defined(DEBUG)
    #define LOG(level,...) log(level,__FILE__,__LINE__,  \
			COUNT_ARGUMENTS(__VA_ARGS__,6,5,4,3,2,1), __VA_ARGS__)
	#define DEBUG(...) LOG(1,__VA_ARGS__)
    #define INFO(...) LOG(2,__VA_ARGS__)
    #define WARN(...) LOG(3,__VA_ARGS__)
	#define ERROR(...) LOG(4,__VA_ARGS__)
    #define FATAL(...) LOG(5,__VA_ARGS__)
#else
    #define LOG(...)
    #define DEBUG(...)
    #define INFO(...)
    #define WARN(...)
	#define ERROR(...)
    #define FATAL(...)
#endif

#endif // __SYSTEM_LOGGER_H__
