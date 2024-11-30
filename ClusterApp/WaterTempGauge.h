#pragma once


#ifndef WATER_TEMP_GAUGE_H
#define WATER_TEMP_GAUGE_H

#include"BaseGauge.h"

class WaterTempGauge : public BaseGauge {
public:
	WaterTempGauge(SDL_Window* window, SDL_Renderer* renderer, int start, int end) :
		BaseGauge(window, renderer, start, end) {

	}

	void update_needle(float value, float min_val, float max_val) override final {
		using namespace std::chrono_literals;

		while (needle.angle > 260)
		{
			needle.angle -= 1;
			std::this_thread::sleep_for(100ms);
			std::cout << "Water Temp: " << needle.angle << std::endl;
		}

	}

	virtual void test_needle(int val = 1) override {
		if (needle.angle >= upper_bound) { needle.angle -= val; }
	}

};

#endif // !WATER_TEMP_GAUGE_H
