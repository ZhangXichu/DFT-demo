# plots graph of complex DFT
# graph of original data points, and amplitude, phase after transformation

import matplotlib
import matplotlib.pyplot as plt
import matplotlib.units as units
import matplotlib.ticker as ticker
import numpy as np

import toolbox as tb

def parse_file_complex_freq(in_file_name):
    """function parses a txt input file of complex numbers

    Args:
        in_file_name ([type]): file name

    Returns:
        4-tuple: number of data points; list of amplitudes; list of phases, lst_re, lst_im
    """
    in_file = open(in_file_name, "r")
    cpx_numbers = in_file.readlines()
    amplitudes = []
    phases = []
    lst_re = []
    lst_im = []
    for cpx_line in cpx_numbers:
        tokens = cpx_line.split()
        # each line in in file is of form [re] [im] [ampl] [phase]
        amplitudes.append(float(tokens[2]))
        phases.append(float(tokens[3]))
        lst_re.append(float(tokens[0]))
        lst_im.append(float(tokens[1]))
    return len(amplitudes), amplitudes, phases, lst_re, lst_im


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

    fig, ax = plt.subplots() 

    tb.vertical_line(x, y, ax)

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

    ax.axhline(0, color='black')

    ax.annotate(foot_note, xy=(1, 0), xycoords='axes fraction', fontsize=13,
                xytext=(0, -15), textcoords='offset points',
                ha='right', va='top')

    # plot discrete data
    plt.scatter(x, y, linewidths=5, c='black', s=10)
    
    plt.xticks(x)


def graph_amplitude(amplitudes, n):
    graph(amplitudes, n)
    # plt.ylim(0.3) # scale of y of amplitude
    
    # configure the filename and corresponding range of values
    # plt.savefig("results/freq_amplitude.pdf")

    # plt.ylim([-20, 65.5])  # scale of y of amplitude in Re X[]
    # plt.savefig("results/freq_re_even.pdf")

    plt.ylim([-25, 25])  # scale of y of amplitude in Im X[]
    plt.savefig("results/freq_im_even.pdf")

    plt.show()


def graph_phases(phase, n):
    graph(phase, n, True)
    plt.ylim([-3.6, 3.6]) # scale of y of phase

    # plt.savefig("results/freq_phase.pdf")

    plt.show()


def graph_original(seq_orig, n):
    graph(seq_orig, n, original=True)
    plt.ylim([-4, 10]) # scale of y of original sequence

    plt.savefig("results/original_seq.pdf")

    # plt.show()



def main():
    in_file_name = "build/forward_dft.txt"
    n, amplitudes, phases, lst_re, lst_im = parse_file_complex_freq(in_file_name)
    # graph_amplitude(amplitudes, n)
    # graph_amplitude(lst_re, n)
    graph_amplitude(lst_im, n)
    # graph_phases(phases, n)

    # random
    # orig_seq = [2, 3, -1, 1, 2.5, 4, 3.2, 1, 5, 6, 4.3, 9, -3, 1, 2.5, 4, 3.2, 1, 5, 6]  # even length 20
    orig_seq = [2, 3, -1, 1, 2.5, 4, 3.2, 1, 5, 6, 4.3, 9, -3, 1, 2.5, 4, 3.2, 1, 5, 6, 21]  # odd length 21
    # impulse
    # orig_seq = [0 for i in range(n)]; 
    # orig_seq[0] = 1

    # graph_original(orig_seq, n)


if __name__ == '__main__':
    main()
