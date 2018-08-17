from clientsocket import *
from Arduino import *

arduino=Arduino("192.168.1.101",5000)
print (arduino.analogRead(0))