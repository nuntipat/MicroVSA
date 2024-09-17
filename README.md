# MicroVSA

This repository contains an official implementation of MicroVSA, a low-dimensional computing (LDC) classifier library for 8, 16, and 32-bit MCUs, as well as several example projects demonstrating how to integrate and benchmark MicroVSA on MCU development boards.

## Project Structure

- `lib/` contains the classifier library, which can be reused in other projects
- `model/` contains the pretrained model files for all datasets mentioned in the paper
- `test_data/` contains test data for the benchmark script and for running self-tests on the board
- `examples/` contains example projects for all MCU development boards mentioned in the paper

## Prerequisite

The easiest way to test MicroVSA on the MCU development board is to use PlatformIO. However, example projects based on proprietary IDEs are also provided for some development boards. Please refer to the list of compatible IDEs for your board in the table below.

| Brand | MCU | Dev Board | IDE |
|-------|-----|-----------|-----|
| Microchip | ATtiny3217 | ATtiny3217 Curiosity Nano | Microchip MPLAB X |
| Microchip | PIC18F16Q40 | PIC18F16Q40 Curiosity Nano | Microchip MPLAB X |
| STMicroelectronics | STM8S207K8 | NUCLEO-8S207K8 | PlatformIO |
| Texas Instruments | MSP430FR5994 | MSP-EXP430FR5994 | TI CCS Cloud / PlatformIO |
| Microchip | PIC24FJ64GU205 | PIC24FJ64GU205 Curiosity Development | Microchip MPLAB X |
| STMicroelectronics | STM32L031K6 | NUCLEO-L031K6 | ST STM32CubeIDE / PlatformIO |
| Microchip | PIC32MM0064GPL036 | PIC32MM Curiosity Development | Microchip MPLAB X |
| STMicroelectronics | STM32L432KC | NUCLEO-L432KC | ST STM32CubeIDE / PlatformIO |
| STMicroelectronics | STM32F412ZG | 32F412GDISCOVERY | ST STM32CubeIDE / PlatformIO |
| STMicroelectronics | STM32H7A3ZI | NUCLEO-H7A3ZI-Q | ST STM32CubeIDE / PlatformIO |
| Adafruit | ESP-WROOM-32 | ESP32 Feather Board | PlatformIO |

For running the benchmark script

- Python >=3.8
- virtualenv
- pyserial (install automatically by the setup script)
- numpy (install automatically by the setup script)
- platformio (install automatically by the setup script)

Setup Instructions

1. (Optional) Create a Python virtual environment

    ```
    MicroVSA $ virtualenv -p python3 venv
    MicroVSA $ source venv/bin/activate
    ```

2. Setup all dependencies

    ```
    (venv) MicroVSA $ ./setup.sh
    ```

## Usage

### Run benchmark automatically

An automatic benchmark script is provided to build, upload, and perform benchmarks of the vanilla LDC, binary LDC, and MCU-optimized LDC on MCU development boards. For the expected runtime and flash and RAM utilization on all MCUs, please refer to Tables 7-9 in our paper.

```bash
# Table 7/8

# PTB Diagnostic ECG Database (Df=64) 
(venv) MicroVSA $ python automate_benchmark.py -i ESP32 -w 32 -m ptb -d 64 -c 2 -s /dev/ttyUSB0

# Qualcomm Keyword Speech Dataset (Df=64) 
(venv) MicroVSA $ python automate_benchmark.py -i ESP32 -w 32 -m qksd -d 64 -c 2 -s /dev/ttyUSB0

# UCI Human Activity Recognition (Df=64) 
(venv) MicroVSA $ python automate_benchmark.py -i ESP32 -w 32 -m har -d 64 -c 6 -s /dev/ttyUSB0

# Free Spoken Digit Dataset (Df=128) 
(venv) MicroVSA $ python automate_benchmark.py -i ESP32 -w 32 -m fsdd -d 128 -c 10 -s /dev/ttyUSB0

# Table 9

# WIreless Sensor Data Mining (Df=64) 
(venv) MicroVSA $ python automate_benchmark.py -i ESP32 -w 32 -m wisdm -d 64 -c 4 -s /dev/ttyUSB0

# ST multi-zone ToF sensors hand posture recognition (Df=128) 
(venv) MicroVSA $ python automate_benchmark.py -i ESP32 -w 32 -m sthand -d 128 -c 8 -s /dev/ttyUSB0

# run `python automate_benchmark.py -h` to view all options
```

Notes
- For boards with limited flash memory, the option `--skip-vanilla` can be used to skip the vanilla LDC benchmark (see Table 7 in the paper).
- The timer resolution needs to be set via the option `-r X` to match the `uart_send_result()` function in `benchmark_util.h`, e.g., `-r 32` for `STM8_PIO` or `-r 8` for `MSP430_PIO`.
- All implementation settings (`MODEL_TRANSPOSE_*` and `MICROVSA_IMPL_*`) in `microvsa_config.h` must be commented before running the automated benchmark script if they have been set manually, as these settings will be passed during compilation time by the automated benchmark script. 

### Build with a specific model and LDC implementation

1. Copy or create a symbolic link of the model file to the board directory. The following command is for the HAR model (Df=64) and the ESP32-based development board.

    ```bash
    (venv) MicroVSA $ cd examples/ESP32/src
    (venv) src $ ln -s ../../../model/model_har_64.h model.h
    (venv) src $ ln -s ../../../model/model_har_64.c model.c
    ```

2. Set the model specific settings in line [34-36](https://github.com/nuntipat/MicroVSA/blob/main/lib/microvsa_config.h#L34-L36) of `microvsa_config.h`. For example, the following setting can be used for HAR model with Df=64.

    ```C
    // maximum number of class in the model (must be >= MICROVSA_MODEL_NUM_CLASS in model.h)
    #define MICROVSA_MAX_NUM_CLASS 6
    // maximum value of Df in word e.g. if Df=64 and MICROVSA_IMPL_WORDSIZE=32, set this value to 2
    #define MICROVSA_MAX_FHV_DIM 2
    // set to MICROVSA_MAX_FHV_DIM * MICROVSA_IMPL_WORDSIZE
    #define MICROVSA_MAX_FHV_DIM_BIT 64
    ```

3. Select the model implementation to benchmark in `microvsa_config.h`. At a minimum, the MICROVSA_IMPL must be defined based on the constant given in line [70-75](https://github.com/nuntipat/MicroVSA/blob/main/lib/microvsa_config.h#L70-L75) of `microvsa_config.h`. The full list of support configuration are given in line [41-66](https://github.com/nuntipat/MicroVSA/blob/main/lib/microvsa_config.h#L41-L66) of `microvsa_config.h`. For example, the following setting is for the MCU-Optimized LDC (C (Col-wise) F (Col-wise)).

    ```C
    #define MICROVSA_IMPL MICROVSA_IMPL_MCU_OPT_CC
    // #define MICROVSA_IMPL_OPTIMIZE_MEM
    // #define MICROVSA_IMPL_POINTERIZE
    // #define MICROVSA_IMPL_UNROLL
    // #define MICROVSA_IMPL_FLAVOR_8BITADD
    // #define MICROVSA_IMPL_FIX_SIZE
    // #define MICROVSA_IMPL_DEBUG_P
    ```

4. (Optional) To configure the LUT size on 32-bit MCU or to use the bit-fiddling method, comment and/or set these two [lines](https://github.com/nuntipat/MicroVSA/blob/main/lib/microvsa_config.h#L29-L30) based on the description in the comment.

    ```C
    // 8/16-bit MCU must use LUT, 32-bit MCU can comment this line to use hamming weight based implementation
    #define MICROVSA_IMPL_USE_LUT
    // 8 (256-entries LUT) or 11 (2048-entries LUT)
    #define MICROVSA_IMPL_LUTBIT 8              
    ```

5. Build and upload the code to the board

    ```bash
    (venv) src $ cd ../
    (venv) ESP32 $ pio run -t upload
    ```

6. Run the benchmark script to send test data and get inference time. 

    ```bash
    (venv) ESP32 $ cd ../../
    # run `python benchmark.py -h` to view all options
    (venv) MicroVSA $ python benchmark.py \
                        -i test_data/har_d64 \
                        -c 6 -t 10 \
                        -s /dev/ttyUSB0
    ```

## Citation

If you find the project helpful, please consider citing our paper:

```
@inproceedings{10.1145/3620665.3640374,
author = {Narkthong, Nuntipat and Duan, Shijin and Ren, Shaolei and Xu, Xiaolin},
title = {MicroVSA: An Ultra-Lightweight Vector Symbolic Architecture-based Classifier Library for Always-On Inference on Tiny Microcontrollers},
year = {2024},
isbn = {9798400703850},
publisher = {Association for Computing Machinery},
address = {New York, NY, USA},
url = {https://doi.org/10.1145/3620665.3640374},
doi = {10.1145/3620665.3640374},
booktitle = {Proceedings of the 29th ACM International Conference on Architectural Support for Programming Languages and Operating Systems, Volume 2},
pages = {730–745},
numpages = {16},
keywords = {vector symbolic architecture, microcontroller, machine learning},
location = {La Jolla, CA, USA},
series = {ASPLOS '24}
}
```
