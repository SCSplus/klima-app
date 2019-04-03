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
        "\"Data\": {"+
        "\"ClimateStationId\": \"" + DeviceId +"\","+
            "\"DateOfEntry\" : \"" + DateTimeNow() + "\","+
            "\"Type\" : {"+
            "\"MeasurementTypeId\": \"\","+
                "\"Name\" : \"Luftdruck\""+
            "}, \"Unit\" : {"+
            "\"MeasurementUnitId\": \"\","+
                "\"Name\" : \"Pascal\","+
                "\"MeasurementType\" : {"+
                "\"MeasurementTypeId\": \"\","+
                    "\"Name\" : \"Luftdruck\""+
            "}}, \"Value\": \""+ strValue +" \",}}";

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
        "}}, \"Value\": \"" + strValue + " \",}}";

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
        "}}, \"Value\": \"" + strValue + " \",}}";

    PostData(data);
}

void webServiceDataStore::PostData(string data)
{
    CURL *curl;
    CURLcode res;
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    const char *cstr = data.c_str();

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "http://192.168.0.11:5000/scsplus/api/send");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, cstr);
        res = curl_easy_perform(curl);
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
