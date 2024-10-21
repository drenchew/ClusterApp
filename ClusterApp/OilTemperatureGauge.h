#pragma once


#ifndef OIL_TEMPERATURE_GAUGE_H
#define OIL_TEMPERATURE_GAUGE_H

#include"BaseGauge.h"

class OilTempGauge : public BaseGauge { 
public:
	OilTempGauge(SDL_Window* window, SDL_Renderer* renderer, int start, int end) :
		BaseGauge(window, renderer, start, end) {

	}

	virtual void update_needle(float value, float min_val, float max_val) override final {
		using namespace std::chrono_literals;
		
		while (1) //needle.angle <70
		{
			needle.angle += 1;
			std::this_thread::sleep_for(80ms);
			//printf("Oiltem %d:\n ", needle.angle);
		}
		
	}

	virtual void test_needle(int val = 1) override {
		if (needle.angle <= upper_bound) { needle.angle += val; }
	}

};

#endif // !OIL_TEMPERATURE_GAUGE_H
