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

    // ToDo: Welcher Wert muss zurückgegeben werden?
    if (analogChannel > 0)
    {
        // bodenfeuchtigkeit ausgabe 1000 ist trocken ab 300 ist nass
        /*printf("Bodenfeuchtigkeit (CE%d,%s): analogChannel %d = %d\n", spiChannel, (channelConfig == CHAN_CONFIG_SINGLE)
            ? "single-ended" : "differential", analogChannel, myAnalogRead(spiChannel, channelConfig, analogChannel - 1));*/
    }
    else
    {
        int i;
        for (i = 0; i < 8; i++)
        {
            /*printf("MCP3008(CE%d,%s): analogChannel %d = %d\n", spiChannel, (channelConfig == CHAN_CONFIG_SINGLE)
                ? "single-ended" : "differential", i + 1, myAnalogRead(spiChannel, channelConfig, i));*/
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