#include <stdio.h>
#include <unistd.h>

#include "configReader.h"
#include "webServiceDataStore.h"

// sensors
#include "airPressureSensor.h"
#include "humiditySensor.h"
#include "temperatureSensor.h"
#include "luminositySensor.h"
#include "risingDampSensor.h"
#include "windStrengthSensor.h"

using namespace std;

int main()
{
	configReader *configs = new configReader();
    webServiceDataStore *dataStore = new webServiceDataStore(
       configs->GetDeviceId(), configs->GetUrl(), configs->GetToken());

    airPressureSensor *airPressure = new airPressureSensor();
    humiditySensor *humidity = new humiditySensor();
    temperatureSensor *temperature = new temperatureSensor();
    luminositySensor *luminosity = new luminositySensor();
    risingDampSensor *risingDamp = new risingDampSensor();
	windStrengthSensor *windStrength = new windStrengthSensor();

    while (true)
    {
        dataStore->PostHumidityData(15);
        dataStore->PostHumidityData(7);
        dataStore->PostHumidityData(25);

      float valueAirPressure = airPressure->GetSensorData();
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
        }

        float valueLuminosity = luminosity->GetSensorData();
        if (valueLuminosity != NULL)
        {
            dataStore->PostLumuinosityData(valueLuminosity);
        }

        float valueRisingDamp = risingDamp->GetSensorData();
        if (valueRisingDamp != NULL)
        {
            dataStore->PostRisingDampData(valueRisingDamp);
        } 
		
		float valueWindStrength = windStrength->GetSensorData();
        if (valueWindStrength != NULL)
        {
		
			dataStore->PostWindStrengthData(valueWindStrength);
        }

        sleep(600);
    }

}
