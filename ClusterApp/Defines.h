#pragma once
#ifndef DEFINES_H
#define DEFINES_H

#include<string>

enum Gauges {
	SPEEDOMETER,
	RPMS,
	OIL_TEMP,
	WATER_TEMP,

};


//RPMS DEFINES

constexpr int RPM_X = 359;
constexpr int RPM_Y = 307;
constexpr int RPM_W = 80;
constexpr int RPM_H = 150;
constexpr int RPM_NX = 114; // -39
constexpr int RPM_NY = 35;


//! RPMS DEFINES


constexpr short NUM_OF_NEEDLES = 4;

constexpr const char NEEDLE_PATH[] = ".\\assets\\needle2.png";
constexpr const char INTERIOR_PATH[] = ".\\assets\\cluster4.png";
constexpr const char ROADR_PATH[] = ".\\assets\\road.jpeg";


#endif // !DEFINES_H
