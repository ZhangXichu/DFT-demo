# plots relavant graphs of real DFT
# time domain
# frequency domain: Im X[] (sine waves), Re X[] (cosine waves)

import matplotlib
import matplotlib.pyplot as plt
from matplotlib import collections as matcoll

import toolbox as tb

# setup test data
impulse = 0
simple_wave = 1

time_domain_data = simple_wave

prefix = ""
y_li = [0, 1]  # range of y-axis
y_li2 = [0, 1]
if time_domain_data == impulse:
    prefix = "impul"
    y_li = [-0.8, 1.5]
elif time_domain_data == simple_wave:
    prefix = "simpw"
    y_li = [-1.1, 1.1]
    y_li2 = [-5, 35]


def file_parser_data(in_file_data):
    """function parses file of real data
    format: [data] as a double on each line

    Args:
        in_file_data (string): file name of data

    Returns:
        list of real data
    """
    in_file = open(in_file_data, "r")
    real_nums_str = in_file.readlines()
    real_nums = []
    for s in real_nums_str:
        real_nums.append(float(s))
    return real_nums


def file_parser_complex(in_file_complex):
    """ function parses file of complex numbers and returns a tuple of two lists
        one stores the Im part (sinusoids)
        another one stores Re part (cosinusoids)
    Args:
        in_file_complex ([type]): [description]

    Returns:
        re: list of amplitude of cosinusoids
        im: list of amplitude of sinusoids
    """
    in_file = open(in_file_complex, "r")
    cpx_strs = in_file.readlines()
    re = []
    im = []
    for cpx_s in cpx_strs:
        tokens = cpx_s.split()
        # format in the file: [re] [im]
        re.append(float(tokens[0]))
        im.append(float(tokens[1]))
    return re, im


def graph_1d_real_data(lst_real_data):
    x = [i for i in range(len(lst_real_data))]
    y = lst_real_data

    fig, ax = plt.subplots()
    # add bold line at y = 0
    ax.axhline(0, color='black')

    plt.scatter(x, y, linewidths=4, c='black', s=10)
    plt.ylim(y_li)

    plt.ylabel("Amplitude")
    plt.xlabel("Index")

    plt.grid(linestyle='dashed', color='black') 

    # plt.savefig("results/" + prefix + "_time_domain.pdf")


def graph_real_dft_freq(in_file_complex):
    """function plots the frequency domain

    Args:
        in_file_complex (string): filename of file with complex numbers
    """
    lst_re, lst_im = file_parser_complex(in_file_complex)
    x = [i for i in range(len(lst_im))]
    y1 = lst_im
    y2 = lst_re

    # graph of Im X[]
    fig, ax = plt.subplots() 
    # add bold line at y = 0
    ax.axhline(0, color='black')
    # set the label size of x and y axis
    ax.yaxis.set_tick_params(labelsize=14)
    ax.xaxis.set_tick_params(labelsize=14)

    plt.scatter(x, y1, linewidths=4, c='black', s=10)
    # plt.ylim(y_li2)
    plt.ylim([-20, 25]) # for the random data sequence
    # set title and title size of x and y axis
    plt.ylabel("Amplitude", fontsize=14)
    plt.xlabel("Index", fontsize=14)
    plt.grid(linestyle='dashed', color='black') 

    tb.vertical_line(x, y1, ax)

    # plt.savefig("results/" + prefix + "_freq_im.pdf")
    # plt.savefig("results/rand_freq_even_im.pdf") # for the random data with length 20
    plt.show()

    # graph of Re X[]
    fig, ax = plt.subplots()
    # set the label size of x and y axis
    ax.yaxis.set_tick_params(labelsize=14)
    ax.xaxis.set_tick_params(labelsize=14)
    # add bold line at y = 0
    ax.axhline(0, color='black')

    plt.scatter(x, y2, linewidths=4, c='black', s=10)
    # plt.ylim(y_li2)
    plt.ylim([-20, 69.5]) # for the random data sequence
    # set title and title size of x and y axis
    plt.ylabel("Amplitude", fontsize=14)
    plt.xlabel("Index", fontsize=14)
    plt.grid(linestyle='dashed', color='black') 

    tb.vertical_line(x, y2, ax)

    # plt.savefig("results/" + prefix + "_freq_re.pdf")
    plt.savefig("results/rand_freq_even_re.pdf") # for the random data with length 20, (Re X[], cos)
    plt.show()



def main():
    # in_file_time_real_data = "build/time_real_data.txt"
    # real_nums = file_parser_data(in_file_time_real_data)
    # graph_1d_real_data(real_nums)

    in_file_name_freq_complex_data = "build/freq_complex_data.txt"
    graph_real_dft_freq(in_file_name_freq_complex_data)


if __name__ == '__main__':
    main()