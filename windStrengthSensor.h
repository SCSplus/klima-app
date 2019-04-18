#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

class windStrengthSensor
{
public:
    windStrengthSensor();
    ~windStrengthSensor();
    float GetSensorData();
};

int imp_per_sec = 0;
const int pinNumber = 29;

void windInterrupt(void) {
	imp_per_sec++;
	std::cout << imp_per_sec;
}

float windStrengthSensor::GetSensorData()
{
	wiringPiSetup();

	pinMode(pinNumber, INPUT);
	pullUpDnControl(pinNumber, PUD_UP);


	float actual_windspeed_msec = 0.0;


	wiringPiISR(pinNumber, INT_EDGE_RISING, &windInterrupt);

	std::cout << actual_windspeed_msec;
	return imp_per_sec;

}


