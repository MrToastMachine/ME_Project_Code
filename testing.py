import numpy as np
import matplotlib.pyplot as plt
import matplotlib.patches as patches

def update_heatmap(Z, X, Y, sensor_position, min_radius, max_radius, min_angle, max_angle):
    # Calculate the relative positions to the sensor's origin
    relative_X = X - sensor_position[0]
    relative_Y = Y - sensor_position[1]
    
    # Convert relative positions to polar coordinates
    R = np.sqrt(relative_X**2 + relative_Y**2)
    Theta = np.arctan2(relative_Y, relative_X) * 180 / np.pi  # Convert to degrees
    

    # Increment the heatmap values where conditions are met
    condition = (R >= min_radius) & (R <= max_radius) & ((Theta >= min_angle) & (Theta <= max_angle))
    Z[condition] += 1
    return Z

def create_heatmap(resolution, sensors):
    # Determine plot limits
    max_x = max(sensor[0][0] + sensor[1] for sensor in sensors)
    max_y = max(sensor[0][1] + sensor[1] for sensor in sensors)
    min_x = min(sensor[0][0] - sensor[1] for sensor in sensors)
    min_y = min(sensor[0][1] - sensor[1] for sensor in sensors)

    x = np.linspace(min_x, max_x, resolution)
    y = np.linspace(min_y, max_y, resolution)
    X, Y = np.meshgrid(x, y)
    Z = np.zeros_like(X)

    # Update heatmap for each sensor's data
    for sensor in sensors:
        sensor_position, min_radius, max_radius, min_angle, max_angle = sensor
        Z = update_heatmap(Z, X, Y, sensor_position, min_radius, max_radius, min_angle, max_angle)

    return X, Y, Z

# Define sensor parameters as tuples (position, min_radius, max_radius, min_angle, max_angle)
sensors = [
    # Position, min_r, max_r, min_ang, max_ang
    ((0, 0), 1.04, 1.24, 0, 30),   # Sensor 1 at origin
    ((2, 2), 0.5, 0.75, 10, 40),   # Sensor 2 at (2, 2)
    ((-1, 1), 1.0, 1.5, 20, 50)    # Sensor 3 at (-1, 1)
]
resolution = 500  # Resolution of the heatmap

# Create the heatmap
X, Y, Z = create_heatmap(resolution, sensors)

# Plotting
fig, ax = plt.subplots()
heatmap = ax.pcolormesh(X, Y, Z, shading='auto', cmap='hot')
ax.set_aspect('equal', 'box')
ax.set_xlim([min(X[0]), max(X[0])])
ax.set_ylim([min(Y[:,0]), max(Y[:,0])])

plt.colorbar(heatmap)
plt.title("Sensor Detection Heatmap with Different Origins")
plt.show()
