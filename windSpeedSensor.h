#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
extern "C"{
#include <wiringPi.h>
}

class windSpeedSensor
{
public:
	windSpeedSensor();
	~windSpeedSensor();
	float GetSensorData();
};

