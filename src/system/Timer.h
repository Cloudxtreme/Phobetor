/* Copyright 2014 Lasse Dissing
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef __SYSTEM_TIMER_H__
#define __SYSTEM_TIMER_H__

class Timer {

public:

				explicit Timer();

	void		OnRender();
	void		OnTick();

	bool		ShouldTick() const;

	double		GetTime() const;
	double		GetSimTime() const;

	double		GetFPS() const;
	double		GetTPS() const;
	double		GetTimePerFrame() const;
	double		GetTimePerTick() const;	

private:

	/* All timers in milliseconds */

	double 		realTime; //Last measured time from the OS
   	double 		simulationTime; //The current time in simulation. Runs on fixed timestep
	double 		lastRenderTime; //Used to calculate frames per second
	double 		lastTickTime; //Used to calculate ticks per second

	double		nextPrintTime; 

	double 		TPT; //Time per tick
	double 		TPF; //Ticks per second

	double 		TPS; //Ticks per second
	double 		FPS; //Frames per second

};

inline Timer::Timer() {
	realTime = 0.0;
	simulationTime = 0.0;
	lastRenderTime = 0.0;
	lastTickTime = 0.0;
	nextPrintTime = 0.0;
	TPT = 0.0;
	TPF = 0.0;
	TPS = 0.0;
	FPS = 0.0;
	glfwSetTime(0);
}

inline void Timer::OnRender() {
	realTime = glfwGetTime() * 1000;
	TPF = (realTime - lastRenderTime);
	FPS = 1000.0 / TPF;
	lastRenderTime = realTime;
}

inline void Timer::OnTick() {
	simulationTime += 16.66;
	TPT = (simulationTime - lastTickTime);
	TPS = 1000.0 / TPT;
	lastTickTime = simulationTime;
}

inline bool Timer::ShouldTick() const {
	return (simulationTime < realTime);
}

inline double Timer::GetTime() const {
	return realTime;
}

inline double Timer::GetSimTime() const {
	return simulationTime;
}

inline double Timer::GetFPS() const {
	return FPS;
}

inline double Timer::GetTPS() const {
	return TPS;
}

inline double Timer::GetTimePerFrame() const {
	return TPF;
}

inline double Timer::GetTimePerTick() const {
	return TPT;
}

#endif //  __SYSTEM_TIMER_H__
