#pragma once


#ifndef WATER_TEMP_GAUGE_H
#define WATER_TEMP_GAUGE_H

#include"BaseGauge.h"

class WaterTempGauge : public BaseGauge {
public:
	WaterTempGauge(SDL_Window* window, SDL_Renderer* renderer, int start, int end) :
		BaseGauge(window, renderer, start, end) {

	}
	virtual void test_needle(int val = 1) override {
		if (needle.angle >= upper_bound) { needle.angle -= val; }
	}

};

#endif // !WATER_TEMP_GAUGE_H
