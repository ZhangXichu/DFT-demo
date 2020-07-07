import matplotlib.pyplot as plt

def file_parser_data(in_file_time):
    """ function parses file of time consumed by fft and dft 
    Args:
        in_file_time (string): [description]
    Returns:
        tuple: [description]
    """
    in_file = open(in_file_time, "r")
    lines = in_file.readlines()  # format: [dft_time] [fft_time]
    dft_time = []
    fft_time = []
    counter = 0
    for s in lines:
        ticks = s.split()
        dft_time.append(int(ticks[0]))
        fft_time.append(int(ticks[1]))
        counter += 1
    return dft_time, fft_time, counter


def graph_dft_fft(in_file_name_time):
    dft_time, fft_time, size = file_parser_data(in_file_name_time)
    x1 = [i for i in range(2, size + 2)]
    x2 = [i for i in range(2, size + 2)]
    
    plt.plot(x2, fft_time, '-o', color='k', label="FFT")
    plt.plot(x1, dft_time, '-x', color='k', label="DFT")

    plt.ylabel("Clock ticks")
    plt.xlabel("Exponent")

    plt.grid(linestyle='dashed', color='black') 
    plt.legend()

    plt.savefig("results/fft_dft_speed.pdf")
    plt.show()


def main():
    in_file_name_time = "build/dft_fft_speed.txt"
    graph_dft_fft(in_file_name_time)


if __name__ == '__main__':
    main()