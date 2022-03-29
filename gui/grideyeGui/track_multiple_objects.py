import re
import sys
import serial
import sqlite3
import os.path
import datetime
import time
import copy
import random
import numpy as np
import matplotlib
import matplotlib.pyplot as plt
import matplotlib.image as mpimg
from matplotlib import animation

matplotlib.use('TkAgg')

columns = 8
rows = 8

zero = np.zeros((8, 8), dtype=float)
prev = np.zeros((8, 8), dtype=float)
plt.ion()
imgplot = plt.imshow(zero,cmap='YlOrRd', interpolation='nearest', vmin = 16.0, vmax = 25.0)
plt.colorbar(imgplot, orientation='vertical')
plt.grid(which='major', axis='both', linestyle='-')
plt.show()



class TrackObject():
    def __init__(self, pixel_id=None, pixel_x=None, pixel_y=None, temp=None):
        self.pixel_id = pixel_id
        self.pixel_x = pixel_x
        self.pixel_y = pixel_y
        self.temp = temp
        self.update_counter = 0

    def set_start_pixels(self, pixel_x=None, pixel_y=None, temp=None):
        self.start_pixel_x = pixel_x
        self.start_pixel_y = pixel_y
        self.temp = temp

        # determine the direction
        self.pixel_dir = pixel_dir

    def set_current_pixels(self, pixel_x=None, pixel_y=None, temp=None):
        self.temp = temp
        self.update_counter = 0
        # determine the direction
    
    def increment_count(self):
        self.update_counter = self.update_counter + 1
        

class FoundObject():
    def __init__(self, pixel_x=None, pixel_y=None, temp=None):
        self.pixel_x = pixel_x
        self.pixel_y = pixel_y
        self.temp = temp


# 3x3 pixels object detection
class Tracker():
    def __init__(self):
        self.track_object_list = []
        self.find_object_list = []
    def process_frame(self, frame):
        # check tracker list
        self.frame = frame

        print "new frame"
        self.find_object_list = []
        self.find_objects()

        # compare with the next frame
        self.update_tracker_list()


    def tracker_timeout(self):
        print "increment timeout"

        print "remove item from list if timeout exceeded"    

    def update_tracker_list(self):
        if self.find_object_list:
            if len(self.track_object_list) == 0:
                print "copy to tracker list"
                # scroll through the found object list and add it to the 
                # tracker list
                for found_idx, found_item in enumerate(self.find_object_list):
                    new_track_obj = TrackObject(found_idx, found_item.pixel_x, \
                        found_item.pixel_x, found_item.temp)
                    self.track_object_list.append(new_track_obj)
            else:
                # compare both list
                for found_idx, found_item in enumerate(self.find_object_list):
                    for track_idx, track_item in enumerate(self.track_object_list):
                        # check if pixel is in the list
                        # check if it is a neighbourhood pixel
                        if (found_item.pixel_x - track_item.pixel_x) <= 2 or \
                           (found_item.pixel_y - track_item.pixel_y) <= 2 :
                           # update tracker list
                           print "Update tracker list " + str(found_item.pixel_x) \
                           + "," + str(found_item.pixel_y)
                           track_item.pixel_x = found_item.pixel_x
                           track_item.pixel_y = found_item.pixel_y

                           # reset count
                           track_item.update_counter = 0
                        else:
                            print "Add the new item to the tracker list"
                            new_track_obj = TrackObject(found_idx, found_item.pixel_x, \
                                found_item.pixel_x, found_item.temp)
                            self.track_object_list.append(new_track_obj)

        
        # update tracker lifetime
        if len(self.track_object_list) > 0:
            for idx, item in enumerate(self.track_object_list):
                # increment count
                self.track_object_list[idx].increment_count()

                # check if count is greater than threshold
                if  self.track_object_list[idx].update_counter > 3:
                    # remove from the list
                    print "Remove item from the list"
                    self.track_object_list.remove(item)
                

    def find_objects(self):
        # scroll through the rows and columns
        for j in range(columns):
            for i in range(rows):
                # check if pixel value is greater than 0 deg C
                if self.frame[i][j] > 0:
                    if len(self.find_object_list) == 0:
                        print "Add first found object:" + str(i) + "," + str(j)
                        print "temp: " + str(self.frame[i][j])
                        # add the first object
                        found_obj = FoundObject(i, j, self.frame[i][j])
                        self.find_object_list.append(found_obj)
                    else:
                        # set flag to indicate a new object
                        new_object = True

                        # iterate through the object list
                        for idx, item in enumerate(self.find_object_list):
                            # check if item and current pixel is 1 pixel distance
                            if self.find_object_list[idx].pixel_x == (i - 1) \
                            or self.find_object_list[idx].pixel_y == (j - 1):
                                # check if the current temp is greater than the 
                                # item temp
                                if self.frame[i][j] > self.find_object_list[idx].temp:
                                    # update the object in the list
                                    print "Update object:" + str(i) + "," + str(j)
                                    print "temp: " + str(self.frame[i][j]) \
                                    + ", " + str(self.find_object_list[idx].temp)
                                    self.find_object_list[idx].pixel_x = i
                                    self.find_object_list[idx].pixel_y = j
                                    self.find_object_list[idx].temp = self.frame[i][j]

                                # reset flag to indicate not to add new object
                                new_object= False

                        # check if new object
                        if new_object:
                            # add new object in the list
                            print "Add new object:" + str(i) + "," + str(j)
                            found_obj = FoundObject(i, j, self.frame[i][j])
                            self.find_object_list.append(found_obj)


class FrameProcessor():
    def __init__(self, input_file):
        self.input_file = input_file
        self.first_frame = True
        self.tracker = Tracker()
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
                # print "Average: " + str(average)
                
                if array.size == 64:
                    max_value=np.amax(array)
                    array[array< (average + 2.2)] = 0
                    # print "Max=" + str(max_value)
                    

                    B=np.reshape(array, (-1, 8))
                    
                    self.tracker.process_frame(B)


                    # if np.all(B == 0):
                    #     print "all zeroes"
                    #     B[:] = prev 
                    # print B
                    
                    imgplot.set_data(B)
                    plt.clf()
                    plt.imshow(B,cmap='YlOrRd', interpolation='nearest', vmin = 15.0, vmax = 30.0)
                    plt.draw()
                    # print "assign previous"
                    # prev[:] = B

                # time.sleep(0.5)

if __name__ == '__main__':
    rxport = "/dev/ttyUSB0"
    baud = 115200

    try:
        with open("log11aug15.txt",'rb') as fileread:            
            frame_obj = FrameProcessor(fileread)

            frame_obj.start()

# if __name__ == '__main__':
#     rxport = "/dev/ttyUSB0"
#     baud = 115200

#     try:
#         serial_rx_object = serial.Serial(rxport, baud, timeout=0.5)
        
#         serial_tester = FrameProcessor(serial_rx_object)

#         serial_tester.start()
        
    except (KeyboardInterrupt):
        # Exit the program, as we have received a Ctrl-C from the user
        print("Ctrl-C received, exiting...")
        sys.exit(1)

    except (IOError):
        print("Pipe no longer available, exiting...")
        sys.exit(1)
    except (ValueError):
        print("Device parameters out of range, exiting...")
        sys.exit(1)
    finally:
        print("tracking closed, exiting...")
        sys.exit(1)
