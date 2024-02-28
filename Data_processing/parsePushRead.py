from getSerialData import *
import pandas as pd
import matplotlib.pyplot as plt

BYTES_TO_READ = 1


def getSerialData(ser):
    byte_read = ser.read(BYTES_TO_READ)
    # print(byte_read, type(byte_read))

    while (byte_read):
        try:
            byte_char = byte_read.decode('ascii')
            if byte_char == "[":
                realDist = ser.read_until(b';')[:-1].decode('ascii')

                data = ser.read_until(b']')[:-1]

                data = data.decode('ascii')

                # print(data)
                return (realDist, data.split(";"))
            
            byte_read = ser.read(BYTES_TO_READ)

        
        except:
            print(f"[Decode] Not ASCII... => byte read: {byte_read}")
            byte_read = ser.read(BYTES_TO_READ)



def plotData(df):

    plt.plot(df['ts'], df['datapoints'], linestyle= '-', color='b')

    # Set labels and title
    plt.xlabel('Timestamp')
    plt.ylabel('Data')
    plt.title('Plot of Data over Time')
    plt.grid(True)

    # Show the plot
    plt.show()


data_file = "ESP_Output.xlsx"

def collectRawData(ser, write_to_excel=False):
    # ser = InitSerialPort('/dev/tty.usbserial-1110', 115200)

    real_dist, raw_data = getSerialData(ser)

    ts = [int(x.split(',')[0]) for x in raw_data]
    data = [int(y.split(',')[1]) for y in raw_data]

    df = pd.DataFrame({'ts': ts, 'datapoints': data})

    if write_to_excel:
        df.to_excel(data_file, index=False)
        print("Completed write to excel file...")

    return (float(real_dist), df)

if __name__=="__main__":
    ser = InitSerialPort('/dev/tty.usbserial-1110', 115200)

    df = collectRawData(ser)

    plotData(df)
