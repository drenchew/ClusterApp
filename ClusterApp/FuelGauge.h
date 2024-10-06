#pragma once
#ifndef FUEL_GAUGE_H
#define FUEL_GAUGE_H

#include"BaseGauge.h"

class FuelGauge : public BaseGauge{
public:

	FuelGauge(SDL_Window* window, SDL_Renderer* renderer):
		BaseGauge(window,renderer)
	{

	}


};

#endif // !FUEL_GAUGE_H



