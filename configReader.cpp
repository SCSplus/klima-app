#include "configReader.h"

configReader::configReader()
{
    string line;
    ifstream myfile("config.ini");
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            if (line.rfind("URL = ", 0) == 0) {
                size_t pos = line.find("=");
                Url = line.substr(pos + 2);
                Url = Url.substr(0, Url.size() - 1);
            }

            if (line.rfind("TOKEN = ", 0) == 0) {
                size_t pos = line.find("=");
                Token = line.substr(pos + 2);
                Token = Token.substr(0, Token.size() - 1);
            }

            if (line.rfind("DEVICEID = ", 0) == 0) {
                size_t pos = line.find("=");
                DeviceId = line.substr(pos + 2);
                DeviceId = DeviceId.substr(0, DeviceId.size() - 1);
            }
        }
        myfile.close();
    }
}

configReader::~configReader()
{
}

string configReader::GetUrl()
{
    return Url;
}

string configReader::GetToken()
{
    return Token;
}

string configReader::GetDeviceId()
{
    return DeviceId;
}
