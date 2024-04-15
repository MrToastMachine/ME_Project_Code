import numpy as np
import pandas as pd

test_dir = 'Test_Data/'

def filter_lines(input_filename, output_filename):
    # Open the input file in read mode and the output file in write mode
    with open(input_filename, 'r') as infile, open(output_filename, 'w') as outfile:
        # Iterate over each line in the input file
        for line in infile:
            # Strip any leading/trailing whitespace from the line
            stripped_line = line.strip()
            # Check if the line starts with a number, specified words, or is blank
            if (stripped_line.startswith(('Sensor', 'Data')) or
                stripped_line == "" or
                stripped_line[0].isdigit()):
                # Write the line to the output file
                outfile.write(line)

# Example usage
# filter_lines(test_dir + 'test1.txt')

for i in range(1, 11):
    input_file = 'test' + str(i) + '.txt'
    output_file = 'filtered_' + input_file
    
    filter_lines(test_dir + input_file, test_dir + output_file)
    print("Finished file " + input_file)

