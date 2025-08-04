# Demo program


This project supports experiments related to the thesis [FFT test integration into NIST STS randomness test tool] (https://is.muni.cz/th/i7638/). . It includes implementations of naive Discrete Fourier Transform (DFT) and Fast Fourier Transform (FFT), along with visualization tools to analyze random number generators.

## Features

- Naive DFT (real and complex, forward and inverse)
- Radix-2 FFT and Rader's FFT for prime lengths
- Matrix-based FFT
- Speed benchmarking between DFT and FFT
- Visualization of random bitmaps and transform results


## Build instruction

```bash
mkdir build
cd build
cmake ..
make
./ft_demo
```

## Configuration

Enable specific tests by uncommenting macros in include/config.h:

- `TEST_DFT_COMPLEX_FORWARD`
- `TEST_DFT_REAL_FORWARD`
- `TEST_DFT_REAL_INVERSE`
- `SPEED_DFT_FFT`
- `TEST_FFT`
- `TEST_FFT_PRIME`
- `TEST_MATRIX`

## RNG Comparison

Two bitmaps are generated to contrast:

- ✅ Good RNG: True random numbers from [random.org](https://www.random.org/)
- ❌ Bad RNG: PHP 5.3 built-in pseudo-RNG

See `tools/bitmap.py` and `tools/rand.php`.


### Create graphs

Graphs can be made using scripts

`plot_complex.py` : complex DFT

`plot_dft_real.py` : real DFT

`ft_dft_speed.py`: speed comparison of FFT and naive DFT