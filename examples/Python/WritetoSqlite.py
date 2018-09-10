#!usr/bin/python

import threading
import datetime
import time
from tkinter import *
from tkinter import filedialog
import tkinter.messagebox
import Arduino
import tablib
import os
import sqlite3
from  tkinter import ttk  #导入内部包



id= 0
records=[]

DBPath = 'DB.db'
conn = sqlite3.connect(DBPath)
cu= conn.cursor()

#IP地址和端口两个参数，需根据WIFI扩展板的实际IP和端口重新设置
arduino=Arduino.Arduino("192.168.1.200",5000)


def timerfun():
    global id
    now=time.asctime( time.localtime(time.time()) )
    if(vT.get()==1):
        temp=arduino.sendMessage('Temp',0,0)

        record=['Temp',int(temp[3]),now]
        print(record)
        records.append(record)
        id +=1
    if(vH.get()==1):
        hum=arduino.sendMessage('Hum',0,0)

        record=['Hum',int(hum[3]),now]
        print(record)
        records.append(record)
        id+=1
    if(id%20==0):
        insertData(record)
        id=0
        record.clear()
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
        dataset = tablib.Dataset(*getData(500), headers=headers)
        with open(filename, 'wb') as f:
            f.write(dataset.xls)
        tkinter.messagebox.showinfo("提示：","数据保存成功！")
    else:
        tkinter.messagebox.showerror("错误：","没有文件名，或者数据为空！")

def selectTopClick():
    updateTreeView(100)


def dbIni():
    sql="select count(*) from sqlite_master where type='table' and name='dhtinfo'"
    result=conn.execute(sql)
    if (result==0):
        create_table_sql = '''CREATE TABLE `devices` (
                                  `id`   INTEGER PRIMARY KEY AUTOINCREMENT,
                                  `deviceName` TEXT,
                                  `value` int(4)  ,
                                   `updateTime` TIMESTAMP ,
                                )'''
        conn.execute(create_table_sql)

def insertData(data):
    insert_Sql=''' insert into dhtinfo values (deviceName,value,updateTime)
                    (?,?,?)
            '''
    conn.executemany(insert_Sql,data)

def getData(count):
    sql='''select top ? from dhtinfo 
      order by id desc'''
    return conn.execute(sql,(count))

def delButton(tree):
    x=tree.get_children()
    for item in x:
        tree.delete(item)

def updateTreeView(data):
    delButton(tree)
    for row in data:
        tree.insert("",row[0],values=row)
    tree.grid()

dbIni()
tk=Tk()



#tkinter 组件设置
tk.title('读取温湿度数据，写入数据库中')
vT = IntVar()
vH = IntVar()
tk.geometry('640x480')
f=Frame(tk,width=640,height=480)
f.place(x=10, y=10, anchor=NW)
cbTemp=Checkbutton(f,text="读取温度",variable=vT)
cbHum=Checkbutton(f,text="读取湿度",variable=vH)
cbTemp.pack(anchor=NW)
cbHum.pack(anchor=NW)
label=Label(f,text="")
cbTemp.pack()
cbHum.pack()
label.pack()
Button(f,text="开始读取",command=okButtonClick,width=14).pack(pady=3,anchor=NW)
Button(f,text="停止读取",command=writeButtonClick,width=14).pack(pady=3,anchor=NW)
Button (f,text='显示最近100条数据',command=selectTopClick,width=14).pack(pady=3,anchor=NW)

tree=ttk.Treeview(f)#表格
tree["columns"] = ("ID","传感器", "传感器值", "写入时间")
tree.column("ID",width=50,anchor='center')
tree.column("传感器", width=60)  # 表示列,不显示
tree.column("传感器值", width=60)
tree.column("写入时间", width=120)

tree.heading("ID", text="ID")  # 显示表头
tree.heading("传感器", text="传感器")
tree.heading("传感器值", text="传感器值")
tree.heading("写入时间",text="写入时间")
tree.insert("",0, values=("1", "2", "3"))  # 插入数据，
tree.insert("", 1, "", values=("1", "2", "3"))
tree.insert("", 2, "", values=("1", "2", "3"))
tree.insert("", 3, "", values=("1", "2", "3"))
tree["show"] = "headings"
tree.pack()
tk.mainloop()
