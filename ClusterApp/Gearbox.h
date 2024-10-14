#pragma once

#ifndef GEARBOX_H
#define GEARBOX_H

#include <vector>
#include <array>
#include "BaseGauge.h" 
#include <algorithm>   

#include "Defines.h"

class Gearbox {
public:
    int currentGear = 1;
    const int maxGear = 6;

    const float shiftDownRpm = 3000;

    // Gear ratios
   // std::array<float, 6> gearRatios = { 0.3f, 0.5, 0.8f, 1.2f, 1.4f, 0.07f };
    std::array<float, 6> gearRatios = { 0.3f, 0.5, 0.8f, 1.2f, 1.1f, 1.7f };

    ISpeedometer* ispeedometer = NULL;
   

    // RPM range for the engine
    const int MIN_RPMS = 800;   // Idle RPM
    const int MAX_RPMS = 8000;  // Redline RPM

   // float speed = 0.0f;


    float rpm = MIN_RPMS;

    Gearbox(std::shared_ptr<BaseGauge> rpmsGauge, std::shared_ptr<BaseGauge> speedometerGauge) :
        rpmsGauge(rpmsGauge), speedometerGauge(speedometerGauge)
    {
        ispeedometer = static_cast<Speedometer*>(speedometerGauge.get());

        for (auto& g : gearRatios)
        {
            g = g * 0.8;
        }
    }


    void handle_input(bool accelerate, bool brake) {

        

        printf("*---------------------------------*\n");
        if (accelerate) {
            accelerate_car();
        }
        if (brake) {
            decelerate_car();
        }

       // update_gauges();
    }

    void accelerate_car() {

        std::cout << "Accelerating\n";
       
        rpm += 150.0f;  // Simulate throttle input

        // If RPM exceeds max, shift up
        if (rpm > MAX_RPMS && currentGear < maxGear) {
            shift_up();
        }

        // Cap the RPM at max RPM
        rpm = std::min(rpm, static_cast<float>(MAX_RPMS));

        // Calculate speed based on gear ratio and RPM
        this->ispeedometer->set_speed(rpm_to_speed(rpm, currentGear));
    }

    void decelerate_car() {
        std::cout << "Braking\n";
        rpm -= 300.0f;


        rpm = std::max(rpm, static_cast<float>(MIN_RPMS));

           

        if (rpm < shiftDownRpm && currentGear > 1) {
            shift_down();
        }

        this->ispeedometer->set_speed(rpm_to_speed(rpm, currentGear));
        //speed = rpm_to_speed(rpm, currentGear);
    }


    float rpm_to_speed(float rpm, int gear) {

        if (rpm == MIN_RPMS) { return 0; }
        return (rpm / MAX_RPMS) * gearRatios[gear - 1] * 350.0f;
    }


    void shift_up() {
        if (currentGear < maxGear) {
            currentGear++;
            printf("Shifting up to gear: %d\n", currentGear);
            // When shifting up lower the RPM proportionally
            rpm = std::max(rpm / 1.5f, static_cast<float>(MIN_RPMS));
        }
    }


    void shift_down() {
        if (currentGear > 1) {
            currentGear--;
            printf("Shifting down to gear: %d\n", currentGear);
           
            rpm = std::min(rpm * 1.5f, float( (MAX_RPMS)));
        }
    }

 
    float get_rpms() {
        return this->rpm;
    }



private:
    std::shared_ptr<BaseGauge> rpmsGauge;
    std::shared_ptr<BaseGauge> speedometerGauge;
};


#endif // !GEARBOX_H