#include "stdafx.h" //comment if not using visual studio
#include <iostream>
#include <ctime>
#include "Quadcopter.h"

int main()
{
	static const double KP = 1.0;  //proportional constant
	static const double KI = 1.0;  //integral constant
	static const double KD = 1.0;  //derivative constant

	uint8_t setPointHeight = 100;   //keep steady at this height

	int8_t pitchErrors[4];
	double pitchIntegrals[4] = { 0,0,0,0 };
	int8_t pitchPreviousErrors[4] = { 0,0,0,0 };
	double pitchDerivatives[4];
	int8_t rollErrors[4];
	double rollIntegrals[4] = { 0,0,0,0 };
	int8_t rollPreviousErrors[4] = { 0,0,0,0 };
	double rollDerivatives[4];
	int16_t heightError;
	double heightIntegral = 0;
	int16_t heightPreviousError = 0;
	double heightDerivative;

	//start the time interval
	std::clock_t startTime = std::clock();

	while (1) {
		//get functions
		int8_t pitch = getPitch();
		int8_t roll = getRoll();
		uint8_t height = getHeight();

		/*
		error is setPoint - processValue
		individual errors for each motor for pitch and roll
		height error is the same for each motor
		positive error means higher thrust, negative error means lower thrust
		for pitch and roll, setPoint == 0
		using arrays: {FR, FL, BR, BL}
		*/
		
		pitchErrors[0] = pitch;     //FR
		pitchErrors[1] = pitch;     //FL
		pitchErrors[2] = -pitch;    //BR
		pitchErrors[3] = -pitch;    //BL

		rollErrors[0] = roll;       //FR
		rollErrors[1] = -roll;      //FL
		rollErrors[2] = roll;       //BR
		rollErrors[3] = -roll;      //BL
		
		heightError = setPointHeight - height;

		//set motors every second (adjustable)
		//WARNING: the temporary get definitions use stdin and typing the values in takes time, which causes problems
		if ((std::clock() - startTime) >= 1.0) {
			//refresh time interval
			double timeChange = (std::clock() - startTime) / (double) CLOCKS_PER_SEC;
			std::cout << "time change is " << timeChange << std::endl;
			startTime = std::clock();

			//calculate integrals and derivatives for each motor
			for (int i = 0; i < 4; i++) {
				pitchIntegrals[i] += pitchErrors[i] * timeChange;
				rollIntegrals[i] += rollErrors[i] * timeChange;
				if (timeChange > 0) {
					pitchDerivatives[i] = (pitchPreviousErrors[i] - pitchErrors[i]) / timeChange;
					rollDerivatives[i] = (rollPreviousErrors[i] - rollErrors[i]) / timeChange;
				}
			}
			heightIntegral += heightError * timeChange;
			if (timeChange > 0) {
				heightDerivative = (heightError - heightPreviousError) / timeChange;
			}

			//set functions
			for (int i = 0; i < 4; i++) {
				//added setPointHeight at the end assumes thrust of that value keeps the quadcopter at that height
				uint8_t thrust = (uint8_t)round(
					pitchErrors[i] * KP + pitchIntegrals[i] * KI + pitchDerivatives[i] * KD +
					rollErrors[i] * KP + rollIntegrals[i] * KI + rollDerivatives[i] * KD +
					heightError * KP + heightIntegral * KI + heightDerivative * KD) + setPointHeight;
				switch (i) {
				case 0:
					setFR(thrust);
					break;
				case 1:
					setFL(thrust);
					break;
				case 2:
					setBR(thrust);
					break;
				case 3:
					setBL(thrust);
				}

				pitchPreviousErrors[i] = pitchErrors[i];
				rollPreviousErrors[i] = rollErrors[i];
				heightPreviousError = heightError;
			}
		}
	}
    return 0;
}
