#include "risingDampSensor.h"

#define	TRUE	            (1==1)
#define	FALSE	            (!TRUE)
#define CHAN_CONFIG_SINGLE  8
#define CHAN_CONFIG_DIFF    0

static int myFd;

risingDampSensor::risingDampSensor()
{
}


risingDampSensor::~risingDampSensor()
{
}

float risingDampSensor::GetSensorData()
{
    int loadSpi = FALSE;
    int analogChannel = 1;
    int spiChannel = 0;
    int channelConfig = CHAN_CONFIG_SINGLE;

    if (loadSpi == TRUE)
    {
        if (!loadSpiDriver())
        {
            return NULL;
        }
    }

    wiringPiSetup();
    if (!spiSetup(spiChannel))
    {
        return NULL;
    }

    
	if (analogChannel > 0)
	{
		int sensorwert = myAnalogRead(spiChannel, channelConfig, analogChannel - 1);

		if (sensorwert < 370)
		{
			return 100.0f;
		}
		if (sensorwert > 370 && sensorwert < 440)
		{
			return 90.0f;
		}
		if (sensorwert > 440 && sensorwert < 510)
		{
			return 80.0f;
		}
		if (sensorwert > 510 && sensorwert < 580)
		{
			return 70.0f;
		}
		if (sensorwert > 580 && sensorwert < 650)
		{
			return 60.0f;
		}
		if (sensorwert > 650 && sensorwert < 720)
		{
			return 50.0f;
		}
		if (sensorwert > 720 && sensorwert < 790)
		{
			return 40.0f;
		}
		if (sensorwert > 790 && sensorwert < 860)
		{
			return 30.0f;
		}
		if (sensorwert > 860 && sensorwert < 930)
		{
			return 20.0f;
		}
		if (sensorwert > 930 && sensorwert < 1000)
		{
			return 10.0f;
		}
		if (sensorwert > 1000)
		{
			return 0.0f;
		}
	}
   
    close(myFd);

    return 0.0f;
}


bool risingDampSensor::loadSpiDriver()
{
    if (system("gpio load spi") == -1)
    {
        return false;
    }

    return true;
}

bool risingDampSensor::spiSetup(int spiChannel)
{
    if ((myFd = wiringPiSPISetup(spiChannel, 1000000)) < 0)
    {
        return false;
    }

    return true;
}

int risingDampSensor::myAnalogRead(int spiChannel, int channelConfig, int analogChannel)
{
    if (analogChannel < 0 || analogChannel>7)
    {
        return -1;
    }

    unsigned char buffer[3] = { 1 }; // start bit
    buffer[1] = (channelConfig + analogChannel) << 4;
    wiringPiSPIDataRW(spiChannel, buffer, 3);
    int result = ((buffer[1] & 3) << 8) + buffer[2]; // get last 10 bits
    return result;
}