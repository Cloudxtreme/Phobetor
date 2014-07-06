/* Copyright 2014 Lasse Dissing
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "Logger.h"

int globalLogLevel = 0;

bool initLogger(int level) {
	globalLogLevel = level;

	return true;
}

const char* levelString(int level) {
	switch (level) {
		case LOG_DEBUG: return "[DEBUG] ";
		case LOG_INFO:  return "";
		case LOG_WARN:  return "[WARN] ";
		case LOG_ERROR: return "[ERROR] ";
		case LOG_FATAL: return "[FATAL] ";
		default:		return "[FISHY] ";
	}
}

void log(int level, const std::string& file, int line, int count, ...) {

	if (level >= globalLogLevel) {

		int pos = file.find_last_of('/');

		std::cout << levelString(level) << file.substr(pos+1) << ':' << line << ":\t";
		va_list args;
		va_start(args,count);
		
		for (int i = 0; i < count; i++) {
			std::cout << va_arg(args, char*);
		}
		std::cout << '\n';
	}
}
