#pragma once
#ifndef BASE_GUAGE_H
#define BASE_GUAGE_H

#include "Needle.h"
#include"Defines.h"

#include <SDL.h>
#include <SDL_image.h>


class BaseGauge {
public:
	 BaseGauge(SDL_Window* window, SDL_Renderer* renderer): 
	  needle(window, renderer)
	 {
	
	 }
	virtual void render(SDL_Renderer* renderer) {

		SDL_RenderCopyEx(renderer, needle.get_texture(), NULL, &needle.get_rect(), needle.angle, get_center_p(), SDL_FLIP_NONE);

	}
	SDL_Texture* get_texture()
	{
		return needle.get_texture();
	}

	void test_needle(int val = 1) {
		static bool dec = false;
		if (needle.angle > 240)
		{
			dec = true;
		}
		else if (needle.angle < -30)
		{
			dec = false; // 
		}
		if (dec=true)
		{
			val = val * (1);
		}
		needle.angle += val;

		
		needle.angle += val;
	}

	SDL_Rect& get_rect() {
		return needle.get_rect();
	}
	int get_angle() {
		needle.get_angle();
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
