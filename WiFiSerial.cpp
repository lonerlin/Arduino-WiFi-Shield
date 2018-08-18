#include "Arduino.h"
#include "WiFiSerial.h"

WiFiSerial::WiFiSerial()
{
	baud = 9600;
}
WiFiSerial::WiFiSerial(long Baud)
{
	baud = Baud;
}
void WiFiSerial::Begin()
{
	eventFun=nullptr;
	Serial.begin(baud);
}
void WiFiSerial::SerialEvent()
{

    if (isMessage)
    {
        messageIni();
        isMessage = false;
    }
	while (Serial.available())
	{

		analyseMessage(Serial.read());

	}

	executeOrder();
}
String WiFiSerial::GetMessage()
{
	return "H," + order + "," + paraOne + "," + paraTwo + ",";
}
//初始化消息
void WiFiSerial::messageIni()
{

	order = "";
	paraOne = 0;
	paraTwo = 0;
	tab = 0;
}
//生成消息
void WiFiSerial::analyseMessage(char ch)
{

	if (ch == ','){

		tab++;
	}
	else{

		switch (tab){
		case 1:
			order += ch;

			break;
		case 2:
			paraOne = buildNumber(paraOne, ch);
			break;
		case 3:
			paraTwo = buildNumber(paraTwo, ch);
			break;
		case 4:
			isMessage = true;

			break;
		default:
			break;
		}
	}
}
//由字符构建整数
int WiFiSerial::buildNumber(int num, char ch)
{
	if (ch >= '0' && ch <= '9')
	{
		num = num * 10 + (ch - '0');
	}
	return num;
}

void WiFiSerial::sendMessage(String Order, int ParaOne, int ParaTwo)
{
	String msg = "H," + Order + "," + ParaOne + "," + ParaTwo + ",";
	Serial.println(msg);
	Serial.flush();
}

void WiFiSerial::executeOrder()
{


	if (tab==4 && (!order.equals("")) && paraOne >= 0)
	{
        isMessage=true;
		if (order.equals("dr"))
		{
			pinMode(paraOne, INPUT);
			sendMessage(order, paraOne, digitalRead(paraOne));
			return;
		}
		if (order.equals("ar"))
		{
			//pinModer(paraOne, INPUT);
			sendMessage(order, paraOne, analogRead(paraOne));
			return;
		}
		if (order.equals("dw") && paraTwo >= 0)
		{
			pinMode(paraOne, OUTPUT);
			digitalWrite(paraOne,paraTwo);
			Serial.println();
			return;
		}
		if (order.equals("aw")  && paraTwo >= 0)
		{
			analogWrite(paraOne, paraTwo);
			Serial.println();
			return;
		}

		if(eventFun)
        {
            eventFun(order,paraOne,paraTwo);
            Serial.println();
        }

	}
	return;
}

void WiFiSerial::setMessageEvent(void (*msgEvent)(String Order,int ParaOne,int ParaTwo))
{
    eventFun=msgEvent;
}
