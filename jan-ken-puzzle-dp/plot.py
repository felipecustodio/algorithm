import csv
import numpy as np
import seaborn as sns
from matplotlib import pyplot as plt


with open('performance_light.csv', 'r') as f:
    reader = csv.reader(f)
    performance_light = list(reader)

with open('performance_light_pypy.csv', 'r') as f:
    reader = csv.reader(f)
    performance_light_pypy = list(reader)

times_light = []
for test_case in performance_light:
    times_light.append(float(test_case[1]))

times_light_pypy = []
for test_case in performance_light_pypy:
    times_light_pypy.append(float(test_case[1]))

print("Plotting elapsed time...")
fig, ax = plt.subplots()
n_groups = len(times_light)
bar_width = 0.35
opacity = 0.8
index = np.arange(n_groups)
error_config = {'ecolor': '0.3'}

# Say, "the default sans-serif font is COMIC SANS"
plt.rcParams['font.sans-serif'] = "cmr10"
# Then, "ALWAYS use sans-serif fonts"
plt.rcParams['font.family'] = "sans-serif"

# plt.rcParams['font.family'] = 'cmmi10'

rects1 = ax.bar(index, times_light, bar_width,
                alpha=opacity, color='#f18a9b',
                error_kw=error_config,
                label='Python 3')

rects2 = ax.bar(index + bar_width, times_light_pypy, bar_width,
                alpha=opacity, color='#a26ea1',
                error_kw=error_config,
                label='PyPy 3')

ax.set_xlabel('Test Case (ID)')
ax.set_ylabel('Time Elapsed (Seconds)')
ax.set_title('Puzzle Solver - Python 3 vs PyPy 3 (Light Tests)')
ax.set_xticks(index + bar_width / 2)
ax.set_xticklabels(index)
ax.legend()

fig.tight_layout()
plt.savefig("plots/time_light.png", dpi=100)
