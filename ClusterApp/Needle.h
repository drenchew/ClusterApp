#pragma once

#ifndef NEEDLE_H
#define NEEDLE_H

#include <SDL.h>
#include <SDL_image.h>
#include<cstdio>
#include<string>
#include"Defines.h"

class Needle {
public:
	SDL_Texture* _image;

	SDL_Rect rect; // represent the needle
	SDL_Point needleCenter;

	int angle = 0;
	int max_angle = 360;

	Needle() = default;

	int get_angle() const 
	{
		return angle;
	}
	SDL_Point* get_center_point()
	{
		return &needleCenter;
	}

	Needle(SDL_Window* window,SDL_Renderer* renderer)
	{
		// Load a PNG image into a texture
		 _image = IMG_LoadTexture(renderer, NEEDLE_PATH);
		if (!_image) {
			printf("Failed to load texture: %s\n", IMG_GetError());
		}
	}

	SDL_Texture* get_texture() {
		return _image;
	}
	SDL_Rect& get_rect() {
		return rect;
	}

	void set_position(int x,int y,int w,int h,int nx,int ny) {
		rect.x = x;
		rect.y = y;
		rect.w = w;
		rect.h = h;

		needleCenter.x = nx;
		needleCenter.y = ny;

		
	}



};


#endif // !NEEDLE_H
