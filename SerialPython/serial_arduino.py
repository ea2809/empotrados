import serial

ser = serial.Serial('/dev/cu.usbmodem1421', 9600)
s = [0]
while True:
    readSerial = ser.readline()+"";
    print readSerial
    # Si es uno es verdad, sino es mentira
    if (readSerial[0:4] == "1234"):
        ser.writelines("1")
    else:
        ser.writelines("0")