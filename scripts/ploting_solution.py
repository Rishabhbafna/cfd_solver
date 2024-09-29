import numpy as np
import matplotlib.pyplot as plt
from glob import glob

# Read data from the file
filenames = glob("out/Solution*.out")
filenames.sort()
for filename in filenames:
    with open(filename, "r") as f:
        lines = f.readlines()

    # Extract relevant information
    xCells = int(lines[0].split(":")[1])
    numGhostCells = int(lines[1].split(":")[1])
    time = float(lines[2].split(":")[1])

    # Extract x and u values
    x = []
    u = []
    for line in lines[3:]:
        x_val, u_val = line.split(":")
        x.append(float(x_val))
        u.append(float(u_val))

    # Create the plot
    plt.plot(x, u, linewidth=3)
    plt.xlabel("x")
    plt.ylabel("u")
    plt.title("At Time t = {}".format(time))
    plt.xlim(-1.1, 1.1)
    plt.ylim(-0.1, 1.1)
    plt.grid(True)  # Add grid lines for better readability
    plt.savefig(filename.replace(".out", ".png"))
    plt.close()