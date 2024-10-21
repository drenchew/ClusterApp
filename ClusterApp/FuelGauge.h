#pragma once
#ifndef FUEL_GAUGE_H
#define FUEL_GAUGE_H

#include"BaseGauge.h"
#include<chrono>

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
	
	void on_start() {

	}

	virtual void update_needle(float value, float min_val, float max_val) override final{
		using namespace std::chrono_literals;

		while (needle.angle > max_val / 1.6 && needle.angle > min_val)
		{
			needle.angle -= value;
			std::this_thread::sleep_for(80ms);
		}
		
	}

	double fuel_left = 0;
};

#endif // !FUEL_GAUGE_H



