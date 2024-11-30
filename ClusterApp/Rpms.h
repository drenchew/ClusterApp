#pragma once

#ifndef RPMS_H
#define RPMS_H

#include "BaseGauge.h"

class RPMGauge : public BaseGauge {
public:
    float rpms = 0;
    RPMGauge(SDL_Window* window, SDL_Renderer* renderer, int start, int end) :
        BaseGauge(window, renderer, start, end) {}

    virtual void test_needle(int val = 1) override {
        if (needle.angle + val <= upper_bound) {
            needle.angle += 4; 
        }
        printf("Test Needle: angle = %d\n", needle.angle);
    }


    void update_needle(float rpm, float minRPM, float maxRPM) override final {
        std::lock_guard<std::mutex> lock(mtx);  


        float new_angle = map_value_to_angle(rpm, minRPM, maxRPM);

        if (new_angle >= lower_bound && new_angle <= upper_bound) {
            needle.angle = static_cast<int>(new_angle);
        }

     

    }
};

#endif // !RPMS_H
