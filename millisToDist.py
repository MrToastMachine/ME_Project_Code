import numpy as np
import matplotlib.pyplot as plt

# Define the function
def f(x):
    dist_in_meters = (340/2) * x * 1e-3 # convert from ms to m for formula
    return dist_in_meters * 100 # convert to cm


len_ms = 30
# Generate x values in the specified range
x_values = np.linspace(0, len_ms, 30)

# Calculate corresponding y values using the function
y_values = f(x_values)

# Plot the function
plt.plot(x_values, y_values, label=r'$f(x) = x^2 + 3$')

# Add labels and title
plt.xlabel('Time of Reflection (ms)')
plt.ylabel('Distance (cm)')
plt.title('Converting reflection time to distance')
plt.xticks([x for x in range(len_ms)])
plt.yticks([y*50 for y in range(10)])
plt.grid()

# Show the plot
plt.show()
