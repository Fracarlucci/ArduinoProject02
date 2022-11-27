import serial
import time 

arduino = serial.Serial(port = 'COM4', baudrate = '9600', timeout = .1)
state = ['NORMAL', 'PRE-ALARM', 'ALARM', 'MANUAL'] 
lightingState = ['ON', 'OFF', 'SHOTDOWN']

while True:
  value = arduino.readline().decode()
  if(len(value) > 0):
    if(value[0] == 's'):
      print(state[int(value[1])])
    if(value[0] == 'l'):
      print(lightingState[int(value[1])])