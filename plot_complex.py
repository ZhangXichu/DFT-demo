import matplotlib
import matplotlib.pyplot as plt
from matplotlib import collections as matcoll
import matplotlib.units as units
import matplotlib.ticker as ticker
import numpy as np


def parse_file(in_file_name):
    """function parses a txt input file of complex numbers

    Args:
        in_file_name ([type]): [description]

    Returns:
        3-tuple: number of data points; list of amplitudes; list of phases
    """
    in_file = open(in_file_name, "r")
    cpx_numbers = in_file.readlines()
    amplitudes = []
    phases = []
    for cpx_line in cpx_numbers:
        tokens = cpx_line.split()
        # each line in in file is of form [re] [im] [ampl] [phase]
        amplitudes.append(float(tokens[2]))
        phases.append(float(tokens[3]))
    return len(amplitudes), amplitudes, phases


# TODO: improve the functions for different range of amplitude and phase
def graph(data, n, radians=False, original=False):
    """[summary]

    Args:
        data ([type]): [description]
        n ([type]): [description]
        radians (bool, optional): True if [data] is phase, and the y-axis labels should be set to radians. Defaults to False.
        original (bool, optional): True if the given data are the origianl points (time domain, before transformation), 
            set [foot_note] to k. Defaults to False.
    """
    y = data
    x = [i for i in range(n)]

    lines = []
    for i in range(len(x)):
        pair=[(x[i],0), (x[i], y[i])]
        lines.append(pair)

    linecoll = matcoll.LineCollection(lines, colors="black")
    fig, ax = plt.subplots() 

    # set the grid in graph
    plt.grid(linestyle='dashed', color='black') 
    # set the label size of x and y axis
    ax.yaxis.set_tick_params(labelsize=14)
    ax.xaxis.set_tick_params(labelsize=14)

    if radians:
        y_label = [r"$-{\pi}$", r"$-\frac{2\pi}{3}$", r"$-\frac{\pi}{3}$", r"$0$"
            , r"$\frac{\pi}{3}$",   r"$\frac{2\pi}{3}$",  r"${\pi}$"]
        ax.set_yticks([-np.pi, -2 * np.pi/3, -np.pi/3, 0, np.pi/3, 2 * np.pi/3, np.pi])
        ax.set_yticklabels(y_label, fontsize=14)

    foot_note = "r"
    if original:
        foot_note = "k"

    ax.add_collection(linecoll)
    ax.axhline(0, color='black')

    ax.annotate(foot_note, xy=(1, 0), xycoords='axes fraction', fontsize=13,
                xytext=(0, -15), textcoords='offset points',
                ha='right', va='top')

    plt.scatter(x, y, linewidths=5, c='black', s=10)
    
    plt.xticks(x)


def graph_amplitude(amplitudes, n):
    graph(amplitudes, n)
    plt.ylim(0.3) # scale of y of amplitude

    plt.show()


def graph_phases(phase, n):
    graph(phase, n, True)
    plt.ylim([-3.6, 3.6]) # scale of y of phase

    plt.show()


def graph_original(seq_orig, n):
    graph(seq_orig, n, original=True)
    plt.ylim([-4, 10]) # scale of y of original sequence

    plt.show()



def main():
    in_file_name = "build/forward_dft.txt"
    n, amplitudes, phases = parse_file(in_file_name)
    # graph_amplitude(amplitudes, n)
    # graph_phases(phases, n)
    orig_seq = [2.0, 3.0, -1.0, 1.0, 2.5, 4.0, 3.2, 1.0, 5.0, 6.0, 4.3, 9.0, -3.0, 1.0, 2.5, 4.0, 3.2, 1.0, 5.0, 6.0]
    graph_original(orig_seq, n)


if __name__ == '__main__':
    main()
