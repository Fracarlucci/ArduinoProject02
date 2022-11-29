import tkinter as tk
import serial 
import threading

# Create the master object
root = tk.Tk()

ArduinoSerial = serial.Serial('com5', 9600) 

def arduino_worker():
    while True:
        data = ArduinoSerial.readline().strip()
        if data.startswith("SmartLight:"):
            smartLight.set(data.split(":")[1])
        elif data.startswith("Bridge:"):
            bridgeState.set(data.split(":")[1])

#Smart Light State Label
tk.Label(root, text="Smart Light State:").grid(row=0, column=0, sticky='w')
smartLight = tk.StringVar()
tk.Label(root, textvariable=smartLight).grid(row=0, column=1, sticky='w')

#Bridge State Label
tk.Label(root, text="Bridge State:" ).grid(row=1, column=0, sticky='w')
bridgeState = tk.StringVar()
tk.Label(root, textvariable=bridgeState).grid(row=1, column=1, sticky='w')

threading.Thread(target=arduino_worker, daemon=True).start()
root.mainloop()