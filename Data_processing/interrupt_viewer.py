import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

data_file = "ESP_Output.xlsx"

data = pd.read_excel(data_file)["datapoints"]
zeroes = np.zeros(len(data))

scaled_data = (data+500) / 1000

plt.figure()
plt.plot(scaled_data,zeroes, 'g.')
plt.xlim(-3,30)
plt.title("ESP32 Interrupt Trigger Timings", fontsize=18)
plt.xlabel("Time (ms)",fontsize=12, x=1.0)
plt.ylabel("Interrupt triggers",fontsize=14)
plt.legend(["Interrupt Triggered"])
plt.yticks([])
plt.grid()
plt.show()