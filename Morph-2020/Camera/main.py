# Untitled - By: Henry - Mon Oct 7 2019

ATTACK_YELLOW = True
ROBOT = 1   # 1=A, 0=B

DEBUG_WHITEBAL = False
DEBUGGING = True


## ======================= BLOB Finder =======================
import image, sensor, time
from math import atan2, sqrt, degrees

class Find():

    def __init__(self):
        self.NO_DATA = 250
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
            [(0, 0, 0, 0, 0, 0)],   #Yellow Goal
            [(0, 0, 0, 0, 0, 0)]]   #Blue Goal
            self.whitebal = (-6.02073, -5.886325, -1.476391)
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

            sensor.set_auto_exposure(False, exposure_us=sensor.get_exposure_us())#10000)
            sensor.set_auto_gain(False, gain_db=sensor.get_gain_db())#15)
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
                    return(angle, distance, True)
        return(self.NO_DATA, self.NO_DATA, False)


    def findBlobs(self):
        # - Find all goal blobs and return their angles and distances - #

        self.screenshot()

        yellowBlobs = self.img.find_blobs(self.thresholds[0],x_stride=5, y_stride=5, area_threshold=200, pixel_threshold=200, merge=True, margin=23)
        blueBlobs = self.img.find_blobs(self.thresholds[1],x_stride=5, y_stride=5, area_threshold=200, pixel_threshold=200, merge=True, margin=23)


        attackX, attackY, attackE = self.sortBlobs(self.attackIsYellow and yellowBlobs or blueBlobs)
        defendX, defendY, defendE = self.sortBlobs(self.attackIsYellow and blueBlobs or yellowBlobs)

        return([attackX, attackY, attackE, defendX, defendY, defendE])




## ======================= SEND DATA =======================
from pyb import UART, LED

class Send():

    def __init__(self, bus=3, baud=115200, tout_c=10):
        self.uart = UART(bus, baud, timeout_char=tout_c)


    def sendData(self, data):

        sendData = [255]

        for i in data:
            i = round(i)
            #print(', '.join(map(str, data)))
            sendData.append(i >> 8)
            sendData.append(i)

        for i in sendData:
            self.uart.writechar(i)







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

    print(clock.fps())
