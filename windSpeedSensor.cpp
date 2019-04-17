#include "windSpeedSensor.h"
#include <iostream>


windSpeedSensor::windSpeedSensor()
{
}


windSpeedSensor::~windSpeedSensor()
{
}

float windSpeedSensor::GetSensorData()
{
	wiringPiSetup();

	const int pinNumber = 40;

	pinMode(pinNumber, INPUT);
	pullUpDnControl(pinNumber, PUD_UP);

	int imp_per_sec = 0;
	float actual_windspeed_msec = 0.0;
	
	void windInterrupt(void) {
		imp_per_sec++;
	}
	wiringPiISR(pinNumber, INT_EDGE_RISING, &windInterrupt);


	float windspeed = 0.0;
	std::cout << actual_windspeed_msec;
	return windspeed;
	
}
