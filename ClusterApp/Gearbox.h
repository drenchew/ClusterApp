#pragma once

#ifndef GEARBOX_H
#define GEARBOX_H

#include <vector>
#include <array>
#include "BaseGauge.h" 
#include <algorithm>    

class Gearbox {
public:
    int currentGear = 1;
    const int maxGear = 6;

    // Gear ratios
    std::array<float, 6> gearRatios = { 0.2f, 2.3f, 1.5f, 1.0f, 0.85f, 0.7f };

    // RPM range for the engine
    const int minRPM = 800;   // Idle RPM
    const int maxRPM = 8000;  // Redline RPM

    float speed = 0.0f;


    float rpm = minRPM;

    Gearbox(std::shared_ptr<BaseGauge> rpmsGauge, std::shared_ptr<BaseGauge> speedometerGauge) :
        rpmsGauge(rpmsGauge), speedometerGauge(speedometerGauge) {}


    void handle_input(bool accelerate, bool brake) {
        if (accelerate) {
            accelerate_car();
        }
        if (brake) {
            decelerate_car();
        }

        update_gauges();
    }

    void accelerate_car() {
       
        rpm += 300.0f;  // Simulate throttle input

        // If RPM exceeds max, shift up
        if (rpm > maxRPM && currentGear < maxGear) {
            shift_up();
        }

        // Cap the RPM at max RPM
        rpm = std::min(rpm, static_cast<float>(maxRPM));

        // Calculate speed based on gear ratio and RPM
        speed = rpm_to_speed(rpm, currentGear);
    }

    void decelerate_car() {

        rpm -= 300.0f;


        rpm = std::max(rpm, static_cast<float>(minRPM));


        if (rpm < minRPM && currentGear > 1) {
            shift_down();
        }


        speed = rpm_to_speed(rpm, currentGear);
    }


    float rpm_to_speed(float rpm, int gear) {

        if (rpm == minRPM) { return 0; }
        return (rpm / maxRPM) * gearRatios[gear - 1] * 350.0f;
    }


    void shift_up() {
        if (currentGear < maxGear) {
            currentGear++;
            printf("Shifting up to gear: %d\n", currentGear);
            // When shifting up lower the RPM proportionally
            rpm = std::max(rpm / 1.5f, static_cast<float>(minRPM));
        }
    }


    void shift_down() {
        if (currentGear > 1) {
            currentGear--;
            printf("Shifting down to gear: %d\n", currentGear);
           
            rpm = std::min(rpm * 1.5f, static_cast<float>(maxRPM));
        }
    }

 
    void update_gauges() {
        rpmsGauge->update_needle(rpm, minRPM, maxRPM);  
        speedometerGauge->update_needle(speed, 0.0f, 350.0f); 
        printf("Current speed: %.2f km/h, RPM: %.2f\n", speed, rpm);
    }

private:
    std::shared_ptr<BaseGauge> rpmsGauge;
    std::shared_ptr<BaseGauge> speedometerGauge;
};


#endif // !GEARBOX_H