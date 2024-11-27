#pragma once
#ifndef DEFINES_H
#define DEFINES_H

#include <string>
#include<unordered_map>

std::unordered_map<int,int> RpmToKmhRatio;

enum Gauges {
    SPEEDOMETER,
    RPMS,
    OIL_TEMP,
    WATER_TEMP,
    OIL_LEVEL,
    FUEL_LEVEL
};

// game updating rate
#define FREEZE_TIME 5


constexpr int WINDOW_H = 520;
constexpr int WINDOW_W = 1024;

// RPMS Gauge
// Mouse Position: (470, 342)
constexpr int MIN_RPMS = 800;   // Idle RPM
constexpr int MAX_RPMS = 8000;  // Redline RPM

constexpr int RPM_X = 359;
constexpr int RPM_Y = 307;
constexpr int RPM_W = 80;
constexpr int RPM_H = 150;
constexpr int RPM_NX = 114; // Offset from needle center point in X-axis
constexpr int RPM_NY = 35;  // Offset from needle center point in Y-axis

// SPEEDOMETER Gauge
// Mouse Position: (290, 379)
constexpr int SPEEDOMETER_X = 176 +30;  // 290 - 114 (Offset similar to RPM)
constexpr int SPEEDOMETER_Y = 344 + 20;  // 379 - 35 (Offset similar to RPM)
constexpr int SPEEDOMETER_W = 60; // -20 
constexpr int SPEEDOMETER_H = 120; // -30
constexpr int SPEEDOMETER_NX = 90; // Same offset as RPM in X-axis  //100
constexpr int SPEEDOMETER_NY = 30;  // Same offset as RPM in Y-axis  //30




// OIL_TEMP Gauge
// Mouse Position: (155, 408)
constexpr int OIL_TEMP_X = 155 -55;  // Offset in X-axis
constexpr int OIL_TEMP_Y = 408 - 20;   // Offset in Y-axis
constexpr int OIL_TEMP_W = 55;
constexpr int OIL_TEMP_H = 65;
constexpr int OIL_TEMP_NX = 45;       // X-offset for the needle's center point
constexpr int OIL_TEMP_NY = 30;        // Y-offset for the needle's center point

// WATER_TEMP Gauge
// Mouse Position: (159, 465)
constexpr int WATER_TEMP_X = 159 - 40; // Offset in X-axis
constexpr int WATER_TEMP_Y = 465 - 25;  // Offset in Y-axis
constexpr int WATER_TEMP_W = 55;
constexpr int WATER_TEMP_H = 65;
constexpr int WATER_TEMP_NX = 45;      // X-offset for the needle's center point
constexpr int WATER_TEMP_NY = 30;       // Y-offset for the needle's center point

// FUEL_LEVEL Gauge
// Mouse Position: (779, 462)
constexpr int FUEL_LEVEL_X = 779 -40; // Estimated similar offset as other gauges
constexpr int FUEL_LEVEL_Y = 462 - 25;  // Estimated similar offset as other gauges
constexpr int FUEL_LEVEL_W = 55;        // Same width as RPM and Speedometer
constexpr int FUEL_LEVEL_H = 65;       // Same height as RPM and Speedometer
constexpr int FUEL_LEVEL_NX = 45;      // Offset for the needle's center point
constexpr int FUEL_LEVEL_NY = 30;       // Offset for the needle's center point

// OIL_LEVEL Gauge
// Mouse Position: (792, 412)
constexpr int OIL_LEVEL_X = 792 - 45;  // Estimated similar offset as other gauges
constexpr int OIL_LEVEL_Y = 412 - 20;   // Estimated similar offset as other gauges
constexpr int OIL_LEVEL_W = 55;         // Same width as RPM and Speedometer
constexpr int OIL_LEVEL_H = 65;        // Same height as RPM and Speedometer
constexpr int OIL_LEVEL_NX = 45;       // Offset for the needle's center point
constexpr int OIL_LEVEL_NY = 30;        // Offset for the needle's center point

// Number of needles
constexpr short NUM_OF_NEEDLES = 6;

// File paths
constexpr const char NEEDLE_PATH[] = ".\\assets\\needle2.png";
constexpr const char INTERIOR_PATH[] = ".\\assets\\cluster4.png";
constexpr const char ROADR_PATH[] = ".\\assets\\road5.png";

#endif // !DEFINES_H
