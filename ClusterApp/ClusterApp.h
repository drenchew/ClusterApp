#pragma once
#ifndef CLUSTER_APP_H
#define CLUSTER_APP_H

#include <SDL.h>
#include <SDL_image.h>

#include <cstdio>
#include <stdexcept>
#include <array>
#include <vector>
#include <thread>
#include <memory>

#include "BaseGauge.h"
#include "FuelGauge.h"
#include "Rpms.h"
#include "OilTemperatureGauge.h"
#include "Speedometer.h"
#include "WaterTempGauge.h"
#include "OilLevelGauge.h"
#include "Gearbox.h"  // Include Gearbox header

using namespace std::chrono_literals;


class ClusterApp {
    SDL_Window* window;
    SDL_Renderer* renderer;

    SDL_Texture* _interior;
    SDL_Texture* _road;

    std::array<std::shared_ptr<BaseGauge>, NUM_OF_NEEDLES> gauges;
    bool running = false;

    std::unique_ptr<Gearbox> gearbox;  // Unique pointer to the gearbox

public:
    ClusterApp() : _interior(nullptr), window(nullptr), renderer(nullptr) {
        init();
        loop();
    }

    void init() {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            std::string errorMessage = "SDL could not initialize! SDL Error: " + std::string(SDL_GetError());
            throw std::runtime_error(errorMessage);  // Throw a runtime error with the message
        }

        if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
            printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        }

        window = SDL_CreateWindow("Car Cluster", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_W, WINDOW_H, SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

        _interior = IMG_LoadTexture(renderer, INTERIOR_PATH);
        _road = IMG_LoadTexture(renderer, ROADR_PATH);

        init_gauges();
        gearbox = std::make_unique<Gearbox>(gauges[Gauges::RPMS], gauges[Gauges::SPEEDOMETER]);
    }

    void init_gauges()
    {

        gauges[Gauges::FUEL_LEVEL] = std::make_shared<FuelGauge>(window, renderer, 320, 215);
        gauges[Gauges::RPMS] = std::make_shared<RPMGauge>(window, renderer, -30, 240);
        gauges[Gauges::OIL_TEMP] = std::make_shared<OilTempGauge>(window, renderer, 20, 130);
        gauges[Gauges::SPEEDOMETER] = std::make_shared<Speedometer>(window, renderer, -25, 137);
        gauges[Gauges::WATER_TEMP] = std::make_shared<WaterTempGauge>(window, renderer, 360, 220);
        gauges[Gauges::OIL_LEVEL] = std::make_shared<OilLevelGauge>(window, renderer, 98, 210);



        //RPM GAUGE 
        gauges[Gauges::RPMS]->needle.set_position(RPM_X, RPM_Y, RPM_H, RPM_W, RPM_NX, RPM_NY);
        gauges[Gauges::SPEEDOMETER]->needle.set_position(SPEEDOMETER_X, SPEEDOMETER_Y, SPEEDOMETER_H, SPEEDOMETER_W, SPEEDOMETER_NX, SPEEDOMETER_NY);
        gauges[Gauges::OIL_TEMP]->needle.set_position(OIL_TEMP_X, OIL_TEMP_Y, OIL_TEMP_H, OIL_TEMP_W, OIL_TEMP_NX, OIL_TEMP_NY);
        gauges[Gauges::WATER_TEMP]->needle.set_position(WATER_TEMP_X, WATER_TEMP_Y, WATER_TEMP_H, WATER_TEMP_W, WATER_TEMP_NX, WATER_TEMP_NY);
        gauges[Gauges::FUEL_LEVEL]->needle.set_position(FUEL_LEVEL_X, FUEL_LEVEL_Y, FUEL_LEVEL_H, FUEL_LEVEL_W, FUEL_LEVEL_NX, FUEL_LEVEL_NY);
        gauges[Gauges::OIL_LEVEL]->needle.set_position(OIL_LEVEL_X, OIL_LEVEL_Y, OIL_LEVEL_H, OIL_LEVEL_W, OIL_LEVEL_NX, OIL_LEVEL_NY);


    }

    void freeze_thread() {
        SDL_Delay(FREEZE_TIME);
    }

    void process_event(SDL_Event& event) {
        bool accelerate = false;
        bool brake = false;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }

            // Handle key down events
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                case SDLK_w:
                    accelerate = true;
                    std::cout << "Accelerating\n";
                    break;
                case SDLK_s:
                    brake = true;
                    std::cout << "Braking\n";

                    break;
                }
                gearbox->handle_input(accelerate, brake);
            }

            // Handle key up events
            if (event.type == SDL_KEYUP) {
                switch (event.key.keysym.sym) {
                case SDLK_w:
                    accelerate = false;
                    break;
                case SDLK_s:
                    brake = false;
                    break;
                }
            }
        }
    }


    void loop() {
        running = true;
        SDL_Event event;

        while (running) {
            process_event(event);

            static int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);

            update();
        }

        kill();
    }

    void kill() {
        for (auto& gauge : gauges) {
            gauge->kill();
        }

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
    }

    void update() {
        // Clear the screen
        SDL_RenderClear(renderer);

        freeze_thread();

        // Render the cluster background
        SDL_RenderCopy(renderer, _interior, NULL, NULL);

        for (auto& gauge : gauges) {
            gauge->render(renderer);
        }

        // Present the updated renderer
        SDL_RenderPresent(renderer);
    }
};

#endif // !CLUSTER_APP_H
