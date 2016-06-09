# test serial program

import serial
import serial.tools.list_ports as ports
from serial.serialutil import SerialException
import io
from time import sleep

devices = {}

# response
estCall = "? listen _"
estResponse = "$ listen yes"

def main():  
    devices = findPorts()

    print(devices)       

def findPorts():
    ret = {}

    # List Available serial ports
    for port in ports.comports():
        print("Found " + port.device)

        if (establishComms(port.device)):
            ID = getID(port.device)
            ret[ID] = port.device;

    # if len(ret) < 1:
    #     findPorts()

    return ret

def getID(port):
    ID = sendMessage("? id _", port).split(" ")

    if len(ID) < 3:
        confirmation = sendMessage("! id test_motor_00", port)

    return ID[2]

def establishComms(port):
    response = sendMessage(estCall, port)

    if (response == estResponse):
        return True

    return False

def sendMessage(msg, port):
    try:
        ser = serial.Serial(port, timeout=1)
        sleep(0.1)
        ser.setDTR(0)
        sleep(0.1)
        # ser.open()

        sio = io.TextIOWrapper(io.BufferedRWPair(ser, ser))
        sio.write(msg)
        sio.flush()

        response = sio.readline().strip()
        return response
    except SerialException: 
        print("Failed to open {}".format(port))

main()