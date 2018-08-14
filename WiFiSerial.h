#ifndef WIFISERIAL_H_INCLUDED
#define WIFISERIAL_H_INCLUDED

#include "Arduino.h"

class WiFiSerial
{
public:
	String msg;
	WiFiSerial();
	WiFiSerial(long Baud);
	void SerialEvent();
	String GetMessage();
	void Begin();
private:

	bool isMessage=true;
	long baud;
	String order;
	int paraOne;
	int paraTwo;
	int tab = 0;

	void messageIni();
	void analyseMessage(char ch);
	int buildNumber(int num, char ch);
	void executeOrder();
	void sendMessage(String Order, int ParaOne,int ParaTwo);
};

#endif // WIFISERIAL_H_INCLUDED
