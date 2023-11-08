# import install_requirements

from kivy.config import Config
from numpy.lib.arraysetops import isin
Config.set('graphics', 'position', 'custom')
Config.set('graphics', 'left', 0)
Config.set('graphics', 'top',  30)
Config.set('graphics', 'width', 1600)
Config.set('graphics', 'height', 900)
from kivy.core.window import Window
# Window.clearcolor = (1, 1, 1, 1)
# Window.size = (1600, 900)  # input system window size

from backend_kivyagg import FigureCanvasKivyAgg
from kivy.app import App
from kivy.uix.button import Button
from kivy.uix.image import Image
from kivy.clock import Clock
from kivy.lang import Builder
from threading import Thread
from kivy.uix.screenmanager import ScreenManager, Screen

try:
    from tkinter import *
except:
    from Tkinter import *
import fakeDataGen as fdg
import PushDataParser as pdp
import matplotlib.pyplot as plt
import matplotlib.image as mpimage
import numpy as np
from PIL import Image
import time


# KIVY LAYOUT CODE
kivy_file = "EagleEyeKivyLayout.kv"

class PlottingTools():
    def __init__(self):
        self.lastPacketNum = -1

    def setupPlots(self):
        """
            ax1: Main People count with history
            ax2: People position mapping
            ax3: CO2 Data
            ax4: Ring chart of occupancy levels
            ax5: Heatmap of people positions
        """
        self.fig = plt.figure()
        
        self.ax1 = self.fig.add_subplot(2, 1, 2) # ax1 displays the live updating people count
        # ax1.set_aspect(0.6)

        self.ax2 = self.fig.add_subplot(2, 3, 1) # ax2 shows the position of the people detected by EagleEye
        self.ax2.set_aspect('equal', adjustable='box')
        self.ax2.axes.get_xaxis().set_visible(False)
        self.ax2.axes.get_yaxis().set_visible(False)
        # self.image = mpimage.imread("RealImage.jpg")
        # self.image = Image.open("FixedFisheyeInverted.jpg").rotate(180)
        self.image1 = Image.open("Images/FloorImage.jpg")
        self.image2 = Image.open("Images/newImage.jpg")

        self.ax3 = self.ax1.twinx()
        # self.ax3 = self.fig.add_subplot(2, 3, 1)
        # ax3.set_aspect(0.6)

        self.ax4 = self.fig.add_subplot(2, 3, 2)

        self.ax5 = self.fig.add_subplot(2, 3, 3)
    
    # Resets and replots data
    def update_plot(self, override=False, *args):
        if metaData.PacketNum == self.lastPacketNum:
            pass
        else:
            self.lastPacketNum = metaData.PacketNum
            self.resetPlots()
            self.ax1.plot(pplCount, main_accent_color)

            if self.imageOn == 1:
                self.ax2.imshow(self.image1)
            elif self.imageOn == 2:
                self.ax2.imshow(self.image2)

            if (metaData.PeopleCount > 0):
                self.updateHeatmap(metaData.People)
                for person in metaData.People:
                    self.ax2.add_patch(plt.Circle((person.ImageX, person.ImageY), radius=15, color=main_accent_color))

            # Overlay of Co2 data onto peopleCount graph
            self.ax3.plot(co2Data, 'seagreen')

            if metaData.PeopleCount > MAX_OCCUPANCY:
                self.ax4.pie(donutData, counterclock=False, startangle=90, colors=overfilled_colours, shadow=True)
            elif metaData.PeopleCount == MAX_OCCUPANCY:
                self.ax4.pie(donutData, counterclock=False, startangle=90, colors=cap_limit_colours, shadow=True)
            else:
                self.ax4.pie(donutData, counterclock=False, startangle=90, colors=donut_chart_colours, shadow=True)
                
            self.ax4.add_patch(plt.Circle( (0,0), 0.7, color='white'))
            self.ax4.text(0,0, f"{round(metaData.PeopleCount)}/{MAX_OCCUPANCY}", size='xx-large', ha='center', weight='bold', fontfamily='BarlowBlack')
            percentage = round(metaData.PeopleCount/MAX_OCCUPANCY * 100)
            # self.ax4.text(0.05,0, f"{percentage}%", size='x-large', ha='center', va='bottom', weight=400)
            self.ax4.set_xlabel(f"{percentage}% occupied", size='x-large')

            self.ax5.imshow(positionHeatmap.transpose(), alpha=0.8, cmap=hmColourScheme)
            self.ax5.invert_yaxis()

            self.ids.graphArea.clear_widgets()
            self.ids.graphArea.add_widget(FigureCanvasKivyAgg(self.fig),0)

    # resetPlots clears both plots and resets the axis settings
    def resetPlots(self):

        self.ax1.clear()
        self.ax1.grid(False)
        self.ax1.set_ylabel("# of People")
        self.ax1.set_yticks([x for x in range(0, MAX_OCCUPANCY+1)])
        self.ax1.tick_params(axis='y', colors=main_accent_color)
        self.ax1.xaxis.label.set_color(main_accent_color)
        self.ax1.set_ylim([-0.1, MAX_OCCUPANCY+0.1])
        self.ax1.set_xticks([0, dataPoints/2, dataPoints])
        self.ax1.set_xticklabels([f'{MINS_HISTORY} Mins ago', f'{int(MINS_HISTORY/2)} Mins ago', 'Now'], y=-0.01)

        self.ax2.clear()
        self.ax2.set_xlim([0, camResX]) # for people positioning set limits of camera resolution
        self.ax2.set_ylim([0, camResY])
        self.ax2.set_title("People Positions")

        self.ax3.clear()
        self.ax3.grid(False)
        self.ax3.tick_params(axis='y', colors='seagreen')
        self.ax3.xaxis.label.set_color('seagreen')
        self.ax3.yaxis.tick_right()
        self.ax3.set_ylim([0, 200])
        self.ax3.set_ylabel("CO2 in ppm")
        self.ax3.set_xticks([0, dataPoints/2, dataPoints])
        self.ax3.set_xticklabels([f'{MINS_HISTORY} Mins ago', f'{int(MINS_HISTORY/2)} Mins ago', 'Now'], y=-0.01)

        self.ax4.clear()

        self.ax5.clear()
        self.ax5.axes.get_xaxis().set_visible(False)
        self.ax5.axes.get_yaxis().set_visible(False)
        self.ax5.set_title("Positions Heatmap")


    def updateHeatmap(self, allPeople):
        if isinstance(heatmapHistory[0], list) :
            for person in heatmapHistory[0]:
                xCoord = person.ImageX // hmPixelSize
                yCoord = person.ImageY // hmPixelSize
                positionHeatmap[xCoord, yCoord] -= 1
        for person in allPeople:
            heatmapX = person.ImageX // hmPixelSize
            heatmapY = person.ImageY // hmPixelSize
            try:
                positionHeatmap[heatmapX, heatmapY] += 1
            except:
                print("OUT OF BOUNDS HEATMAP ERROR")
                print(person.ImageX, person.ImageY)
        
        np.roll(heatmapHistory, -1)
        heatmapHistory[-1] = allPeople  
    
    def toggleImage(self, choice):
        self.imageOn = choice
        self.update_plot(override=True)    


class FirstWindow(Screen, PlottingTools):
    def __init__(self, **kwargs):
        super(FirstWindow, self).__init__(**kwargs)
        super().setupPlots()
        self.startUpdater()
        self.imageOn = 1
    
    def startUpdater(self):
        print("Starting Window 1")
        Clock.schedule_interval(super().update_plot, 2.5)

    def stopUpdater(self):
        print("Stopping Window 1")
        Clock.unschedule(super().update_plot)
    
    def changeScreens(self):
        self.stopUpdater()
        MyApp.room2.startUpdater()

    def openSettings(self):
        get_user_values(alreadyRunning=True)
    

class SecondWindow(Screen, PlottingTools):
    def __init__(self, **kwargs):
        super(SecondWindow, self).__init__(**kwargs)
        super().setupPlots()
        self.imageOn = True

        
    def startUpdater(self):
        print("Starting Window 2")
        Clock.schedule_interval(super().update_plot, 2.5)

    def stopUpdater(self):
        print("Stopping Window 2")
        Clock.unschedule(super().update_plot)

    def changeScreens(self):
        self.stopUpdater()
        MyApp.room1.startUpdater()


class MyApp(App):
    def build(self, **kwargs):
        self.title = "EagleEye Dashboard"
        
        Builder.load_file(kivy_file)

        MyApp.room1 = FirstWindow()
        MyApp.room2 = SecondWindow()
        

        sm = ScreenManager()
        sm.add_widget(MyApp.room1)
        sm.add_widget(MyApp.room2)

        MyApp.room2.startUpdater()
        time.sleep(3)
        MyApp.room2.stopUpdater()

        return sm

# Function to convert person position from fisheye pos to undistorted pos
def calculate_arc_length(pos, radius, centre):
    distFromCentre = pos - centre
    arcLength = radius * np.arcsin(distFromCentre / radius)
    return arcLength

def get_new_data():
    global pplCount
    global co2Data
    global donutData
    i = 0
    while(not dataPaused):
        metaData.ParsePushData(ser)
        
        pplCount = np.roll(pplCount, -1)
        pplCount[-1] = metaData.PeopleCount
        if pplCount[-1] != pplCount[-2]:
            pplCount[-2] += (pplCount[-1]-pplCount[-2])/2

        co2Data = np.roll(co2Data, -1)

        if metaData.PeopleCount <= MAX_OCCUPANCY:
            donutData = [metaData.PeopleCount, MAX_OCCUPANCY-metaData.PeopleCount]
        else:
            donutData = [5,0]

def get_user_values(alreadyRunning=False):

    def assignVals(*args):
        global COM_PORT, BAUD_RATE, HEARTBEAT, MINS_HISTORY, USE_REAL_DATA, MAX_OCCUPANCY

        try:
            COM_PORT = com_port.get()
            BAUD_RATE = int(baud_rate.get())
            HEARTBEAT = int(heartbeat.get())
            MINS_HISTORY = int(mins_history.get())
            MAX_OCCUPANCY = int(max_occupancy.get())
            if use_real_data.get() == "True":
                USE_REAL_DATA = True
            else:
                USE_REAL_DATA = False

            if alreadyRunning:
                serial_port_restart()

        except:
            print("Invalid data input")

    tkWindow = Tk()
    tkWindow.title("EagleEye Settings")
    tkWindow.geometry('270x170')

    com_port = StringVar(tkWindow)
    baud_rate = StringVar(tkWindow)
    heartbeat = StringVar(tkWindow)
    mins_history = StringVar(tkWindow)
    max_occupancy = StringVar(tkWindow)
    use_real_data = StringVar(tkWindow, "True")

    Label(tkWindow, text="Com Port (eg: COM10)", padx=5).grid(row=0)
    Label(tkWindow, text="Baud Rate", padx=5).grid(row=1)
    Label(tkWindow, text="Heartbeat", padx=5).grid(row=2)
    Label(tkWindow, text="Time into past", padx=5).grid(row=3)
    Label(tkWindow, text="Max Occupancy", padx=5).grid(row=4)
    Label(tkWindow, text="Use Real Data", padx=5).grid(row=5)

    com_entry = Entry(tkWindow, textvariable=com_port).grid(row=0, column=1)
    baud_entry = Entry(tkWindow, textvariable=baud_rate).grid(row=1, column=1)
    heartbeat_entry = Entry(tkWindow, textvariable=heartbeat).grid(row=2, column=1)
    mins_history_entry = Entry(tkWindow, textvariable=mins_history).grid(row=3, column=1)
    max_occupancy_entry = Entry(tkWindow, textvariable=max_occupancy).grid(row=4, column=1)
    use_real_data_entry = OptionMenu(tkWindow, use_real_data, "True", "False").grid(row=5, column=1)

    saveButton = Button(tkWindow, text="Save", command=assignVals).grid(row=6,column=0)
    closeButton = Button(tkWindow, text="Close", command=tkWindow.destroy).grid(row=6,column=1)

    mainloop()

def serial_port_restart():
    global metaData, ser, dataPaused
    
    print("Resetting Serial Port")

    dataPaused = True
    # if metaData:
    #     del metaData
    # Toggle True or false to use real or fake generated data - testing only
    # True -> COM Data : False -> Fake data
    if USE_REAL_DATA:
        ser = pdp.InitSerialPort(COM_PORT, BAUD_RATE) #initialise serial port connection as ser
        metaData = pdp.MetaData() # create object from PushDataParser file to store EagleEye data
        metaData.ParsePushData(ser)
    else:
        ser = fdg.InitSerialPort(HEARTBEAT) #initialise serial port connection as ser
        metaData = fdg.MetaData() # create object from fake data file
        metaData.ParsePushData(ser)

    dataPaused = False


# Set constants for camera res
camResX = 640
camResY = 480

# USER DEFINED VARIABLES - set default values
HEARTBEAT = 5 # Time set in EagleEye DesktopApp for time between packets [seconds]
MINS_HISTORY = 30 # Set how far into past data will be shown to
MAX_OCCUPANCY = 5
COM_PORT = 'COM10'
BAUD_RATE = 115200
USE_REAL_DATA = False

dataPaused = False # Used for when switching between com ports in settings menu

# SETUP FOR PLOTS
plt.style.use('seaborn') # colour-scheme
main_accent_color = 'royalblue'

cap_limit_colours = ['orange', 'whitesmoke']
overfilled_colours = ['crimson', 'whitesmoke']
donut_chart_colours = [main_accent_color, 'whitesmoke']
donutData = [0, 5]

# CALCULATE NUM OF DATAPOINTS
dataPoints = int(MINS_HISTORY * (60 / HEARTBEAT)) # calculate no. of points needed
pplCount = np.zeros(dataPoints)

positionHeatmap = np.zeros((16,12))
heatmapHistory = np.empty(dataPoints, dtype=list)
hmPixelSize = 40
hmColourScheme = 'Blues'

# Fake CO2 Data
noise = np.random.normal(0,1,dataPoints)
co2Data = [y + 50*np.sin(0.02*x) + 100 for x, y in enumerate(noise)]

if __name__ == "__main__":
    
    get_user_values()
    print(COM_PORT, BAUD_RATE, HEARTBEAT, MINS_HISTORY, USE_REAL_DATA, MAX_OCCUPANCY)

    # Toggle True or false to use real or fake generated data - testing only
    # True -> COM Data : False -> Fake data
    if USE_REAL_DATA:
        ser = pdp.InitSerialPort(COM_PORT, BAUD_RATE) #initialise serial port connection as ser
        metaData = pdp.MetaData() # create object from PushDataParser file to store EagleEye data
        metaData.ParsePushData(ser)
    else:
        ser = fdg.InitSerialPort(HEARTBEAT) #initialise serial port connection as ser
        metaData = fdg.MetaData() # create object from fake data file
        metaData.ParsePushData(ser)

    # Set up thread to get data in background
    update_data_thread = Thread(target = get_new_data)
    update_data_thread.daemon = True
    update_data_thread.start()


    MyApp().run()

"""
TODO:
    + Change font to Barlow
"""
