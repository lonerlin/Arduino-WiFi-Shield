#!usr/bin/python

import threading
import datetime
import time
from tkinter import *
from tkinter import filedialog
import tkinter.messagebox
import Arduino
import tablib

#IP地址和端口两个参数，需根据WIFI扩展板的实际IP和端口重新设置
arduino=Arduino.Arduino("192.168.1.200",5000)

id= 0
records=[]

def timerfun():
    global id
    now=time.asctime( time.localtime(time.time()) )
    if(vT.get()==1):
        temp=arduino.sendMessage('Temp',0,0)

        record=[id,'Temp',int(temp[3]),now]
        print(record)
        records.append(record)
        id +=1
    if(vH.get()==1):
        hum=arduino.sendMessage('Hum',0,0)

        record=[id,'Hum',int(hum[3]),now]
        print(record)
        records.append(record)
        id+=1
    global timer
    timer = threading.Timer(1, timerfun)
    timer.start()


def okButtonClick():
    records.clear()
    timer=threading.Timer(1,timerfun)
    timer.start()
def writeButtonClick():
    global timer
    if(timer):
        timer.cancel()
    filename=filedialog.asksaveasfilename(defaultextension='xls',filetypes=[('excel files', '.xls')])
    if(filename!="" and len(records)>0):
        headers = ("ID", "传感器", "传感器值", "写入时间")
        dataset = tablib.Dataset(*records, headers=headers)
        with open(filename, 'wb') as f:
            f.write(dataset.xls)
        tkinter.messagebox.showinfo("提示：","数据保存成功！")
    else:
        tkinter.messagebox.showerror("错误：","没有文件名，或者数据为空！")

tk=Tk()
tk.title('读取温湿度数据，输出到Excel文件')
vT = IntVar()
vH = IntVar()
tk.geometry('320x240')
f=Frame(tk,width=300,height=220)
f.place(x=10, y=10, anchor=NW)

cbTemp=Checkbutton(f,text="读取温度",anchor='w',variable=vT)
cbHum=Checkbutton(f,text="读取湿度",anchor='w',variable=vH)

label=Label(f,text="")
cbTemp.pack()
cbHum.pack()
label.pack()
Button(f,text="开始读取",command=okButtonClick,width=14).pack(pady=3)
Button(f,text="停止并写入Excel",command=writeButtonClick,width=14).pack(pady=3)




tk.mainloop()
