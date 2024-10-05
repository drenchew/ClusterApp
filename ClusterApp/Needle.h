#pragma once

#ifndef NEEDLE_H
#define NEEDLE_H

#include <SDL.h>
#include <SDL_image.h>
#include<cstdio>
#include<string>

class Needle {
public:
	SDL_Texture* _image;

	SDL_Rect rect; // represent the needle
	SDL_Point needleCenter;
	int angle = 0;

	Needle(SDL_Window* window,SDL_Renderer* renderer,std::string& path)
	{
		// Load a PNG image into a texture
		 _image = IMG_LoadTexture(renderer, path.c_str());
		if (!_image) {
			printf("Failed to load texture: %s\n", IMG_GetError());
		}
	}

	void set_position(int x,int y,int w,int h,int nx,int ny) {
		rect.x = x;
		rect.y = y;
		rect.w = w;
		rect.h = h;

		needleCenter.x = nx;
		needleCenter.y = ny;

		 // rpmNeedle.x = 474 - 75;  // Adjust X position (centered horizontally)
	  // rpmNeedle.y = 347 - 75;  // Adjust Y position (centered vertically)
		 // rpmNeedle.w = 150;  // Width of the needle image
		//rpmNeedle.h = 150;  // Height of the needle image

	}



};


#endif // !NEEDLE_H
