#pragma once

#ifndef SPEEDOMETER_GAUGE_H
#define SPEEDOMETER_GAUGE_H

#include "BaseGauge.h"

class Speedometer : public BaseGauge {
public:
    Speedometer(SDL_Window* window, SDL_Renderer* renderer, int start, int end) :
        BaseGauge(window, renderer, start, end) {
    }

    
    virtual void update_needle(float speed, float min_val, float max_val) override {
        std::lock_guard<std::mutex> lock(mtx); 

      
        float new_angle = map_value_to_angle(speed, min_val, max_val);

       
        if (new_angle < lower_bound) {
            needle.angle = lower_bound; 
        }
        else if (new_angle > upper_bound) {
            needle.angle = upper_bound;
        }
        else {
            needle.angle = static_cast<int>(new_angle);
        }

        printf("Updated Speedometer Needle: angle = %d\n", needle.angle);
    }

    //  For testing purposes
    virtual void test_needle(int val = 1) override {
        if (needle.angle <= upper_bound) {
            needle.angle += 1;
        }
    }
};

#endif // !SPEEDOMETER_GAUGE_H
