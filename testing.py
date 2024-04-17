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

    x = np.linspace(0, 2, resolution)
    y = np.linspace(0, 2, resolution)
    X, Y = np.meshgrid(x, y)
    Z = np.zeros_like(X)

    # Update heatmap for each sensor's data
    for sensor in sensors:
        sensor_position, min_radius, max_radius, min_angle, max_angle = sensor
        Z = update_heatmap(Z, X, Y, sensor_position, min_radius, max_radius, min_angle, max_angle)

    return X, Y, Z

# Define sensor parameters as tuples (position, min_radius, max_radius, min_angle, max_angle)
sensors = [
    ((0, 0), 1.04, 1.24, 30, 60),   # Sensor 1 at origin
    ((2, 0), 1.1, 1.3, 120, 150),   # Sensor 2 at (2, 2)
    # ((-1, 1), 1.0, 1.5, 20, 50)    # Sensor 3 at (-1, 1)
]
resolution = 500  # Resolution of the heatmap

# Create the heatmap
X, Y, Z = create_heatmap(resolution, sensors)

# Plotting
fig, ax = plt.subplots()
heatmap = ax.pcolormesh(X, Y, Z, shading='auto', cmap='Greens')
ax.set_aspect('equal', 'box')
ax.set_xlim([0, 2])
ax.set_ylim([0, 2])

plt.colorbar(heatmap)
plt.title("Heatmap example")
plt.show()
