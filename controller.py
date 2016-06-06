# test serial program

import serial
import serial.tools.list_ports as ports
import io
from time import sleep

devices = []

# response
estCall = "? listen _"
estResponse = "$ listen yes"

def main():
    
    devices = findPorts()

    print(devices)

    # ask for ids
    for port in devices:
        print(getID(port))        

def findPorts():
    ret = []

    # List Available serial ports
    for port in ports.comports():
        print(port.device)

        if (establishComms(port.device)):
            ret.append(port.device)

    # if len(ret) < 1:
    #     findPorts()

    return ret

def getID(port):
    ID = sendMessage("? id _", port).split(" ")

    if len(ID) < 3:
        confirmation = sendMessage("! set_id test_motor_00", port)
        print(confirmation)

    return ID

def establishComms(port):
    response = sendMessage(estCall, port)

    if (response == estResponse):
        return True

    return False

def sendMessage(msg, port):
    ser = serial.Serial(port, timeout=1)
    sio = io.TextIOWrapper(io.BufferedRWPair(ser, ser))
    sio.write(msg)
    sio.flush()

    return sio.readline().strip()

main()