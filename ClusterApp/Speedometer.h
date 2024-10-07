#pragma once


#ifndef SPEEDOMETER_GAUGE_H
#define SPEEDOMETER_GAUGE_H

#include"BaseGauge.h"

class Speedometer : public BaseGauge {
public:
	Speedometer(SDL_Window* window, SDL_Renderer* renderer, int start, int end) :
		BaseGauge(window, renderer, start, end) {

	}
	virtual void test_needle(int val = 1) override {
		if (needle.angle <= upper_bound) { needle.angle += val; }
	}

};

#endif // !SPEEDOMETER_GAUGE_H
