#include "webServiceDataStore.h"

webServiceDataStore::webServiceDataStore(string deviceid, string url, string token)
{
    DeviceId = deviceid;
    Url = url;
    Token = token;
}

webServiceDataStore::~webServiceDataStore()
{
}

void webServiceDataStore::PostAirPressureData(float value)
{
    string strValue = std::to_string(value);

    string data = "{\"DynamicToken\": \"" + Token + "\"," +
        "\"Data\": {" +
        "\"ClimateStationId\": \"" + DeviceId + "\"," +
        "\"DateOfEntry\" : \"" + DateTimeNow() + "\"," +
        "\"Type\" : {" +
        "\"MeasurementTypeId\": \"\"," +
        "\"Name\" : \"Luftdruck\"" +
        "}, \"Unit\" : {" +
        "\"MeasurementUnitId\": \"\"," +
        "\"Name\" : \"Pascal\"," +
        "\"MeasurementType\" : {" +
        "\"MeasurementTypeId\": \"\"," +
        "\"Name\" : \"Luftdruck\"" +
        "}}, \"Value\": \"" + strValue + " \"}}";

    PostData(data);
}

void webServiceDataStore::PostTemperatureData(float value)
{
    string strValue = std::to_string(value);

    string data = "{\"DynamicToken\": \"" + Token + "\"," +
        "\"Data\": {" +
        "\"ClimateStationId\": \"" + DeviceId + "\"," +
        "\"DateOfEntry\" : \"" + DateTimeNow() + "\"," +
        "\"Type\" : {" +
        "\"MeasurementTypeId\": \"\"," +
        "\"Name\" : \"Temperatur\"" +
        "}, \"Unit\" : {" +
        "\"MeasurementUnitId\": \"\"," +
        "\"Name\" : \"Celsius\"," +
        "\"MeasurementType\" : {" +
        "\"MeasurementTypeId\": \"\"," +
        "\"Name\" : \"Temperatur\"" +
        "}}, \"Value\": \"" + strValue + " \"}}";

    PostData(data);
}

void webServiceDataStore::PostHumidityData(float value)
{
    string strValue = std::to_string(value);
    string data = "{\"DynamicToken\": \"" + Token + "\"," +
        "\"Data\": {" +
        "\"ClimateStationId\": \"" + DeviceId + "\"," +
        "\"DateOfEntry\" : \"" + DateTimeNow() + "\"," +
        "\"Type\" : {" +
        "\"MeasurementTypeId\": \"\"," +
        "\"Name\" : \"Luftfeuchtigkeit\"" +
        "}, \"Unit\" : {" +
        "\"MeasurementUnitId\": \"\"," +
        "\"Name\" : \"Prozent\"," +
        "\"MeasurementType\" : {" +
        "\"MeasurementTypeId\": \"\"," +
        "\"Name\" : \"Luftfeuchtigkeit\"" +
        "}}, \"Value\": \"" + strValue + " \"}}";

    PostData(data);
}

void webServiceDataStore::PostLumuinosityData(float value)
{
    string strValue = std::to_string(value);
    string data = "{\"DynamicToken\": \"" + Token + "\"," +
        "\"Data\": {" +
        "\"ClimateStationId\": \"" + DeviceId + "\"," +
        "\"DateOfEntry\" : \"" + DateTimeNow() + "\"," +
        "\"Type\" : {" +
        "\"MeasurementTypeId\": \"\"," +
        "\"Name\" : \"Helligkeit\"" +
        "}, \"Unit\" : {" +
        "\"MeasurementUnitId\": \"\"," +
        "\"Name\" : \"Lumen\"," +
        "\"MeasurementType\" : {" +
        "\"MeasurementTypeId\": \"\"," +
        "\"Name\" : \"Helligkeit\"" +
        "}}, \"Value\": \"" + strValue + " \"}}";

    PostData(data);
}

void webServiceDataStore::PostRisingDampData(float value)
{
    string strValue = std::to_string(value);

    string data = "{\"DynamicToken\": \"" + Token + "\"," +
        "\"Data\": {" +
        "\"ClimateStationId\": \"" + DeviceId + "\"," +
        "\"DateOfEntry\" : \"" + DateTimeNow() + "\"," +
        "\"Type\" : {" +
        "\"MeasurementTypeId\": \"\"," +
        "\"Name\" : \"Bodenfeuchtigkeit\"" +
        "}, \"Unit\" : {" +
        "\"MeasurementUnitId\": \"\"," +
        "\"Name\" : \"Einheit\"," +
        "\"MeasurementType\" : {" +
        "\"MeasurementTypeId\": \"\"," +
        "\"Name\" : \"Bodenfeuchtigkeit\"" +
        "}}, \"Value\": \"" + strValue + " \"}}";

    PostData(data);
}


void webServiceDataStore::PostWindStrengthData(float value)
{
    string strValue = std::to_string(value);

    string data = "{\"DynamicToken\": \"" + Token + "\"," +
        "\"Data\": {" +
        "\"ClimateStationId\": \"" + DeviceId + "\"," +
        "\"DateOfEntry\" : \"" + DateTimeNow() + "\"," +
        "\"Type\" : {" +
        "\"MeasurementTypeId\": \"\"," +
        "\"Name\" : \"Windgeschwindigkeit\"" +
        "}, \"Unit\" : {" +
        "\"MeasurementUnitId\": \"\"," +
        "\"Name\" : \"kmh\"," +
        "\"MeasurementType\" : {" +
        "\"MeasurementTypeId\": \"\"," +
        "\"Name\" : \"Windgeschwindigkeit\"" +
        "}}, \"Value\": \"" + strValue + " \"}}";

    PostData(data);
}


void webServiceDataStore::PostData(string data)
{
    CURL *curl;
    CURLcode res;
    curl_global_init(CURL_GLOBAL_ALL);

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Accept: application/json");
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, "charsets: utf-8");

    curl = curl_easy_init();

    const char *cstr = data.c_str();

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "http://192.168.0.11:5000/api/MeasurementData/Create");
        curl_easy_setopt(curl, CURLOPT_POST, 1);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, cstr);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, data.length());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");

        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(res));
        }

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    return;
}

string webServiceDataStore::DateTimeNow()
{
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
    std::string str(buffer);

    return str;
}
