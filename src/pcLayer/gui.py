import tkinter as tk
import serial 
import threading
from tkinter import Scale, HORIZONTAL

import matplotlib
matplotlib.use("TkAgg")
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg, NavigationToolbar2Tk
from matplotlib.figure import Figure
import matplotlib.animation as animation
from matplotlib import style
style.use("ggplot")

# Create the master object
root = tk.Tk()

#Init serial comm
ArduinoSerial = serial.Serial('COM3', 9600) 

#Erase content of WaterLevelData file
open('waterLevelData.txt', 'w').close()

#Main worker to handle serial comm with arduino
def arduino_worker():
    while True:
        data = ArduinoSerial.readline().strip().decode("utf-8")
        if data.startswith("SmartLight:"):
            smartLight.set(data.split(":")[1])
        elif data.startswith("Bridge:"):
            bridgeState.set(data.split(":")[1])
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

#Slider 

tk.Label(root, text="Open Valve:" ).pack()

def onSliderChange(event):
     ArduinoSerial.write(("Slider: " + str(slider.get())).encode("utf-8"))

slider = Scale(root, from_=0, to=180, command=onSliderChange, orient=HORIZONTAL)
slider.pack()

#Realtime graph
f = Figure(figsize=(5,4), dpi=100)
a = f.add_subplot(111)

def animate(i):
    pullData = open('waterLevelData.txt','r').read()
    dataArray = pullData.split('\n')
    xar=[]
    yar=[]
    for eachLine in dataArray:
        if len(eachLine)>1:
            x,y = eachLine.split(',')
            xar.append(int(x))
            yar.append(int(y))
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