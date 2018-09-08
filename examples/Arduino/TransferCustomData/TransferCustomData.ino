#include <dht11.h>
#include <WiFiSerial.h>

WiFiSerial wSerial(9600);
dht11 DHT11;
#define DHT11PIN 2

void MessageEvent(String order,int paraOne,int paraTwo)
{
    digitalWrite(5,1);
    if(order=="Temp")
    {
       int chk = DHT11.read(DHT11PIN);
      wSerial.sendMessage("Temp",0,DHT11.temperature);
    }
    if(order=="Hum")
    {
       int chk = DHT11.read(DHT11PIN);
      wSerial.sendMessage("Hum",0, DHT11.humidity);
    }
}

void setup()
{
  wSerial.Begin();
  wSerial.setMessageEvent(MessageEvent);
}

void loop()
{
   wSerial.SerialEvent();
  //Serial.print(dht11_pin_2.getTemperature());
  //Serial.println();
}


