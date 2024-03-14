import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

data_file = "ESP_Output.xlsx"

data = pd.read_excel(data_file)["datapoints"]
zeroes = np.zeros(len(data))

plt.figure()

plt.plot(data,zeroes, 'o')
plt.show()