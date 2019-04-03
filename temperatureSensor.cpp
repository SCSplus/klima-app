#include "temperatureSensor.h"



temperatureSensor::temperatureSensor()
{
}


temperatureSensor::~temperatureSensor()
{
}

float temperatureSensor::GetSensorData()
{
    // I2C bus erstellen
    int file;

    char *bus = "/dev/i2c-1";
    if ((file = open(bus, O_RDWR)) < 0)
    {
        return NULL;
    }
    //sensor aufrufen , BME280 I2C adresse ist 0x76(136)
    ioctl(file, I2C_SLAVE, 0x76);

    //	24 byte aus dem register lesen (0X88)
    char reg[1] = { 0x88 };
    write(file, reg, 1);
    char b1[24] = { 0 };
    if (read(file, b1, 24) != 24)
    {
        return NULL;
    }

    // daten konvertieren
    // Temperaturkoeffizienten
    int dig_T1 = (b1[0] + b1[1] * 256);
    int dig_T2 = (b1[2] + b1[3] * 256);
    if (dig_T2 > 32767)
    {
        dig_T2 -= 65536;
    }
    int dig_T3 = (b1[4] + b1[5] * 256);
    if (dig_T3 > 32767)
    {
        dig_T3 -= 65536;
    }

    // Druckkoeffizienten
    int dig_P1 = (b1[6] + b1[7] * 256);
    int dig_P2 = (b1[8] + b1[9] * 256);
    if (dig_P2 > 32767)
    {
        dig_P2 -= 65536;
    }
    int dig_P3 = (b1[10] + b1[11] * 256);
    if (dig_P3 > 32767)
    {
        dig_P3 -= 65536;
    }
    int dig_P4 = (b1[12] + b1[13] * 256);
    if (dig_P4 > 32767)
    {
        dig_P4 -= 65536;
    }
    int dig_P5 = (b1[14] + b1[15] * 256);
    if (dig_P5 > 32767)
    {
        dig_P5 -= 65536;
    }
    int dig_P6 = (b1[16] + b1[17] * 256);
    if (dig_P6 > 32767)
    {
        dig_P6 -= 65536;
    }
    int dig_P7 = (b1[18] + b1[19] * 256);
    if (dig_P7 > 32767)
    {
        dig_P7 -= 65536;
    }
    int dig_P8 = (b1[20] + b1[21] * 256);
    if (dig_P8 > 32767)
    {
        dig_P8 -= 65536;
    }
    int dig_P9 = (b1[22] + b1[23] * 256);
    if (dig_P9 > 32767)
    {
        dig_P9 -= 65536;
    }

    // Liest 1 Byte Daten aus dem Register (0xA1)
    reg[0] = 0xA1;
    write(file, reg, 1);
    char data[8] = { 0 };
    read(file, data, 1);
    int dig_H1 = data[0];

    // Liest 7 Byte Daten aus dem Register (0xE1)
    reg[0] = 0xE1;
    write(file, reg, 1);
    read(file, b1, 7);

    // daten konvertieren
    // Feuchtigkeitskoeffizienten
    int dig_H2 = (b1[0] + b1[1] * 256);
    if (dig_H2 > 32767)
    {
        dig_H2 -= 65536;
    }
    int dig_H3 = b1[2] & 0xFF;
    int dig_H4 = (b1[3] * 16 + (b1[4] & 0xF));
    if (dig_H4 > 32767)
    {
        dig_H4 -= 65536;
    }
    int dig_H5 = (b1[4] / 16) + (b1[5] * 16);
    if (dig_H5 > 32767)
    {
        dig_H5 -= 65536;
    }
    int dig_H6 = b1[6];
    if (dig_H6 > 127)
    {
        dig_H6 -= 256;
    }

    // Kontrollfeuchtigkeitsregister ausw�hlen (0xF2)
    // Luftfeuchtigkeit �ber Abtastrate = 1 (0x01)
    char config[2] = { 0 };
    config[0] = 0xF2;
    config[1] = 0x01;
    write(file, config, 2);
    // Kontrollmessregister ausw�hlen (0xF4)
    // Normalmodus, Temperatur und Druck �ber Abtastrate = 1 (0x27)
    config[0] = 0xF4;
    config[1] = 0x27;
    write(file, config, 2);
    // Konfigurationsregister ausw�hlen (0xF5)
    // Standby Zeit = 1000 ms (0xA0)
    config[0] = 0xF5;
    config[1] = 0xA0;
    write(file, config, 2);

    // 8 Byte Daten aus dem Register lesen (0xF7)
    // Druck MSB1, Druck MSB, Druck LSB, Temp MSB1, Temp MSB, Temp LSB, Feuchte LSB, Feuchte MSB
    reg[0] = 0xF7;
    write(file, reg, 1);
    read(file, data, 8);

    // Wandeln  Druck- und Temperaturdaten in 19 Bit um
    long adc_p = ((long)(data[0] * 65536 + ((long)(data[1] * 256) + (long)(data[2] & 0xF0)))) / 16;
    long adc_t = ((long)(data[3] * 65536 + ((long)(data[4] * 256) + (long)(data[5] & 0xF0)))) / 16;
    // Konvertieren Sie die Feuchtedaten
    long adc_h = (data[6] * 256 + data[7]);

    // Berechnungen der Temperaturverschiebung
    float var1 = (((float)adc_t) / 16384.0 - ((float)dig_T1) / 1024.0) * ((float)dig_T2);
    float var2 = ((((float)adc_t) / 131072.0 - ((float)dig_T1) / 8192.0) *
        (((float)adc_t) / 131072.0 - ((float)dig_T1) / 8192.0)) * ((float)dig_T3);
    float t_fine = (long)(var1 + var2);
    float cTemp = (var1 + var2) / 5120.0;

    return cTemp;
}
