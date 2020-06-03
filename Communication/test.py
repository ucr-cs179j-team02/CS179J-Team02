import time
import serial

ser = serial.Serial('COM3', 9600)

val = "3"

for i in range(3):
    ser.write(val.encode())
    time.sleep(0.26)

print("hello")
#ser.write(val.encode())
