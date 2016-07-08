import serial
import serial.tools.list_ports as list
from serial.serialutil import SerialException
import io
from time import sleep

version = "0.1"

""" Talks to available ports and creates motor object if it finds anything """
def getMotors (config_folder = ""):
    # initialize return array
    motors = []

    # if configuration folder is not given, then use default
    # if (config_folder == ""):

    # search through available ports
    for port in list.comports():
        print("Found " + port.device)

        # if we can establish communications with the port, get the id and then append motor object to motors
        if (establishComms(port.device)):
            ID = sendMessage("?", "id", "_", port.device)
            motors.append(str(ID[2]))
            # motors.append(Motor(config_folder, port.device, ID))

    # return motor array
    return motors

def establishComms(port):
    # send initial message
    response = sendMessage ("?", "version", "_", port)

    # check to make sure that returned version matches ours
    if (response[2] == version):
        return True

    # communications have not been established
    return False

def sendMessage(symbol, command, data, port, func=None):
    # define delay because of serial gods looking down on us
    delay = 0.6
    try:
        # create serial port and relevant text wrapper
        ser = serial.Serial(None, timeout=2)
        ser.port = port
        ser.dsrdtr = True
        ser.open()

        # create message
        msg = "{} {} {}".format(symbol, command, data)

        # ask the gods of serial about the delays
        # sleep(delay)
        ser.write(bytes(msg, "ascii"))
        # sleep(delay)

        # read response and strip extrenous space and split it
        response = ser.readline().strip().decode("ascii").split(" ")

        # make sure that there are 3 parts
        if len(response) != 3:
            raise Exception("Arduino response was not proper length, but was {}".format(response))

        # make sure that response has the same command as initial message
        if response[1] != command:
            raise Exception("Arduino responded with incorrect command. {} instead of {}".format(response[1], command))

        # if response opens a stream, pass the serial instance to a given function
        if response[0] == ">" and func != None:
            func(ser)

        return response
    except SerialException:
        print("Failed to open {}".format(port))

# print(getMotors())

def func(ser):
    while True:
        response = ser.readline().strip().decode("ascii").split(" ")
        print(response)
        if response[0] == "/":
            break

port = "/dev/ttyACM0"
sendMessage("!", "move", '10', port, func)
print("done")

"""
# Disable reset after hangup
with open(path) as f:
    attrs = termios.tcgetattr(f)
    attrs[2] = attrs[2] & ~termios.HUPCL
    termios.tcsetattr(f, termios.TCSAFLUSH, attrs)
"""