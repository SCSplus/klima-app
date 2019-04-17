#include <stdio.h>
#include <unistd.h>

#include "configReader.h"
#include "webServiceDataStore.h"

// sensors
#include "airPressureSensor.h"
#include "humiditySensor.h"
#include "temperatureSensor.h"
#include "windSpeedSensor.h"

using namespace std;

int main()
{
    configReader *configs = new configReader();
    webServiceDataStore *dataStore = new webServiceDataStore(
       configs->GetDeviceId(), configs->GetUrl(), configs->GetToken());

    airPressureSensor *airPressure = new airPressureSensor();
    humiditySensor *humidity = new humiditySensor();
    temperatureSensor *temperature = new temperatureSensor();
    windSpeedSensor *windSpeed = new windSpeedSensor();

    while (true)
    {
        dataStore->PostHumidityData(15);
        dataStore->PostHumidityData(7);
        dataStore->PostHumidityData(25);

		float valueWindSpeed = windSpeed->GetSensorData();
			if (valueWindSpeed != NULL)
			{
				dataStore->PostHumidityData(valueWindSpeed);
			}

        /*float valueAirPressure = airPressure->GetSensorData();
        if (valueAirPressure != NULL)
        {
            dataStore->PostHumidityData(valueAirPressure);
        }

        float valueHumidity = humidity->GetSensorData();
        if (valueHumidity != NULL)
        {
            dataStore->PostHumidityData(valueHumidity);
        }

        float valueTemperature = temperature->GetSensorData();
        if (valueTemperature != NULL)
        {
            dataStore->PostHumidityData(valueTemperature);
        }*/

        //sleep(10);
    }

}
