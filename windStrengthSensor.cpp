#include "windStrengthSensor.h"
#include <iostream>
#include <ctime>
#include <cmath>

using namespace std;


windStrengthSensor::windStrengthSensor()
{
}


windStrengthSensor::~windStrengthSensor()
{
}

clock_t start;
double duration;
int imp_per_sec = 0;
int result = 0;
const int pinNumber = 29;

void windInterrupt(void) {
	imp_per_sec++;
	duration = difftime(time(0),start);
	if (duration > 0.005) {
		pinMode(pinNumber, INPUT);
		pullUpDnControl(pinNumber,PUD_OFF);
	}
}


float windStrengthSensor::GetSensorData()
{
	wiringPiSetup();
	
	pinMode(pinNumber, INPUT);
	pullUpDnControl(pinNumber, PUD_UP);

	start = time(0);
	wiringPiISR(pinNumber, INT_EDGE_RISING, &windInterrupt);
	//result = imp_per_sec;
	result = 8e-9 * pow(imp_per_sec, 5) - 2e-6 * pow(imp_per_sec, 4) + 2e-4 * pow(imp_per_sec, 3) - 7.3e-3 * pow(imp_per_sec, 2) + 0.4503 * imp_per_sec + 0.11;
	imp_per_sec = 0;
	return result;

}

