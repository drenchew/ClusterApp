#pragma once

#ifndef SPEEDOMETER_GAUGE_H
#define SPEEDOMETER_GAUGE_H

#include "BaseGauge.h"

class ISpeedometer {
protected:
    float speed = 0;
public:
    
    virtual float get_speed() const  = 0;
    virtual void set_speed(float val)  = 0;

    virtual ~ISpeedometer() = default;

};

class Speedometer : public ISpeedometer, public BaseGauge {
public:
    virtual float get_speed() const override final  {
        return speed;
    }

    virtual void set_speed(float val) override{
        this->speed = val;
    }

    Speedometer(SDL_Window* window, SDL_Renderer* renderer, int start, int end) :
        BaseGauge(window, renderer, start, end) {
    }

    
    virtual void update_needle(float speed, float min_val, float max_val) override {
        std::lock_guard<std::mutex> lock(mtx); 

      
            float new_angle = map_value_to_angle(speed, min_val, max_val);

            needle.angle = static_cast<int>(std::clamp(new_angle, static_cast<float>(lower_bound), static_cast<float>(upper_bound)));

         //   printf("Speedometer = %.3f, Angle = %d\n", speed, needle.angle);
        

    }

    //  For testing purposes
    virtual void test_needle(int val = 1) override {
        if (needle.angle <= upper_bound) {
            needle.angle += 1;
        }
    }
};




#endif // !SPEEDOMETER_GAUGE_H
