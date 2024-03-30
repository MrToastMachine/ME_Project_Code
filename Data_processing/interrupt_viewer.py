import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

data_file = "ESP_Output_01.xlsx"

data = pd.read_excel(data_file)["datapoints"]
zeroes = np.zeros(len(data))

scaled_data = (data) / 1000

plt.figure()
plt.scatter(scaled_data,zeroes, c='g', marker='|',s=700)
plt.xlim(-3,30)
plt.title("Interrupt Timings (Pre-Clustering)", fontsize=18)
plt.xlabel("Time (ms)",fontsize=12, x=1.0)
plt.ylabel("Interrupt triggers",fontsize=14)
plt.legend(["Interrupt Triggered"], loc="best")
plt.yticks([])
plt.grid()
plt.show()