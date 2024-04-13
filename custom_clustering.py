import numpy as np
import pandas as pd

interrupt_times = pd.read_excel("ESP_Output.xlsx")["datapoints"][:-1]

print ([x for x in interrupt_times])

object_dists = []
object_pulse_sizes = []

current_obj_time = interrupt_times[0]

min_count_for_object = 15
max_delay = 30

count = 1

for i in range(1,len(interrupt_times)):
	if interrupt_times[i] < 1200:
		continue

	delta = interrupt_times[i] - interrupt_times[i-1]

	# print(delta)

	if delta < max_delay:
		count += 1
	else:
		if count >= min_count_for_object:
			object_dists.append(current_obj_time)
			object_pulse_sizes.append(interrupt_times[i-1] - current_obj_time)

		current_obj_time = interrupt_times[i]
		count = 1

if count >= min_count_for_object:
	object_dists.append(current_obj_time)
	object_pulse_sizes.append(interrupt_times[i-1] - current_obj_time)

# Speed of sound in air at room temp
c = 346

real_dists = []

# print([x for x in zip(object_dists, object_pulse_sizes)])

for i in range(len(object_dists)):
	pass



