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

"""
interrupt times as plaintext
[27, 52, 77, 103, 128, 146, 153, 178, 195, 202, 227, 252, 277, 302, 327, 351, 376, 401, 425, 442, 450, 467, 475, 500, 524, 549, 574, 599, 624, 648, 673, 698, 723, 747, 772, 797, 821, 845, 870, 895, 919, 943, 968, 992, 1016, 1037, 1040, 9754, 9759, 9786, 9812, 9828, 9837, 9854, 9863, 9888, 9913, 9938, 9963, 9989, 10014, 10039, 10064, 10088, 10105, 10113, 10138, 10163, 10187, 10212, 10237, 10261, 10286, 10311, 10336, 10360, 10385, 10401, 10410, 10435, 10460, 10485, 10510, 10534, 10559, 10584, 10600, 10609, 10633, 10658, 10683, 10708, 10733, 10751, 10758, 10776, 10782, 10807, 10831, 10852, 10856, 19763, 19791, 19810, 19817, 19842, 19868, 19893, 19918, 19943, 19968, 19993, 20018, 20043, 20068, 20092, 20117, 20146, 20166, 20191, 20213, 20215]
"""