# some auxilary functions for plotting data 

import matplotlib
import matplotlib.pyplot as plt
from matplotlib import collections as matcoll

def vertical_line(x, y, ax):
    """ function adds vertical line from each dot to x-axis in a scatter graph 

    Args:
        x (list): x-axis
        y (list): y-axis
        ax (`.axes.Axes` object): returned by `subplots`
    """
    lines = []
    for i in range(len(x)):
        pair=[(x[i],0), (x[i], y[i])]
        lines.append(pair)
    linecoll = matcoll.LineCollection(lines, colors="black")

    ax.add_collection(linecoll)