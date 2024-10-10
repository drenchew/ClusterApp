#pragma once

#ifndef GEARBOX_H
#define GEARBOX_H




#include <cstdio>
#include <vector>
#include <array>
#include "BaseGauge.h"  // Assuming you have the RPM and Speedometer gauges already
#include <algorithm>    // For std::clamp

class Gearbox {
public:
    int currentGear = 1;
    const int maxGear = 6;

    // Gear ratios: each gear affects how much the RPMs contribute to speed
    std::array<float, 6> gearRatios = { 3.8f, 2.3f, 1.5f, 1.0f, 0.85f, 0.7f };

    // RPM range for the engine
    const int minRPM = 800;   // Idle RPM
    const int maxRPM = 8000;  // Redline RPM

    // Speed of the car (in km/h)
    float speed = 0.0f;

    // Current RPM of the engine
    float rpm = minRPM;

    Gearbox(std::shared_ptr<BaseGauge> rpmsGauge, std::shared_ptr<BaseGauge> speedometerGauge) :
        rpmsGauge(rpmsGauge), speedometerGauge(speedometerGauge) {}

    // Handle input for acceleration and braking
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
        // Increase RPM
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
        // Decrease RPM
        rpm -= 300.0f;

        // Prevent RPM from falling below idle RPM
        rpm = std::max(rpm, static_cast<float>(minRPM));

        // If RPM goes too low, shift down
        if (rpm < minRPM && currentGear > 1) {
            shift_down();
        }

        // Reduce speed based on lower RPM
        speed = rpm_to_speed(rpm, currentGear);
    }

    // Convert RPM to speed based on the current gear ratio
    float rpm_to_speed(float rpm, int gear) {
        // Calculate the speed as a proportion of the RPM and gear ratio
        // Multiply by 350 (max speed) to scale it correctly
        return (rpm / maxRPM) * gearRatios[gear - 1] * 350.0f;
    }

    // Shift up to the next gear
    void shift_up() {
        if (currentGear < maxGear) {
            currentGear++;
            printf("Shifting up to gear: %d\n", currentGear);
            // When shifting up, lower the RPM proportionally
            rpm = std::max(rpm / 1.5f, static_cast<float>(minRPM));
        }
    }

    // Shift down to the previous gear
    void shift_down() {
        if (currentGear > 1) {
            currentGear--;
            printf("Shifting down to gear: %d\n", currentGear);
            // When shifting down, increase the RPM proportionally
            rpm = std::min(rpm * 1.5f, static_cast<float>(maxRPM));
        }
    }

    // Update the gauges to reflect the current RPM and speed
    void update_gauges() {
        rpmsGauge->update_needle(static_cast<int>(rpm) - rpmsGauge->get_angle());  // Update RPM needle
        speedometerGauge->update_needle(static_cast<int>(speed) - speedometerGauge->get_angle());  // Update Speed needle
        printf("Current speed: %.2f km/h, RPM: %.2f\n", speed, rpm);
    }

private:
    std::shared_ptr<BaseGauge> rpmsGauge;
    std::shared_ptr<BaseGauge> speedometerGauge;
};


#endif // !GEARBOX_H