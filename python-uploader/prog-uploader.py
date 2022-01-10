import serial
import time

arduino = serial.Serial(port='COM6', baudrate=9600, timeout=1)

filename = input("Filename: ")

lines = []
f = open(filename)
lines = f.readlines()


print(arduino.readlines())
time.sleep(1)
arduino.write(bytes(str("write"), 'utf-8'))
time.sleep(1)
print(arduino.readlines())
arduino.write(bytes(str(str("prog")+input("enter program number 1~5: ")), 'utf-8'))
time.sleep(1)
print(arduino.readlines())

for line in lines:
    time.sleep(2)
    receive = arduino.readlines()
    print(receive)
    print(line)
    arduino.write(bytes(str(line), 'utf-8'))

    

    

