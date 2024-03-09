import serial
import pandas as pd
import numpy as np
from getSerialData import *
import matplotlib.pyplot as plt


# Open serial connection to the Arduino (adjust port and baud rate as needed)
# ser = serial.Serial('/dev/tty.usbserial-1110', 115200, timeout=1)


BYTES_TO_READ = 1

def getSerialData(ser):
    print(ser)
    byte_read = ser.read(BYTES_TO_READ)
    # print(byte_read, type(byte_read))

    while (byte_read):
        try:
            byte_char = byte_read.decode('ascii')
            if byte_char == "[":

                data = ser.read_until(b']')[:-1]

                data = data.decode('ascii')

                # print(data)
                return (data.split(","))
            
            byte_read = ser.read(BYTES_TO_READ)

        
        except:
            print(f"[Decode] Not ASCII... => byte read: {byte_read}")
            byte_read = ser.read(BYTES_TO_READ)

data_file = "ESP_Output.xlsx"

def plotInterrupts(df):

    # specifying the plot size
    plt.figure(figsize = (20, 5))

    plt.hist(df['datapoints'], bins=100, color='blue', edgecolor='black', alpha=0.7)

    # for interrupt_time in df['datapoints']:
    #     print(interrupt_time)
    #     # only one line may be specified; full height
    #     plt.axvline(x = interrupt_time, color = 'b', linestyle='-', linewidth=1)
    #     # plt.xscale('linear')
    #     # plt.xlim(0,30000)

    # rendering plot
    plt.show()


def collectRawData(ser, write_to_excel=False):
    # ser = InitSerialPort('/dev/tty.usbserial-1110', 115200)

    raw_data = getSerialData(ser)

    # data = [int(y.split(',')) for y in raw_data]
    data = [int(x) for x in raw_data]
    print(f"Num interrupt times: {len(data)}")

    df = pd.DataFrame({'datapoints': raw_data})

    if write_to_excel:
        df.to_excel(data_file, index=False)
        print("Completed write to excel file...")

    return (df)

if __name__=="__main__":
    ser = InitSerialPort('COM8', 115200)

    df = collectRawData(ser, True)

    plotInterrupts(df)

