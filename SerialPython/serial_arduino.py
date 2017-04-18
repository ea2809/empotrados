import urllib2
import serial

SER = serial.Serial('/dev/cu.usbmodem1411', 9600)

API = "14342345243243545"

while True:
    READSERIAL = SER.readline()+""
    print READSERIAL
    # Si es uno es verdad, sino es mentira
    PETICION = urllib2.urlopen("http://127.0.0.1:8080/check/"+API+"/"+READSERIAL)
    LEIDO = PETICION.read()
    print LEIDO
    PETICION.close()
    SER.writelines(LEIDO);