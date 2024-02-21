# https://colab.research.google.com/drive/1xWozRQ7DyaocAg4hIf6jbn5tiTUT_CBk#scrollTo=IQUAI0Xh95DJ

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from scipy import signal
from parsePushRead import *
from getSerialData import *
from mpltools import layout

ser = 0

real_dist = 0.0
raw_data = []

def highpassFilter(data, cutoff, trans_bw, Fs):
    ### PRE HIGH PASS 

    # delta_f = 3000 -> trans_bw
    # pre_cutoff = 5000 -> cutoff
    fc_half = cutoff - trans_bw/2

    # Hamming
    pre_hamming = int(np.ceil(3.3 * Fs/trans_bw)) # Filter Length for Hamming Window

    pre_hamming = pre_hamming + 1 if pre_hamming % 2 == 0 else pre_hamming # Ensure filter length is odd

    MidM_pre_hamming = int((pre_hamming-1)/2)

    ncoeffHP_hamming = signal.firwin(pre_hamming, fc_half, window = 'hamming', fs = Fs, pass_zero=False)

    sensor_data_pre_filtered = signal.lfilter(ncoeffHP_hamming, [1.0], data)

    output_no_delay = sensor_data_pre_filtered[MidM_pre_hamming:len(data)+MidM_pre_hamming]

    return output_no_delay

def bandpassFilter(data, centre_freq, bandwidth, trans_bw, Fs):
    # BAND-PASS SPECS

    # centre_freq = 40000 
    # bandwidth = 2000
    # transition_bw = 1000


    ############## HIGH PASS ################

    HPPassbandF = centre_freq - bandwidth/2  # Passband Edge Frequency in Hz
    FcHP = HPPassbandF - trans_bw/2   # Cutoff Frequency in Hz

    # Hamming
    M_hamming = int(np.ceil(3.3 * Fs/trans_bw)) # Filter Length for Hamming Window

    M_hamming = M_hamming + 1 if M_hamming % 2 == 0 else M_hamming # Ensure filter length is odd
    # print(f"M_hamming = {M_hamming}")

    MidM_HP = int((M_hamming-1)/2)
    # print(f"MidM_hamming = {MidM_hamming}")

    ncoeffHP_hamming = signal.firwin(M_hamming, FcHP, window = 'hamming', fs = Fs, pass_zero=False)

    # apply filter
    sensor_HPoutput = signal.lfilter(ncoeffHP_hamming, [1.0], data)


    ############### LOW PASS ################

    LPPassbandF = centre_freq + bandwidth/2  # Passband Edge Frequency in Hz
    FcLP = LPPassbandF + trans_bw/2   # Cutoff Frequency in Hz

    MLP = int(np.ceil(3.3 * Fs/trans_bw)) # Calculate filter length M
    MLP = MLP + 1 if MLP % 2 == 0 else MLP # Ensure that filter length is odd
    MidM_LP = int((MLP-1)/2) #Filter Midpoint

    # Calculate FIR filter coefficients
    ncoeffLP = signal.firwin(MLP, FcLP, window = 'hamming', fs = Fs, pass_zero=True)

    # Apply Low pass filter to already high pass filtered signal
    sensor_LPoutput = signal.lfilter(ncoeffLP, [1.0], sensor_HPoutput)

    # remove delay introduced by filter
    output_no_delay = sensor_LPoutput[MidM_HP+MidM_LP:len(data)+MidM_HP+MidM_LP]

    print(f"bandpassed filtered data length: {len(output_no_delay)}")

    return output_no_delay

def getSpectrum(signal, Fs):

    raw_freqs, raw_welchperiodogram = signal.welch(signal, Fs, 'hamming', nperseg=512, detrend=False)

    return(raw_freqs, raw_welchperiodogram)


def getSensorData(read_excel=False):
    global real_dist
    global raw_data
    global ser

    if read_excel:
        dataframe = pd.read_excel('ESP_Output.xlsx')
    else:
        if not ser:
            ser = InitSerialPort('/dev/tty.usbserial-1110', 115200)

        real_dist, dataframe = collectRawData(ser, write_to_excel=True)

    raw_data = dataframe['datapoints'].to_numpy()
    # return raw_data

    Fs = 100000
    bp_centre_freq = 40000
    bp_bandwidth = 4000
    bp_trans_width = 1000

    pre_filtered = highpassFilter(raw_data, 5000, 3000, Fs)
    data_post_filtering = bandpassFilter(pre_filtered, bp_centre_freq, bp_bandwidth, bp_trans_width, Fs)

    return data_post_filtering

def getFilteredData():
    Fs = 100000
    sensor_data = getSensorData()

    bp_centre_freq = 40000
    bp_bandwidth = 4000
    bp_trans_width = 1000

    pre_filtered = highpassFilter(sensor_data, 5000, 3000, Fs)
    data_post_filtering = bandpassFilter(pre_filtered, bp_centre_freq, bp_bandwidth, bp_trans_width, Fs)

    return data_post_filtering

def livePlot():
    plt.ion()

    real_dist_n = (2 * real_dist/100) / (340 * 1e-5)

    print(f"Real Distance: {real_dist} cm")
    print(f"Corresponding sample: {real_dist_n}")

    graph = plt.plot(filtered_data, color='g')[0]
    plt.plot(real_dist_n, 0, 'ro')
    plt.grid(True)
    plt.ylim(-7,7)
    plt.pause(0.25)

    while True:
        filtered_data = getFilteredData()
        real_dist_n = (2 * real_dist/100) / (340 * 1e-5)
        print(f"Real Distance: {real_dist} cm")
        print(f"Corresponding sample: {real_dist_n}")
        
        graph.remove()

        graph = plt.plot(filtered_data, color='g')[0]
        plt.plot(real_dist_n, 0, 'ro')

        plt.show()

        plt.pause(0.25)


filtered_data = getSensorData(False)
print(f"Real Distance = {real_dist}")


plt.figure(figsize = (10,6)) # 10 in by 6 in
plt.subplot(211)
plt.plot(raw_data, linestyle= '-', color='b')

# Set labels and title
plt.xlabel('Sample number')
plt.ylabel('Data')
plt.title('Raw Data')
plt.grid(True)


# Plot output signal and frequency content of filtered signal
plt.subplot(212)
plt.plot(filtered_data)
plt.title("Low Pass Filter Output", color ="purple")
plt.ylabel('$\mu$ volts', fontsize=14, color="blue", weight="bold")
plt.xlabel('$n$', fontsize=14, color="blue", weight="bold",  x=1.0)
layout.cross_spines(zero_cross=True)
# plt.ylim(-8,8)
plt.grid(True)

# plt.subplot(212)
# plt.plot(f, 20*np.log10(sensor_LPoutputwelch))
# plt.title("Low Pass Output Magnitude Spectrum", color ="purple")
# plt.ylabel('$|Y(k)|^2$dB', fontsize=14, color="blue", weight="bold")
# plt.xlabel('$F$Hz', fontsize=14, color="blue", weight="bold",  x=0.98)
# # plt.xticks([5,15])
# # plt.axis([0, 125,-120,50])
# plt.grid(True)
plt.tight_layout() # ensure sufficient spacing between subplots

plt.show()
