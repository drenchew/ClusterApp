#pragma once
#ifndef BASE_GUAGE_H
#define BASE_GUAGE_H

#include "Needle.h"
#include"Defines.h"

#include <SDL.h>
#include <SDL_image.h>

#include<mutex>


class BaseGauge {
public:
	BaseGauge(SDL_Window* window, SDL_Renderer* renderer, int start=0, int end=0) :
		lower_bound(start), upper_bound(end),
	  needle(window, renderer)
	 {
		needle.angle = lower_bound;
	 }
	virtual void render(SDL_Renderer* renderer) {

		SDL_RenderCopyEx(renderer, needle.get_texture(), NULL, &needle.get_rect(), needle.angle, needle.get_center_point(), SDL_FLIP_NONE);

	}
	SDL_Texture* get_texture()
	{
		return needle.get_texture();
	}

	int lower_bound ;
	int upper_bound ;
	int current_val =0;

	virtual void test_needle(int val = 1) {
		needle.angle += val;
	}

	virtual void update_needle(const int val) {
		//use mutex here
		
		int new_val = needle.angle + val;
		if (new_val < upper_bound && new_val>lower_bound)
		{
			needle.angle = new_val;
		}
		printf(" the angle: %d\n", needle.angle);
		
	}

	void test_in_range(int start , int end) {
		
		
	}

	SDL_Rect& get_rect() {
		return needle.get_rect();
	}
	int get_angle() {
		return needle.get_angle();
	}

	
	virtual void kill() {
		SDL_DestroyTexture(needle.get_texture());
		
	}

	virtual ~BaseGauge() = default;

	float value=0;

	Needle needle;
};

#endif // !BASE_GUAGE_H
