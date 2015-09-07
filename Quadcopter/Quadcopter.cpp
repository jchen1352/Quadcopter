#include "stdafx.h"
#include <iostream>
#include "Quadcopter.h"

int8_t getPitch() {
	int8_t pitch;
	std::cin >> pitch;
	return pitch;
}

int8_t getRoll() {
	int8_t roll;
	std::cin >> roll;
	return roll;
}

uint8_t getHeight() {
	uint8_t height;
	std::cin >> height;
	return height;
}

void setThrust(uint8_t& motor, uint8_t strength) {
	motor = strength;
}