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

void WiFiSerial:: SerialEvent()
{
    messageIni();
    while(Serial.available())
    {
        GetMessage(mySerial.read());
    }
}

//初始化消息
void WiFISerial:: messageIni()
{
  order="";
  paraOne=0;
  paraTwo=0;
  tab=0;
  }
 //生成消息
void WiFISerial::getMessage(char ch)
{
  if(ch==','){
    tab++;
    }else{
      switch(tab){
        case 1:
          order+=ch;
        case 2:
          paraOne=buildNumber(paraOne,ch);
          mySerial.println(paraOne);
        case 3:
          paraTwo=buildNumber(paraTwo,ch);
        default:
          break;
        }
      }

  }
  //由字符构建整数
int WiFISerial:: buildNumber(int num,char ch)
{
  if(ch>='0' && ch<='9')
  {
    num=num*10+(ch-'0');
    }
    return num;
  }

  void WiFISerial:: sendMessage(String Order,int paraOne,int ParaTow)
{
    String msg="H," + Order +"," + paraOne + "," + ParaTwo + ",";
    Serial.println(msg);
    Serial.flash();
  }
