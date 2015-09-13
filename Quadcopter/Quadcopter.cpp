#include "stdafx.h" //comment if not using visual studio
#include <iostream>
#include <string>
#include "Quadcopter.h"

//temporary get definitions using stdin
int8_t getPitch() {
	int pitch;
	std::cin >> pitch;
	std::cout << "Pitch entered: " << (int)(int8_t)pitch << std::endl;
	return (int8_t)pitch;
}

int8_t getRoll() {
	int roll;
	std::cin >> roll;
	std::cout << "Roll entered: " << (int)(int8_t)roll << std::endl;
	return (int8_t)roll;
}

uint8_t getHeight() {
	int height;
	std::cin >> height;
	std::cout << "Height entered: " << (int)(uint8_t)height << std::endl;
	return (uint8_t)height;
}

void setFR(uint8_t thrust) {
	std::cout << "FR is " << (int)thrust << std::endl;
}

void setFL(uint8_t thrust) {
	std::cout << "FL is " << (int)thrust << std::endl;
}

void setBR(uint8_t thrust) {
	std::cout << "BR is " << (int)thrust << std::endl;
}

void setBL(uint8_t thrust) {
	std::cout << "BL is " << (int)thrust << std::endl;
}