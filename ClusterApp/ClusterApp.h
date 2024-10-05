#pragma once
#ifndef CLUSTER_APP_H
#define CLUSTER_APP_H

#include <SDL.h>
#include <SDL_image.h>

#include <cstdio>
#include <stdexcept>
#include<array>

#include"BaseGauge.h"

constexpr int WINDOW_H = 520;
constexpr int WINDOW_W = 1024;

class ClusterApp {
	SDL_Window* window;
	SDL_Renderer* renderer;

	std::array<BaseGauge,> gauges;

	ClusterApp(): window(nullptr), renderer(nullptr){}

	void init() {
		if (SDL_Init(SDL_INIT_VIDEO) < 0) {
			std::string errorMessage = "SDL could not initialize! SDL Error: " + std::string(SDL_GetError());
			throw std::runtime_error(errorMessage); // Throw a runtime error with the message
		}

		if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
			printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
			//throw std::runtime_error(IMG_GetError());
		}


		SDL_Window* window = SDL_CreateWindow("Car Cluster", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_W, WINDOW_H, SDL_WINDOW_SHOWN);
		SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	}


	void clear() {

	}

	void update() {

	}

};


#endif // !CLUSTER_APP_H
