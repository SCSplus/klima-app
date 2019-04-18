#include "windStrengthSensor.h"
#include <iostream>

using namespace std;


windStrengthSensor::windStrengthSensor()
{
}


windStrengthSensor::~windStrengthSensor()
{
}

int imp_per_sec = 0;
const int pinNumber = 29;

void windInterrupt(void) {
	imp_per_sec++;
	cout << imp_per_sec;
}

float windStrengthSensor::GetSensorData()
{
	wiringPiSetup();
	
	pinMode(pinNumber, INPUT);
	pullUpDnControl(pinNumber, PUD_UP);


	wiringPiISR(pinNumber, INT_EDGE_RISING, &windInterrupt);

	return imp_per_sec;

}

