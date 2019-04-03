#pragma once

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class configReader
{
public:
    configReader();
    ~configReader();
    string GetUrl();
    string GetToken();
    string GetDeviceId();

private:
    string Url;
    string Token;
    string DeviceId;
};
