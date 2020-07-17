import matplotlib.pyplot as plt
import sys

fitness_curve = []
with open('fitness.csv','r') as file:
	for line in file:
		fitness_curve.append(float(line))
fitness_curve.append(float(sys.argv[1]))

plt.plot(fitness_curve)
plt.show()

with open('fitness.csv','a') as file:
	file.write(sys.argv[1] + '\n')
