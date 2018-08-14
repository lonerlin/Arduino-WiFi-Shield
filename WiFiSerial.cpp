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
//��ʼ����Ϣ
void WiFiSerial::messageIni()
{
	Serial.println("Ini");
	order = "";
	paraOne = 0;
	paraTwo = 0;
	tab = 0;
}
//������Ϣ
void WiFiSerial::analyseMessage(char ch)
{
	Serial.println(ch);
	if (ch == ','){
		Serial.println("douhao");
		tab++;
	}
	else{
		Serial.println(tab);
		switch (tab){
		case 1:
			order += ch;
			Serial.print("order:");
			Serial.println(order);
			break;
		case 2:
			paraOne = buildNumber(paraOne, ch);
			//mySerial.println(paraOne);
			break;
		case 3:
			paraTwo = buildNumber(paraTwo, ch);
			break;
		case 4:
			isMessage = true;
			Serial.println("isMessage=True");
			break;
		default:
			break;
		}
	}
}
//���ַ���������
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
		
		if (order.equals("dr"))
		{
			pinMode(paraOne, INPUT);
			sendMessage(order, paraOne, digitalRead(paraOne));
			isMessage = True;
			return;
		}
		if (order.equals("ar"))
		{
			//pinModer(paraOne, INPUT);
			sendMessage(order, paraOne, analogRead(paraOne));
			isMessage = True;
			return;
		}
		if (order.equals("dw") && paraTwo >= 0)
		{
			pinMode(paraOne, OUTPUT);
			digitalWrite(paraOne,paraTwo);
			return;
		}
		if (order.equals("aw")  && paraTwo >= 0)
		{
			analogWrite(paraOne, paraTwo);
			return;
		}
	}
	return;
}