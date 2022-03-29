import re
import math
import time
import matplotlib
matplotlib.use("TkAgg")

from pylab import *
from random import randint


thermo_vmin = 14.0
thermo_vmax = 30.0

track_vmin = 0.0
track_vmax = 50.0

columns = 8
rows = 8

pause = False
up_counter = 0
down_counter = 0

print "Initialize values"
thermo_array = np.zeros((8, 8), dtype=float)
track_array = np.zeros((8, 8), dtype=float)
"""initial conditions"""

"""creating the plot"""
print "Creating the plots"
fig, ax_lst = plt.subplots(1, 2)
therm_plot = ax_lst[0].imshow(thermo_array, interpolation='nearest',
                            vmin=thermo_vmin,
                            vmax=thermo_vmax,
                            cmap='YlOrRd')
track_plot = ax_lst[1].imshow(track_array, interpolation='nearest',
                        vmin=track_vmin,
                        vmax=track_vmax,
                        cmap='Accent')

# x = np.linspace(0, 2 * np.pi, 400)
# y = np.sin(x ** 2)

# xy_plot = ax_lst[2].scatter(x, y)

# mng = plt.get_current_fig_manager()
# mng.window.maxsize()

def onclick(event):
    global pause
    pause = not pause

fig.canvas.mpl_connect('button_press_event', onclick)

class TrackObject():
    def __init__(self, pixel_id=None, pixel_x=None, pixel_y=None, temp=None):
        self.pixel_id = pixel_id
        self.pixel_x = pixel_x
        self.pixel_y = pixel_y
        self.temp = temp
        self.timeout = 0

    def set_start_pixels(self, pixel_x=None, pixel_y=None, temp=None):
        self.start_pixel_x = pixel_x
        self.start_pixel_y = pixel_y
        self.temp = temp

        # determine the direction
        self.pixel_dir = pixel_dir

    def set_current_pixels(self, pixel_x=None, pixel_y=None, temp=None):
        self.temp = temp
        self.timeout = 0
        # determine the direction
    
    def increment_count(self):
        self.timeout = self.timeout + 1
        

class FoundObject():
    def __init__(self, pixel_x=None, pixel_y=None, temp=None):
        self.pixel_x = pixel_x
        self.pixel_y = pixel_y
        self.temp = temp


# 3x3 pixels object detection
class Tracker():
    def __init__(self):
        self.current_track_object_list = []
        self.new_track_object_list = []
        self.find_object_list = []
    def process_frame(self, frame):

        track_array = np.zeros((8, 8), dtype=float)
        # check tracker list
        self.frame = frame

        print "new frame"
        self.find_object_list = []
        self.find_objects()

        # compare with the next frame
        self.new_track_object_list = []
        self.update_tracker_list()


    def tracker_timeout(self):
        print "increment timeout"

        print "remove item from list if timeout exceeded"    

    def update_tracker_list(self):
        if self.find_object_list:
            if len(self.current_track_object_list) == 0:
                
                # scroll through the found object list and add it to the 
                # tracker list
                for found_idx, found_item in enumerate(self.find_object_list):
                    
                    new_track_obj = TrackObject(randint(0,1000), found_item.pixel_x, \
                        found_item.pixel_y, found_item.temp)
                    ts = time.time()
                    # track_array[found_item.pixel_x,found_item.pixel_y] = 20.0
                    print str(ts) + ": copy to tracker list: " \
                    + str(new_track_obj.pixel_id) + ": " +\
                    str(new_track_obj.pixel_x) + "," + str(new_track_obj.pixel_y)
                    self.current_track_object_list.append(new_track_obj)
            else:
                # compare both list
                for found_idx, found_item in enumerate(self.find_object_list):

                    add_new_object = True

                    for track_idx, track_item in enumerate(self.current_track_object_list):

                        print "Found: " + str(found_item.pixel_x) + "," + str(found_item.pixel_y)
                        print "Track: " + str(track_item.pixel_x) + "," + str(track_item.pixel_y)

                        # check if pixel is in the list
                        # check if it is a neighbourhood pixel
                        if abs(found_item.pixel_x - track_item.pixel_x) <= 1 and \
                           abs(found_item.pixel_y - track_item.pixel_y) <= 2 :

                            # update tracker list
                            ts = time.time()
                            global down_counter
                            global up_counter

                            # # Check if the item has cross the center line
                            if (track_item.pixel_y == 2 or track_item.pixel_y == 3) \
                                and (found_item.pixel_y == 4 or found_item.pixel_y == 5):
                                up_counter += 1
                                print "<<<< up ++ >>>> " + str(up_counter)

                            if (track_item.pixel_y == 5 or track_item.pixel_y == 4) \
                             and (found_item.pixel_y == 3 or found_item.pixel_y == 2):
                                # print "<<<< down ++ >>>>"
                                down_counter += 1
                                print "<<<< down ++ >>>> " + str(down_counter)

                            print str(ts) + ": Update tracker list " + str(track_item.pixel_id) + ": "\
                            + str(found_item.pixel_x) + "," + str(found_item.pixel_y)
                            track_item.pixel_x = found_item.pixel_x
                            track_item.pixel_y = found_item.pixel_y

                            # track_array[track_item.pixel_x,track_item.pixel_y] = 50.0

                            # reset count
                            track_item.timeout = 0
                            add_new_object = False
                            break

                    if add_new_object:       
                        random_id = randint(0,1000)
                        new_track_obj = TrackObject(random_id, found_item.pixel_x, \
                            found_item.pixel_y, found_item.temp)
                        # track_array[found_item.pixel_x,found_item.pixel_y] = 40.0
                        ts = time.time()
                        print str(ts) + ": Add the new item to the tracker list:"\
                        + str(new_track_obj.pixel_id) + ": " +\
                        str(new_track_obj.pixel_x) + "," + str(new_track_obj.pixel_y)
                        self.new_track_object_list.append(new_track_obj)

                # copy the new object list to the current tracking list
                if len(self.new_track_object_list) > 0:
                    for new_idx, new_item in enumerate(self.new_track_object_list):
                        new_track_obj = TrackObject(new_item.pixel_id, new_item.pixel_x, \
                                    new_item.pixel_y, new_item.temp)
                        self.current_track_object_list.append(new_track_obj)
        
        # update counter - determine how many times the tracker has been updated
        # over a certain threshold remove it
        
        

        # update tracker lifetime
        if len(self.current_track_object_list) > 0:
            for idx, item in enumerate(self.current_track_object_list):
                # increment count
                self.current_track_object_list[idx].increment_count()

                # check if count is greater than threshold
                if  self.current_track_object_list[idx].timeout > 2:
                    # remove from the list
                    ts = time.time()
                    print str(ts) + ": Remove item from the list: " + str(item.pixel_id)
                    self.current_track_object_list.remove(item)
                

    def find_objects(self):
        # scroll through the rows and columns
        for j in range(columns):
            for i in range(rows):
                # check if pixel value is greater than 0 deg C
                if self.frame[i][j] > 0:
                    if len(self.find_object_list) == 0:
                        ts = time.time()
                        print str(ts) + ": Add first found object:" + str(i) + "," + str(j)
                        # print "temp: " + str(self.frame[i][j])
                        # gray color
                        track_array[i,j] = 50.0 
                        # add the first object
                        found_obj = FoundObject(i, j, self.frame[i][j])
                        self.find_object_list.append(found_obj)
                    else:
                        # set flag to indicate a new object
                        new_object = True

                        # iterate through the object list
                        for idx, item in enumerate(self.find_object_list):
                            # check if item and current pixel is 1 pixel distance
                            if abs(self.find_object_list[idx].pixel_x -i) <= 1 \
                            and abs(self.find_object_list[idx].pixel_y -j) <= 1:
                                # check if the current temp is greater than the 
                                # item temp
                                if self.frame[i][j] > self.find_object_list[idx].temp:
                                    # update the object in the list
                                    ts = time.time()
                                    print str(ts) + ": Update object:" + str(i) + "," + str(j)
                                    # print "temp: " + str(self.frame[i][j]) \
                                    # + ", " + str(self.find_object_list[idx].temp)
                                    # red color
                                    track_array[i,j] = 40.0
                                    self.find_object_list[idx].pixel_x = i
                                    self.find_object_list[idx].pixel_y = j
                                    self.find_object_list[idx].temp = self.frame[i][j]

                                # reset flag to indicate not to add new object
                                new_object= False

                        # check if new object
                        if new_object:
                            # add new object in the list
                            ts = time.time()
                            print str(ts) + ": Add new object:" + str(i) + "," + str(j)
                            found_obj = FoundObject(i, j, self.frame[i][j])
                            # yellowish color
                            track_array[i,j] = 20.0
                            self.find_object_list.append(found_obj)



class ProcessFrame():
    def __init__(self, input_file):
        self.input_file = input_file
        self.first_frame = True
        self.thermistor_value = 0.0
        self.tracker = Tracker()
    def start(self):
        while True:
            if not pause:
                data = self.input_file.readline()
                self.process_data(data)
            fig.canvas.get_tk_widget().update() # process events

    def process_data(self, rxdata):
        # print(rxdata)
        if "T" in rxdata:
            print "find therm value in string"
            # num = re.findall("\d+.\d+", rxdata)
            num = re.sub("[^0-9.]", " ", rxdata)
            num = num.replace(" ", "")
            if re.search("\.", num):
                try:
                    print num
                    self.thermistor_value = float(num)
                except ValueError:
                    print "Not a float"
                
            # print "Therm=" + str(thermistor_value)
        else:
            if (any(i in rxdata for i in ('{','}'))):
                rxdata=rxdata.replace('{','')
                rxdata=rxdata.replace('}','')
                rxdata=rxdata[:-1]
                array=np.fromstring(rxdata, dtype=float, sep=",")
                average = np.mean(array)

                print "average: " + str(average)

                if array.size == 64:
                    max_value=np.amax(array)
                    np.savetxt("foo.csv", array, delimiter=",")
                    print "max: " + str(max_value)
                    filtered = (max_value - average)/2
                    # array[array< (average + 1.2)] = 0
                    array[array <= average+1] = 0.0
                    thermo_array=np.reshape(array, (-1, 8))
                    self.tracker.process_frame(thermo_array)
                    therm_plot.set_data(thermo_array)
                    track_plot.set_data(track_array)
                    ts = time.time()
                    time_text = plt.text(-3,-2, "Time: " + str(ts), fontsize=17, ha="center")
                    up_count_text = plt.text(-8,10, "Up: " + str(up_counter), fontsize=17, ha="center")
                    down_count_text = plt.text(-5,10, "Down: " + str(down_counter), fontsize=17, ha="center")
                    plt.draw()
                    plt.pause(0.2)
                    time_text.remove() 
                    up_count_text.remove()
                    down_count_text.remove()



if __name__ == '__main__':
    try:
        # with open("puttyhot.log",'rb') as fileread:
        # with open("multiple_people2.txt",'rb') as fileread:
        with open("5JAN16 putty.log", 'rb') as fileread:
        # with open("putty@20.8C - Closed jacket.log",'rb') as fileread:
        # with open("putty@21C - Open jacket.log",'rb') as fileread:
        # with open("putty@18C.log",'rb') as fileread:
        # with open("putty27.log",'rb') as fileread:
        # with open("putty@21C - no jacket.log",'rb') as fileread:
            # print "Create Process Frame"            
            frame_obj = ProcessFrame(fileread)
            # print "Start Process Frame"
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