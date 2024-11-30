#pragma once
#ifndef BASE_GAUGE_H
#define BASE_GAUGE_H

#include "Needle.h"
#include "Defines.h"
#include <SDL.h>
#include <SDL_image.h>
#include <mutex>
#include<algorithm>

class BaseGauge {
public:
    std::mutex mtx; 

    BaseGauge() = delete;
    virtual ~BaseGauge() = default;

    BaseGauge(SDL_Window* window, SDL_Renderer* renderer, int start = 0, int end = 0) :
        lower_bound(start), upper_bound(end),
        needle(window, renderer) {
        needle.angle = lower_bound;  
    }

    virtual void render(SDL_Renderer* renderer) {
        SDL_RenderCopyEx(renderer, needle.get_texture(), NULL, &needle.get_rect(), needle.angle, needle.get_center_point(), SDL_FLIP_NONE);
    }

    SDL_Texture* get_texture() {
        return needle.get_texture();
    }

    int lower_bound;
    int upper_bound;
    int current_val = 0;

    virtual void test_needle(int val = 1) {
        needle.angle += val;
    }

    virtual void update_needle(float value, float min_val, float max_val) {
        std::lock_guard<std::mutex> lock(mtx); 
        float new_angle = map_value_to_angle(value, min_val, max_val);

        if (new_angle >= lower_bound && new_angle <= upper_bound) {
            needle.angle = static_cast<int>(new_angle);
        }
        printf("angle = %d\n", needle.angle);
    }

 
    float map_value_to_angle(float value, float min_val, float max_val) {
        value = std::clamp(value, min_val, max_val);

        return (lower_bound + (value - min_val) * (upper_bound - lower_bound) / (max_val - min_val) - 10)+3;
    }


    int get_angle() {
        return needle.get_angle();
    }

    virtual void kill() {
        SDL_DestroyTexture(needle.get_texture());
    }

   

    float value = 0;


    Needle needle;
};

#endif // !BASE_GAUGE_H
