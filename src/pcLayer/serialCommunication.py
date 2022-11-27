import serial
import time 

arduino = serial.Serial(port = 'COM4', baudrate = '9600', timeout = .1)

while True:
  value = arduino.readlines()
  if(len(value) > 0):
    print(value)