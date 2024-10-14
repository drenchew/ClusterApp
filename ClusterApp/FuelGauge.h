#pragma once
#ifndef FUEL_GAUGE_H
#define FUEL_GAUGE_H

#include"BaseGauge.h"

class FuelGauge final: public BaseGauge{
public:

	FuelGauge(SDL_Window* window, SDL_Renderer* renderer,int start,int end):
		BaseGauge(window,renderer,start,end)
	{

	}

	virtual void test_needle(int val = 1) override {
		//test_in_range(lower_bound, upper_bound);
		if (needle.angle > upper_bound) { needle.angle -= val; }
	}

	virtual void update_needle(float value, float min_val, float max_val) override final{

	}

	double fuel_left = 0;
};

#endif // !FUEL_GAUGE_H



