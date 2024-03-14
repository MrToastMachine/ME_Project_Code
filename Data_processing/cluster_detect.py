import numpy as np
from sklearn.cluster import DBSCAN
from sklearn.preprocessing import StandardScaler
import random
import pandas as pd
import matplotlib.pyplot as plt

# Replace this with your actual list of integers
# data = np.array([random.randint(0, 30000) for _ in range(100)]).reshape(-1, 1)

data = pd.read_excel("ESP_OUTPUT_01.xlsx")['datapoints'][:-1]

data = data.to_numpy().reshape(-1,1)

# Preprocess the data (optional, but can be helpful)
scaler = StandardScaler()
data_scaled = scaler.fit_transform(data)

# Apply DBSCAN
eps = 0.5  # Adjust the epsilon value based on your data
min_samples = 30  # Adjust the minimum number of samples in a cluster
dbscan = DBSCAN(eps=eps, min_samples=min_samples)
clusters = dbscan.fit_predict(data_scaled)

# Count clusters
unique_clusters, cluster_counts = np.unique(clusters, return_counts=True)

# Filter clusters based on a minimum size threshold
min_cluster_size = 10  # Adjust the minimum size of a cluster
filtered_clusters = unique_clusters[cluster_counts >= min_cluster_size]

# Print the filtered clusters
print(f"Detected {len(filtered_clusters)} pulses with size greater than {min_cluster_size}:")
print(filtered_clusters)

# Visualize the clusters (optional)
plt.scatter(data, [1] * len(data), c=clusters, cmap='viridis')
plt.title('DBSCAN Clustering of Integer Dataset')
plt.xlabel('Values')
plt.show()
