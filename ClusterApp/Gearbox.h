#pragma once

#ifndef GEARBOX_H
#define GEARBOX_H

#include <vector>
#include <array>
#include "BaseGauge.h" 
#include <algorithm>   

#include "Defines.h"
const int maxGear = 5;

class Gearbox {
public:
    int currentGear = 1;
 

    const float shiftDownRpm = 3000;

    // Gear ratios
   // std::array<float, 6> gearRatios = { 0.3f, 0.5, 0.8f, 1.2f, 1.4f, 0.07f };
    std::array<float, maxGear> gearRatios = { 0.3f, 0.5f, 0.8f, 1.2f,1.8f };

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

    void engine_brake() {
	//	std::cout << "Engine Braking\n";
		float currSpeed = ispeedometer->get_speed();
        if (currSpeed < 100.0f)
        {
            rpm -= 0.2f;
        }
        else {
			rpm -= 1;
        }

		rpm = std::max(rpm, static_cast<float>(MIN_RPMS));

        if (rpm < shiftDownRpm && currentGear > 1) {
            shift_down();
        }

		this->ispeedometer->set_speed(rpm_to_speed(rpm, currentGear));
    }

    void handle_input(bool accelerate, bool brake,bool enBrake) {

       // printf("*---------------------------------*\n");
        if (accelerate) {
            accelerate_car();
        }
        else if (enBrake) {
			engine_brake();
        }
        if (brake) {
            decelerate_car();
        }
    }


    void accelerate_car() {

       // std::cout << "Accelerating\n";
       
		 float curr_speed = ispeedometer->get_speed();
		 if (curr_speed <= 100.0f)
		 {
			 rpm += 40;
		 }
         else if (curr_speed >100 && curr_speed<=150)
		 {
			 rpm += 15;
		 }
         else if (curr_speed > 150.0f && curr_speed <= 200)
         {
			 rpm += 5;
         }
		 else {
			 rpm += 2.5;
		 }
   
        if (rpm > MAX_RPMS && currentGear < maxGear) {
            shift_up();
        }

        rpm = std::min(rpm, static_cast<float>(MAX_RPMS));

        this->ispeedometer->set_speed(rpm_to_speed(rpm, currentGear));
    }

    void decelerate_car() {
        
        
        if ((rpm - 15 < MIN_RPMS)) {
           
            return;
        }
      //  std::cout << "Braking\n";

		float currSpeed = ispeedometer->get_speed();
		if (currSpeed < 100.0f)
		{
            rpm -= 15;
		}
        else if(currSpeed > 200.0f)
		{
            rpm -= 5;
		}
		else {
			rpm -= 10;
		}




        rpm = std::max(rpm, static_cast<float>(MIN_RPMS));

           

        if (rpm < shiftDownRpm && currentGear > 1) {
            shift_down();
        }

        this->ispeedometer->set_speed(rpm_to_speed(rpm, currentGear));

    }


    float rpm_to_speed(float rpm, int gear) {

        if (rpm == MIN_RPMS) { return 0; }
        return (rpm / MAX_RPMS) * gearRatios[gear - 1] * 350.0f;
    }


    void shift_up() {
        if (currentGear < maxGear) {
            currentGear++;
            printf("Shifting up to gear: %d\n", currentGear);
           
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