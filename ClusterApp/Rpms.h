#pragma once


#ifndef RPMS_H
#define RPMS_H

#include"BaseGauge.h"

class RPMGauge : public BaseGauge { //240 upper
public:
	RPMGauge(SDL_Window* window, SDL_Renderer* renderer,int start,int end) :
		BaseGauge(window, renderer,start,end) {

	}
	virtual void test_needle(int val = 1) override {
		if (needle.angle <= upper_bound) { needle.angle += 4; }
	}

};

#endif // !RPMS_H
