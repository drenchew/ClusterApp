#pragma once
#ifndef BASE_GUAGE_H
#define BASE_GUAGE_H

#include "Needle.h"
#include"Defines.h"

#include <SDL.h>
#include <SDL_image.h>


class BaseGauge {
public:
	BaseGauge(SDL_Window* window, SDL_Renderer* renderer, int start=0, int end=0) :
		lower_bound(start), upper_bound(end),
	  needle(window, renderer)
	 {
		needle.angle = lower_bound;
	 }
	virtual void render(SDL_Renderer* renderer) {

		SDL_RenderCopyEx(renderer, needle.get_texture(), NULL, &needle.get_rect(), needle.angle, get_center_p(), SDL_FLIP_NONE);

	}
	SDL_Texture* get_texture()
	{
		return needle.get_texture();
	}

	int lower_bound ;
	int upper_bound ;
	int current_val =0;

	virtual void test_needle(int val = 1) {
		//static int num = 0;
		//std::cout << "here from " << num++ << std::endl;;

		
		needle.angle += val;
	}

	void test_in_range(int start , int end) {
		
		
	}

	SDL_Rect& get_rect() {
		return needle.get_rect();
	}
	int get_angle() {
		return needle.get_angle();
	}

	SDL_Point* get_center_p() {
		return needle.get_center_point();
	}
	virtual void kill() {
		SDL_DestroyTexture(needle.get_texture());
		
	}

	virtual ~BaseGauge() = default;

	float value=0;

	Needle needle;
};

#endif // !BASE_GUAGE_H
