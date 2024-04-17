import pandas as pd
from BoardInfo import *

def scrapeData(input_filename):
    with open(input_filename, 'r') as infile:
        reading_num = 0
        for line in infile:
            if line.startswith("Data collected from all boards"):
                reading_num += 1


def extract_sensor_data(filename):
    # Initialize data structure to hold the test results
    test_data = []

    # Open the file for reading
    with open(filename, 'r') as file:
        # Temporary storage for current test's data
        current_test = {}
        current_board = None

        # Process each line in the file
        for line in file:
            line = line.strip()
            if 'Data collected from all boards' in line:
                # If starting a new test, save the previous test and start fresh
                if current_test:
                    test_data.append(current_test)
                    current_test = {}
            elif 'Data from board' in line:
                # Start new board section
                board_id = line.split()[-1].strip(':')
                current_board = f'board_{board_id}'
                current_test[current_board] = {'Sensor A': [], 'Sensor B': [], 'Sensor C': []}
            elif 'Sensor' in line:
                # Process sensor lines
                sensor_id = line.split()[1]
            elif ':' in line:
                # Process data lines
                value, count = line.split(':')
                value = float(value.strip())
                count = int(count.strip())
                current_test[current_board][f'Sensor {sensor_id}'].append((value, count))

        # Append the last test if not already added
        if current_test:
            test_data.append(current_test)

    return test_data

if __name__=="__main__":
    test_num = 10

    test_dir = 'Test_Data/'
    # Example usage
    file_path = test_dir + f'filtered_test{test_num}.txt'  # Specify the path to your file here
    sensor_data = extract_sensor_data(file_path)

    df = pd.DataFrame(sensor_data)

    all_data = pd.DataFrame(sensor_data)
    df.to_excel(test_dir + f'TEST0{test_num}_READINGS.xlsx')



# print(sensor_data)  # Prints out the extracted data

            