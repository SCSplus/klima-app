#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <wiringPiI2C.h>

#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>

class luminositySensor
{
public:
    luminositySensor();
    ~luminositySensor();
    float GetSensorData();
};

