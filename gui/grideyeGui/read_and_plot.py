import re
import sys
import serial
import sqlite3
import os.path
import datetime
import time
import random
import numpy as np
import matplotlib
import matplotlib.pyplot as plt
import matplotlib.image as mpimg
from matplotlib import animation

matplotlib.use('TkAgg')

zero = np.zeros((8, 8), dtype=float)
prev = np.zeros((8, 8), dtype=float)
plt.ion()
imgplot = plt.imshow(zero,cmap='YlOrRd', interpolation='nearest', vmin = 16.0, vmax = 25.0)
plt.colorbar(imgplot, orientation='vertical')
plt.grid(which='major', axis='both', linestyle='-')
plt.show()


class SerialTester():
    def __init__(self, input_file):
        self.input_file = input_file
        self.first_frame = True

    def start(self):
        while True:
            data = self.input_file.readline()
            self.process_data(data)

    def process_data(self, rxdata):
        # print(rxdata)
        if "T" in rxdata:
            thermistor_value = re.findall("\d+.\d+", rxdata)
            print "Therm=" + str(thermistor_value)
        else:
            if (any(i in rxdata for i in ('{','}'))):
                rxdata=rxdata.replace('{','')
                rxdata=rxdata.replace('}','')
                rxdata=rxdata[:-1]
                array=np.fromstring(rxdata, dtype=float, sep=",")
                average = np.mean(array)
                print "Average: " + str(average)
                
                if array.size == 64:
                    max_value=np.amax(array)
                    array[array< (average + 2.2)] = 0
                    print "Max=" + str(max_value)


                    B=np.reshape(array, (-1, 8))
                    B = B

                    if np.all(B == 0):
                        print "all zeroes"
                        B[:] = prev 
                    print B
                    
                    imgplot.set_data(B)
                    plt.clf()
                    plt.imshow(B,cmap='YlOrRd', interpolation='nearest', vmin = 22.0, vmax = 28.0)
                    plt.draw()
                    # print "assign previous"
                    prev[:] = B

                # time.sleep(0.1)

if __name__ == '__main__':
    rxport = "/dev/ttyUSB0"
    baud = 115200

    try:
        with open("multiple_people2.txt",'rb') as fileread:            
            serial_tester = SerialTester(fileread)

            serial_tester.start()

# if __name__ == '__main__':
#     rxport = "/dev/ttyUSB0"
#     baud = 115200

#     try:
#         serial_rx_object = serial.Serial(rxport, baud, timeout=0.5)
        
#         serial_tester = SerialTester(serial_rx_object)

#         serial_tester.start()

    except (KeyboardInterrupt):
        # Exit the program, as we have received a Ctrl-C from the user
        print("Ctrl-C received, exiting...")
        sys.exit(1)

    except (IOError):
        print("Pipe no longer available, exiting...")
        sys.exit(1)

    except (serial.SerialException):
        print("Device can't be found, exiting...")
        sys.exit(1)

    except (ValueError):
        print("Device parameters out of range, exiting...")
        sys.exit(1)
    finally:
        print("serial closed, exiting...")
        sys.exit(1)
