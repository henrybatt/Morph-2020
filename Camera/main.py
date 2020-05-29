# Untitled - By: Henry - Mon Oct 7 2019

##### MUST MAKE CFASTER


ATTACK_YELLOW = True
ROBOT = 1   # 1=A, 0=B

DEBUG_WHITEBAL = False
DEBUGGING = False


## ======================= BLOB Finder =======================
import image, sensor, time
from math import atan2, sqrt, degrees

class Find():

    def __init__(self):
        self.NO_DATA_ANGLE = -1
        self.NO_DATA_DIST = 0
        self.debugCount = 0
        self.DEBUG_COUNT_MAX = 30


    def init(self, robot, _ATTACK_YELLOW, _debug, DEBUG_WHITEBAL):
    # - Setup Sensors and values - #

        self.debug = _debug
        self.attackIsYellow = _ATTACK_YELLOW
        self.robot = robot

        # - Camera Specific Values - #
        if robot:
            self.thresholds = [
            (64, 99, -78, 31, 55, 96),   #Yellow Goal
            (11, 50, -60, -11, -7, 34)]   #Blue Goal
            self.whitebal = (-6.157801, -6.02073, -0.931115)
            self.window = (20, 0, 120, 120)
            self.MAX_RAD = 70
            self.CENTREX = 60
            self.CENTREY = 60
        else:
            self.thresholds = [
            [(0, 0, 0, 0, 0, 0)],   #Yellow Goal
            [(0, 0, 0, 0, 0, 0)]]   #Blue Goal
            self.whitebal = (-6.02073, -5.886325, -1.476391)
            self.window = (20, 0, 120, 120)
            self.MAX_RAD = 70
            self.CENTREX = 60
            self.CENTREY = 60

        # - Sensor Setup - #
        sensor.reset()
        sensor.set_pixformat(sensor.RGB565)
        sensor.set_framesize(sensor.QQVGA)
        sensor.set_windowing(self.window)
        sensor.skip_frames(time = 100)

        # -  Balance - #

        if DEBUG_WHITEBAL:
            sensor.set_auto_whitebal(True)
        else:
            sensor.set_brightness(0)
            sensor.set_contrast(3)
            sensor.set_saturation(2)

            sensor.set_auto_whitebal(False, rgb_gain_db=self.whitebal)
            sensor.set_auto_exposure(False, exposure_us=10000)
            sensor.set_auto_gain(False, gain_db=15)
            sensor.skip_frames(time=500)


    def screenshot(self):
        self.img = sensor.snapshot()
        if (self.debug):
            self.img.draw_cross(self.CENTREX, self.CENTREY)
            self.img.draw_circle(self.CENTREX, self.CENTREY, self.MAX_RAD)
            self.img.draw_string(30, 0, str(self.robot)+" " +str(self.attackIsYellow))


    def calculateAngleDist(self, object):
        x = object.cx() - (self.CENTREX)
        y = object.cy() - (self.CENTREY)
        angle = (450 - degrees(atan2(y, x))) % 360
        distance = (sqrt(x**2 + y**2))
        return angle, distance


    def whiteBal(self):
       self.debugCount += 1
       if self.debugCount >= self.DEBUG_COUNT_MAX:
           print(sensor.get_rgb_gain_db())
           self.debugCount = 0


    def sortBlobs(self, blobs):
        if len(blobs) > 0:
            for blob in sorted(blobs, key=lambda x: x.pixels(), reverse = True):
                angle, distance = self.calculateAngleDist(blob)
                if distance < self.MAX_RAD:
                    if (self.debug):
                        self.img.draw_cross(blob.cx(), blob.cy())
                        self.img.draw_rectangle(blob.rect())
                        self.img.draw_line((self.CENTREX, self.CENTREY, blob.cx(), blob.cy()),thickness=1)
                    return(angle, distance)
        return(self.NO_DATA_ANGLE, self.NO_DATA_DIST)


    def findBlobs(self):
        # - Find all goal blobs and return their angles and distances - #

        self.screenshot()

        goalBlobs = self.img.find_blobs(self.thresholds[0:], x_stride=5, y_stride=5, area_threshold=200, pixel_threshold=200, merge=True, margin=23)

        # Blob Codes #
        # yellow = 1
        # blue = 2

        yellowBlobs = []
        blueBlobs = []

        for blob in goalBlobs:
            if blob.code() == 1:
                yellowBlobs.append(blob)
            elif blob.code() == 2:
                blueBlobs.append(blob)

        if self.attackIsYellow:
            attackAngle, attackDist = self.sortBlobs(yellowBlobs)
            defendAngle, defendDist = self.sortBlobs(blueBlobs)
        else:
            attackAngle, attackDist = self.sortBlobs(blueBlobs)
            defendAngle, defendDist = self.sortBlobs(yellowBlobs)

        return([attackAngle, attackDist, defendAngle, defendDist])




## ======================= SEND DATA =======================
from pyb import UART, LED

class Send():

    def __init__(self, bus=3, baud=115200, tout_c=10):
        self.uart = UART(bus, baud, timeout_char=tout_c)


    def sendData(self, data):

        data = [round(x) for x in data]

        # - Data to write - #
        # Starting byte
        sendData = [255, 255]

        # Attack Data
        sendData.append((data[0] >> 8) & 0xFF)
        sendData.append(data[0] & 0xFF)
        sendData.append(data[1])

        # Defend Data
        sendData.append((data[2] >> 8) & 0xFF)
        sendData.append(data[2] & 0xF)
        sendData.append(data[3])

        # - Ensure no data is the same as starting byte - #
        for i in range(1, len(sendData)):
            if(sendData[i] == 255): sendData[i] -= 1

        # - Send Data - #
        for d in sendData:
            self.uart.writechar(d)


        print(', '.join(map(str, data)))
        #print(', '.join(map(str, sendData)))


## ======================= MAIN =======================

clock = time.clock()

LED(1).on()

finder = Find()
sender = Send()

finder.init(ROBOT, ATTACK_YELLOW, DEBUGGING, DEBUG_WHITEBAL)

LED(1).off()

while(True):

    clock.tick()
    if DEBUG_WHITEBAL:
        finder.whiteBal()

    data = finder.findBlobs()
    sender.sendData(data)

    #print(clock.fps())
