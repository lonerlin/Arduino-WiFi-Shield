from clientsocket import *

class Arduino:
    def __init__(self,ip,port):
        self.ip=ip
        self.port=port
        self.arduino=ClientSocket(ip,port,single_use=False)
    def digitalWrite(self,pin,value):
        self.arduino.send("H,dw, " + str(pin) + ","+ str(value) + ", ")
        return None
    def digitalRead(self,pin):
        return self.arduino.send("H,dr," + str(pin) + ",0,").decode('utf-8').split(',')[3]
    def analogWrite(self,pin,value):
        self.arduino.send("H,aw, " + str(pin) + "," + str(value) + ", ")
    def analogRead(self,pin):
        value= self.arduino.send("H,ar," + str(pin) + ",0,").decode('utf-8').split(',')
        return  value[3]
