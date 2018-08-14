#include "Arduino.h"
#include "WiFiSerial.h"

WiFiSerial::WiFiSerial()
{
	Serial.begin(9600);
}
WiFiSerial::WiFiSerial(int Baud)
{
	Serial.begin(Baud);
}

void WiFiSerial::SerialEvent()
{
	messageIni();
	while (Serial.available())
	{
		GetMessage(mySerial.read());
	}
	executeOrder();
}
String WiFiSerial::GetMessage()
{
	return "H," + order + "," + paraOne + "," + paraTwo + ",";
}
//初始化消息
void WiFISerial::messageIni()
{
	order = "";
	paraOne = 0;
	paraTwo = 0;
	tab = 0;
}
//生成消息
void WiFISerial::analyseMessage(char ch)
{
	if (ch == ','){
		tab++;
	}
	else{
		switch (tab){
		case 1:
			order += ch;
		case 2:
			paraOne = buildNumber(paraOne, ch);
			mySerial.println(paraOne);
		case 3:
			paraTwo = buildNumber(paraTwo, ch);
		default:
			break;
		}
	}
}
//由字符构建整数
int WiFISerial::buildNumber(int num, char ch)
{
	if (ch >= '0' && ch <= '9')
	{
		num = num * 10 + (ch - '0');
	}
	return num;
}

void WiFiSerial::sendMessage(String Order, int ParaOne, int ParaTow)
{
	String msg = "H," + Order + "," + ParaOne + "," + ParaTwo + ",";
	Serial.println(msg);
	Serial.flash();
}

void WiFiSerial::executeOrder()
{
	if ((strcmp(order, "") != 0) && paraOne>=0 )
	{
		if (strcmp(order, "dr") == 0)
		{
			pinMode(paraOne, INPUT);
			sendMessage(order, paraOne, digitalRead(paraOne));
			return;
		}
		if (strcmp(order, "ar") == 0)
		{
			//pinModer(paraOne, INPUT);
			sendMessage(order, paraOne, analogRead(paraOne));
			return;
		}
		if (strcmp(order, "dw") == 0 && paraTwo >= 0)
		{
			pinMode(paraOne, OUTPUT);
			digitalWrite(paraOne,paraTwo);
			return;
		}
		if (strcmp(order, "aw") == 0 && paraTwo >= 0)
		{
			analogWrite(paraOne, paraTwo);
			return;
		}
	}
	return;
}