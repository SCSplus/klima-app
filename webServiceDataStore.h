#pragma once
#include <stdio.h>
#include <ctime>
#include <curl/curl.h>
#include <iostream>

using namespace std;

class webServiceDataStore
{
public:
    webServiceDataStore(string deviceid, string url, string token);
    ~webServiceDataStore();
    void PostAirPressureData(float value);
    void PostTemperatureData(float value);
    void PostHumidityData(float value);
    void PostLumuinosityData(float value);
    void PostRisingDampData(float value);
    void PostWindStrengthData(float value);

private:
    void PostData(string data);
    string Url;
    string Token;
    string DeviceId;
    string DateTimeNow();
};
