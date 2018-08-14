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
	String GetMessage();
private:

	String order;
	int paraOne;
	int paraTwo;
	int tab = 0;

	void messageIni();
	void analyseMessage(char ch);
	int buildNumber(int num, char ch);
	void executeOrder();
	void sendMessage(String Order, int para);
}

#endif // WIFISERIAL_H_INCLUDED
