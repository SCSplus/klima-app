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


