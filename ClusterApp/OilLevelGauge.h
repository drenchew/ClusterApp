#pragma once
#pragma once


#ifndef OIL_LEVEL_GAUGE_H
#define OIL_LEVEL_GAUGE_H

#include"BaseGauge.h"

class OilLevelGauge : public BaseGauge {
public:
	OilLevelGauge(SDL_Window* window, SDL_Renderer* renderer, int start, int end) :
		BaseGauge(window, renderer, start, end) {

	}
	virtual void test_needle(int val = 1) override {
		if (needle.angle <= upper_bound) { needle.angle += val; }
	}

};

#endif // !OIL_LEVEL_GAUGE_H
