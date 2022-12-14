import tkinter as tk
import serial 
import threading

import matplotlib
matplotlib.use("TkAgg")
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg, NavigationToolbar2Tk
from matplotlib.figure import Figure
import matplotlib.animation as animation
from matplotlib import style
style.use("ggplot")

#Maps to parse serial input into strings
state = ['NORMAL', 'PRE-ALARM', 'ALARM', 'MANUAL'] 
lightingState = ['ON', 'OFF', 'SHUTDOWN']

#Create the tkinter master object
root = tk.Tk()
root.title('Smart Bridge')

#Init serial comm
ArduinoSerial = serial.Serial('COM5', 9600) 

#Erase content of WaterLevelData file
open('waterLevelData.txt', 'w').close()

#Main worker to handle serial comm with arduino
def arduino_worker():
    while True:
        data = ArduinoSerial.readline().strip().decode("utf-8")
        if data.startswith("SmartLight:"):
            smartLight.set(lightingState[int(data.split(":")[1])])
        elif data.startswith("Bridge:"):
            bridgeState.set(state[int(data.split(":")[1])])
        elif data.startswith("Graph:"):
            file = open('waterLevelData.txt', 'a')
            file.write(data.split(":")[1] + "\n")
            file.close()

#Smart light state label
tk.Label(root, text="Smart Light State:").pack()
smartLight = tk.StringVar()
tk.Label(root, textvariable=smartLight).pack()

#Bridge state label
tk.Label(root, text="Bridge State:" ).pack()
bridgeState = tk.StringVar()
tk.Label(root, textvariable=bridgeState).pack()

#Realtime graph (matplotlib figure embedded into tkinter window)
f = Figure(figsize=(5,4), dpi=100)
a = f.add_subplot(111)

#Function to plot data in realtime
def animate(i):
    pullData = open('waterLevelData.txt','r').read()
    dataArray = pullData.split('\n')
    xar=[]
    yar=[]
    for eachLine in dataArray:
        if len(eachLine)>1:
            x,y = eachLine.split(',')
            xar.append(float(x))
            yar.append(float(y))
    a.clear()
    a.plot(xar,yar)

canvas = FigureCanvasTkAgg(f, master=root)
canvas.draw()
canvas.get_tk_widget().pack(side=tk.TOP, fill=tk.BOTH, expand=1)

toolbar = NavigationToolbar2Tk( canvas, root )
toolbar.update()
canvas._tkcanvas.pack(side=tk.TOP, fill=tk.BOTH, expand=1)

ani = animation.FuncAnimation(f,animate, interval=1000)

#Threads start
threading.Thread(target=arduino_worker, daemon=True).start()
root.mainloop()