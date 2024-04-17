# import numpy as np

# RESOLUTION = (160,160)

# heatmap = np.zeros(RESOLUTION)

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import matplotlib.patches as patches
from BoardInfo import *
from scrapeTestData import *

##################### TUNING PARAMETERS ########################
ROOM_SIZE = (1.6, 1.6)
delta_from_norm = 14.5 * (2*np.pi / 360) # FOV of sensors
default_obj_size = 0.2 #estmated object diameter
num_runs = 5 # num readings to add to plot

# Board init setup
b1 = Board(1, (1.6,0), np.pi)
b2 = Board(2, (0, 0), np.pi/2)
b3 = Board(3, (0,1.6), 0)


def update_heatmap(Z, X, Y, sensor_position, min_radius, sensor_angle, add):
    # Calculate the relative positions to the sensor's origin
    relative_X = X - sensor_position[0]
    relative_Y = Y - sensor_position[1]

    
    min_angle = sensor_angle - delta_from_norm
    max_angle = sensor_angle + delta_from_norm

    # Convert relative positions to polar coordinates
    R = np.sqrt(relative_X**2 + relative_Y**2)
    Theta = np.arctan2(relative_Y, relative_X)

    max_radius = min_radius + default_obj_size

    # Increment the heatmap values where conditions are met
    condition = (R >= min_radius) & (R <= max_radius) & ((Theta >= min_angle) & (Theta <= max_angle))
    Z[condition] = Z[condition] + 1 if add else Z[condition] - 1 
    return Z

def create_heatmap(X, Y, Z, resolution, add=True):
    
    # # Convert grid to polar coordinates
    # R = np.sqrt(X**2 + Y**2)
    # Theta = np.arctan2(Y, X) * 180 / np.pi  # Convert to degrees

    for sensor in b1.all_sensors:
        # sensor.printInfo()
        # for i in range(num_runs):
        for j in range(len(sensor.detections)):
            Z = update_heatmap(Z, X, Y, (sensor.posX, sensor.posY), sensor.detections[j], sensor.angle, add)
                
    for sensor in b2.all_sensors:
        # sensor.printInfo()
        # for i in range(num_runs):
            # print(sensor.sensor_id)
        for j in range(len(sensor.detections)):
            Z = update_heatmap(Z, X, Y, (sensor.posX, sensor.posY), sensor.detections[j], sensor.angle, add)
                
    for sensor in b3.all_sensors:
        # sensor.printInfo()
        # for i in range(num_runs):
        for j in range(len(sensor.detections)):
            Z = update_heatmap(Z, X, Y, (sensor.posX, sensor.posY), sensor.detections[j], sensor.angle, add)
                
    return X, Y, Z

def loadSensorData(sensor_data):

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


############## Load Test Data and background data ###############

def heatmap_generator(main_data_file, bg_data_file=''):

    ######## Heatmap Grid Definitions ##########
    resolution = 500
    # Define the resolution of the heatmap
    x = np.linspace(0, ROOM_SIZE[0], resolution)
    y = np.linspace(0, ROOM_SIZE[1], resolution)
    X, Y = np.meshgrid(x, y)
    Z = np.zeros_like(X)
    test_dir = 'Test_Data/' # Folder holing all test data
    
    # main data file
    file_path = test_dir + main_data_file  # Specify the path to your file here
    sensor_data = extract_sensor_data(file_path)

    if bg_data_file != '':
        # background data file
        bg_file_path = test_dir + bg_data_file
        bg_sensor_data = extract_sensor_data(bg_file_path)

        # subtract background data
        loadSensorData(bg_sensor_data)
        X, Y, Z = create_heatmap(X, Y, Z, resolution, add=False)

    # clear distances stored in sensors
    b1.clearSensorData()
    b2.clearSensorData()
    b3.clearSensorData()

    # add test object data
    loadSensorData(sensor_data)
    X, Y, Z = create_heatmap(X, Y, Z, resolution, add=True)

    return X, Y, Z


############################### CENTROID CALCULATIONS ######################################

def find_centroid_of_hottest_area(Z):
    # Find the maximum value in the heatmap
    max_value = np.max(Z)
    # Find all indices where the heatmap's value equals the maximum value
    max_points = np.argwhere(Z == max_value)
    # Compute the centroid of these points
    centroid_idx = np.mean(max_points, axis=0).astype(int)
    return centroid_idx

test_results = []

# for i in range(1, 8):
if(0):
    main_file = f'filtered_test{i}.txt'

    X, Y, Z = heatmap_generator(main_file)

    # Find the centroid of the hottest area
    centroid_idx = find_centroid_of_hottest_area(Z)
    centroid_coordinates = (X[centroid_idx[0], centroid_idx[1]], Y[centroid_idx[0], centroid_idx[1]])

    # print("Centroid index:", centroid_idx)
    print(f"Centroid test_0{i}:", centroid_coordinates)

    test_results.append(centroid_coordinates)

# pd.DataFrame(test_results).to_excel('ALL_TEST_RESULTS.xlsx')




main_file = 'filtered_test8.txt'
bg_data_file = 'filtered_test7.txt'
X, Y, Z = heatmap_generator(main_file,bg_data_file)


# Find the centroid of the hottest area
centroid_idx = find_centroid_of_hottest_area(Z)
centroid_coordinates = (X[centroid_idx[0], centroid_idx[1]], Y[centroid_idx[0], centroid_idx[1]])

# print("Centroid index:", centroid_idx)
print("Centroid coordinates:", centroid_coordinates)

########################## PLOTTING ##############################

show_heatmap = False
if show_heatmap:
    # Plotting
    fig, ax = plt.subplots()
    heatmap = ax.pcolormesh(X, Y, Z, shading='auto', cmap='Greens')
    ax.set_aspect('equal', 'box')
    ax.set_xlim([0, 1.6])
    ax.set_ylim([0, 1.6])

    for s in b1.all_sensors:
        ax.scatter(s.posX, s.posY, color='blue', s=20)
    for s in b2.all_sensors:
        ax.scatter(s.posX, s.posY, color='blue', s=20)
    for s in b3.all_sensors:
        ax.scatter(s.posX, s.posY, color='blue', s=20)

    plt.xlabel('X coordinate [m]')
    plt.ylabel('Y coordinate [m]')



    # plt.colorbar(heatmap)
    plt.title("Sensor Detection Heatmap [Background Subtraction]")
    plt.show()

plot_centroid_heatmap = True
if plot_centroid_heatmap:
    # Plotting the heatmap and the centroid
    fig, ax = plt.subplots()
    heatmap = ax.pcolormesh(X, Y, Z, shading='auto', cmap='Greens')
    ax.scatter(centroid_coordinates[0], centroid_coordinates[1], color='red', s=100, edgecolor='black', label='Centroid of Highest Detections')

    for s in b1.all_sensors:
        ax.scatter(s.posX, s.posY, color='blue', s=20)
    for s in b2.all_sensors:
        ax.scatter(s.posX, s.posY, color='blue', s=20)
    for s in b3.all_sensors:
        ax.scatter(s.posX, s.posY, color='blue', s=20)

    ax.set_xlabel('X coordinate [m]')
    ax.set_ylabel('Y coordinate [m]')
    ax.set_aspect('equal', 'box')

    ax.legend()

    # plt.colorbar(heatmap)
    plt.title("Sensor Detection Heatmap [Background Subtraction]")
    plt.show()
