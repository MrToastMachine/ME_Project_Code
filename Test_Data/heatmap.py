# import numpy as np

# RESOLUTION = (160,160)

# heatmap = np.zeros(RESOLUTION)

import numpy as np
import matplotlib.pyplot as plt
import matplotlib.patches as patches
from BoardInfo import *
from scrapeTestData import *

ROOM_SIZE = (1.6, 1.6)

b1 = Board(1, (1.6,0), np.pi)
b2 = Board(2, (0, 0), np.pi/2)
b3 = Board(3, (0,1.6), 0)


def update_heatmap(Z, X, Y, sensor_position, min_radius, sensor_angle):
    # Calculate the relative positions to the sensor's origin
    relative_X = X - sensor_position[0]
    relative_Y = Y - sensor_position[1]
    
    min_angle = sensor_angle - (np.pi/12)
    max_angle = sensor_angle + (np.pi/12)

    # Convert relative positions to polar coordinates
    R = np.sqrt(relative_X**2 + relative_Y**2)
    Theta = np.arctan2(relative_Y, relative_X)

    default_obj_size = 0.2

    max_radius = min_radius + default_obj_size

    # Increment the heatmap values where conditions are met
    condition = (R >= min_radius) & (R <= max_radius) & ((Theta >= min_angle) & (Theta <= max_angle))
    Z[condition] += 1
    return Z

def create_heatmap(resolution):
    # Define the resolution of the heatmap
    x = np.linspace(0, ROOM_SIZE[0], resolution)
    y = np.linspace(0, ROOM_SIZE[1], resolution)
    X, Y = np.meshgrid(x, y)
    Z = np.zeros_like(X)
    
    # # Convert grid to polar coordinates
    # R = np.sqrt(X**2 + Y**2)
    # Theta = np.arctan2(Y, X) * 180 / np.pi  # Convert to degrees

    for sensor in b1.all_sensors:
        # sensor.printInfo()
        for i in range(num_runs):
            for j in range(len(sensor.detections)):
                Z = update_heatmap(Z, X, Y, (sensor.posX, sensor.posY), sensor.detections[i], sensor.angle)
                
    for sensor in b2.all_sensors:
        # sensor.printInfo()
        for i in range(num_runs):
            for j in range(len(sensor.detections)):
                Z = update_heatmap(Z, X, Y, (sensor.posX, sensor.posY), sensor.detections[i], sensor.angle)
                
    for sensor in b3.all_sensors:
        # sensor.printInfo()
        for i in range(num_runs):
            for j in range(len(sensor.detections)):
                Z = update_heatmap(Z, X, Y, (sensor.posX, sensor.posY), sensor.detections[i], sensor.angle)
                


    return X, Y, Z

test_dir = 'Test_Data/'
# Example usage
file_path = test_dir + 'filtered_test1.txt'  # Specify the path to your file here
sensor_data = extract_sensor_data(file_path)

b1 = Board(1, (1.6,0), np.pi)
b2 = Board(2, (0, 0), np.pi/2)
b3 = Board(3, (0,1.6), 0)

num_runs = 5

for reading in sensor_data[:num_runs]:
    # data = reading['board_01']['Sensor A']
    b1.sensorA.loadTestData(reading['board_01']['Sensor A'])
    b1.sensorB.loadTestData(reading['board_01']['Sensor B'])
    b1.sensorC.loadTestData(reading['board_01']['Sensor C'])

    b2.sensorA.loadTestData(reading['board_02']['Sensor A'])
    b2.sensorB.loadTestData(reading['board_02']['Sensor B'])
    b2.sensorC.loadTestData(reading['board_02']['Sensor C'])

    b3.sensorA.loadTestData(reading['board_03']['Sensor A'])
    b3.sensorB.loadTestData(reading['board_03']['Sensor B'])
    b3.sensorC.loadTestData(reading['board_03']['Sensor C'])

resolution = 500

# Create the heatmap
X, Y, Z = create_heatmap(resolution)

# Plotting
fig, ax = plt.subplots()
heatmap = ax.pcolormesh(X, Y, Z, shading='auto', cmap='Greens')
ax.set_aspect('equal', 'box')
ax.set_xlim([0, 1.6])
ax.set_ylim([0, 1.6])

# Draw the sector for visual confirmation
# wedge = patches.Wedge(center=(0, 0), r=max_radius, theta1=min_angle, theta2=max_angle, facecolor='none', edgecolor='blue', ls='--', lw=1.5)
# ax.add_patch(wedge)

plt.colorbar(heatmap)
plt.title("Sensor Detection Heatmap")
plt.show()

