import subprocess
import atexit
import serial

#The following line is for serial over GPIO
port = '/dev/ttyUSB0'

ard = serial.Serial(port,115200,timeout=5)

def myrun(cmd):
    """from http://blog.kagesenshi.org/2008/02/teeing-python-subprocesspopen-output.html
    """
    p = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    stdout = []
    while True:
        line = p.stdout.readline()
        print(line, end="\r") # only works in terminal
        line = b'98'+b';'+line+b';99;'
        #print(line)
        sendToArd(line)
        if line == '' and p.poll() != None:
            break
    return ''.join(stdout)

def sendToArd(msg):
    ard.write(msg)

def closeConnection():
    print("Closing Connection")
    ard.close()

atexit.register(closeConnection)

command="cava -p ./cava-config"

myrun(command)



