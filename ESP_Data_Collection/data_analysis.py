# https://colab.research.google.com/drive/1xWozRQ7DyaocAg4hIf6jbn5tiTUT_CBk#scrollTo=IQUAI0Xh95DJ

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from scipy import signal

from mpltools import layout

dataframe = pd.read_excel('ESP_Output.xlsx')
sensor_data = dataframe['datapoints'].to_numpy()

Fs = 100000

num_datapoints = len(sensor_data)
secs_of_data = num_datapoints/(Fs)
# print(f"{secs_of_data} minutes of data available")


raw_freqs, raw_welchperiodogram = signal.welch(sensor_data, Fs, 'hamming', nperseg=1024, detrend=False)

plt.figure(figsize = (10,6)) # 10 in by 6 in
plt.subplot(211)
plt.plot(sensor_data) # Show 5.6 seconds of data
plt.title("ECG Data", color ="purple")
plt.ylabel('$\mu$ volts', fontsize=14, color="blue", weight="bold")
plt.xlabel('$n$', fontsize=14, color="blue", weight="bold",  x=1.0)
layout.cross_spines(zero_cross=True)
# plt.grid(True)

plt.subplot(212)
plt.plot(raw_freqs, 20*np.log10(raw_welchperiodogram))
plt.title("Input Magnitude Spectrum", color ="purple")
plt.ylabel('$|X(k)|^2$dB', fontsize=14, color="blue", weight="bold")
plt.xlabel('$F$Hz', fontsize=14, color="blue", weight="bold",  x=1.0)
# plt.xticks([0,5,15,90,120,150])
plt.tight_layout() # ensure sufficient spacing between subplots
plt.grid(True)

plt.show()


### HIGH PASS

deltaHPF = 500 # Transition Bandwidth in Hz
HPPassbandF = 35000  # Passband Edge Frequency in Hz
FcHP = HPPassbandF - deltaHPF/2   # Cutoff Frequency in Hz

# Blackman
M_blackman = int(np.ceil(5.5 * Fs/deltaHPF)) # Filter Length for Blackman Window
M_blackman = M_blackman + 1 if M_blackman % 2 == 0 else M_blackman # Ensure filter length is odd
print(f"M_blackman = {M_blackman}")

MidM_blackman = int((M_blackman-1)/2)
print(f"MidM_blackman = {MidM_blackman}")

ncoeffHP_blackman = signal.firwin(M_blackman, FcHP, window = 'blackman', fs = Fs, pass_zero=False)
                                  
w_blackman, HWHP_blackman = signal.freqz(ncoeffHP_blackman, fs = Fs)

ecg_HPoutput = signal.lfilter(ncoeffHP_blackman, [1.0], sensor_data)

f_HP, ecg_HPoutputwelch =  signal.welch(ecg_HPoutput, Fs, 'blackman', nperseg=1024, detrend=False)

plt.figure(2, figsize = (10,6)) # 10 in by 6 in
plt.subplot(211)
plt.plot(ecg_HPoutput)
plt.title("High Pass Filter Output", color ="purple")
plt.ylabel('$\mu$ volts', fontsize=14, color="blue", weight="bold")
plt.xlabel('$n$', fontsize=14, color="blue", weight="bold",  x=1.0)
plt.grid(True)
layout.cross_spines(zero_cross=True)

plt.subplot(212)
plt.plot(f_HP, 20*np.log10(ecg_HPoutputwelch))
plt.title("High Pass Output Magnitude Spectrum [Blackman]", color ="purple")
plt.ylabel('$|Y(k)|^2$dB', fontsize=14, color="blue", weight="bold")
plt.xlabel('$F$Hz', fontsize=14, color="blue", weight="bold",  x=1.0)
# plt.xticks([5,15,90,120,150])
# plt.axis([0, 125,-120,50])
plt.grid(True)
plt.tight_layout() # ensure sufficient spacing between subplots
plt.show()