# Small scale Fourier analysis

A demo program of small scale Fourier analysis. It implements forward and inverse DFT and transformation of real data using complex DFT.

The part written in C is used to collect data and the part written in Python is used to plot corresponding graphs.

## Usage

### Installation

This program uses Cmake to compile. Create an directory `build` and run in the `build` directory, where the .txt file of output file will be stored

    cmake ..

Then run the command

    make

in the same directory An exceutable file `ft_demo` will be created.

### Output data

Comment/Uncomment the macros in `config.h` to set which test in `main.c` to run. Results of each transformation are stored in output .txt files.

### Create graphs
