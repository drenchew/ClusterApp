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
#include "Gearbox.h"

using namespace std::chrono_literals;


class ClusterApp {
    SDL_Window* window;
    SDL_Renderer* renderer;

    SDL_Texture* _interior;
    SDL_Texture* _road;

    std::array<std::shared_ptr<BaseGauge>, NUM_OF_NEEDLES> gauges;
    bool running = false;

    std::unique_ptr<Gearbox> gearbox; 

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
        gauges[Gauges::OIL_LEVEL] = std::make_shared<OilLevelGauge>(window, renderer, 210, 98);// 98 , 210



        gauges[Gauges::RPMS]->needle.set_position(RPM_X, RPM_Y, RPM_H, RPM_W, RPM_NX, RPM_NY);
        gauges[Gauges::SPEEDOMETER]->needle.set_position(SPEEDOMETER_X, SPEEDOMETER_Y, SPEEDOMETER_H, SPEEDOMETER_W, SPEEDOMETER_NX, SPEEDOMETER_NY);
        gauges[Gauges::OIL_TEMP]->needle.set_position(OIL_TEMP_X, OIL_TEMP_Y, OIL_TEMP_H, OIL_TEMP_W, OIL_TEMP_NX, OIL_TEMP_NY);
        gauges[Gauges::WATER_TEMP]->needle.set_position(WATER_TEMP_X, WATER_TEMP_Y, WATER_TEMP_H, WATER_TEMP_W, WATER_TEMP_NX, WATER_TEMP_NY);
        gauges[Gauges::FUEL_LEVEL]->needle.set_position(FUEL_LEVEL_X, FUEL_LEVEL_Y, FUEL_LEVEL_H, FUEL_LEVEL_W, FUEL_LEVEL_NX, FUEL_LEVEL_NY);
        gauges[Gauges::OIL_LEVEL]->needle.set_position(OIL_LEVEL_X, OIL_LEVEL_Y, OIL_LEVEL_H, OIL_LEVEL_W, OIL_LEVEL_NX, OIL_LEVEL_NY);

        std::thread fuel_thread(&ClusterApp::update_fuel_gauge, this, 2.0f, 0.0f, 350.0f);
        std::thread oilLevel_thread(&ClusterApp::update_oilLevel_gauge, this, 2.0f, 0.0f, 130);
        std::thread oilTemp_thread(&ClusterApp::update_oilLevel_gauge, this, 2.0f, 0.0f, 280);


        oilTemp_thread.detach();
        oilLevel_thread.detach();
        fuel_thread.detach();
       

    }

    void update_fuel_gauge(float value, float min_val, float max_val) {
     
            gauges[Gauges::FUEL_LEVEL]->update_needle(value, min_val, max_val);
    }

    void update_oilTemp_gauge(float value, float min_val, float max_val) {

        gauges[Gauges::WATER_TEMP]->update_needle(value, min_val, max_val);
    }

    void update_oilLevel_gauge(float value, float min_val, float max_val) {
        gauges[Gauges::OIL_LEVEL]->update_needle(value, min_val, max_val);
    }


    void freeze_thread() {
        SDL_Delay(FREEZE_TIME);
    }

    void process_event(SDL_Event& event) {
        static  bool accelerate = false;
        static bool brake = false;
        static bool engineBrake = false;
        

        while (SDL_PollEvent(&event)) {
            

            if (event.type == SDL_QUIT) {
                running = false;
            }

            // Handle key down events
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                case SDLK_w:
                    accelerate = true;
                    engineBrake = false;
                    break;
                case SDLK_s:
                    brake = true;
                    engineBrake = false;
                    break;

                }             

            }
           
            if (event.type == SDL_KEYUP) {
                switch (event.key.keysym.sym) {
                case SDLK_w:
					engineBrake = true;
                    accelerate = false;
                    break;
                case SDLK_s:
					engineBrake = true;
                    brake = false;
                    break;
                }

               
            }
         

        }

        gearbox->handle_input(accelerate, brake, engineBrake);
        float rpms = gearbox->get_rpms();

        gauges[Gauges::RPMS]->update_needle(gearbox->get_rpms(), MIN_RPMS, MAX_RPMS);
        gauges[Gauges::SPEEDOMETER]->update_needle(gearbox->ispeedometer->get_speed(), 0.0f, 350.0f);

    }


    void loop() {
        running = true;
        SDL_Event event;

        while (running) {
            process_event(event);

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

        SDL_RenderClear(renderer);

        freeze_thread();

        SDL_RenderCopy(renderer, this->_road, NULL, NULL);

        SDL_RenderCopy(renderer, _interior, NULL, NULL);
  

        for (auto& gauge : gauges) {
            gauge->render(renderer);
        }
      

        SDL_RenderPresent(renderer);
    }
};

#endif // !CLUSTER_APP_H
