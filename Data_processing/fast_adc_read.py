import serial
import struct
import numpy as np
import time

# Open serial connection to the Arduino (adjust port and baud rate as needed)
ser = serial.Serial('/dev/tty.usbserial-1110', 115200, timeout=1)

# Define the size of the matrix
num_rows = 2
num_cols = 1000

while(1):
    try:
        # Read the raw bytes from serial
        raw_data = ser.read(num_rows * num_cols * 2)  # Assuming int is 2 bytes

        # Unpack the received data into a NumPy array
        # sensor_data = np.array(struct.unpack('>' + 'h' * (num_rows * num_cols), raw_data)).reshape((num_rows, num_cols))

        # Print or process the received data
        print(raw_data)

    except:
        print("################# ERROR #######################")

    time.sleep(1)