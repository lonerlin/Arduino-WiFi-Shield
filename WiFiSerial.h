#ifndef WIFISERIAL_H_INCLUDED
#define WIFISERIAL_H_INCLUDED

#include "Arduino.h"

Class WiFiSerial
{
    public:
        String msg;
        WiFiSerial();
        WiFiSerial(int Baud);
        void SerialEvent();
    private:

        String order;
        int paraOne;
        int paraTwo;
        int tab=0;

        void messageIni();
        void getMessage(char ch);
        int buildNumber(int num,char ch);
        void sendMessage(String Order,int para);
}

#endif // WIFISERIAL_H_INCLUDED
