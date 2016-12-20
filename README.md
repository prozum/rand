[![Travis: Build Status](https://travis-ci.org/prozum/rand.svg?branch=master)](https://travis-ci.org/prozum/rand)
[![Coverity: Analysis Status](https://scan.coverity.com/projects/11118/badge.svg)](https://scan.coverity.com/projects/11118)

RANDIE (Realtime Autonomous Navigational Drone for Indoor Environments
======================================================================
Firmware for an indoor navigation drone. The current implementation is based on the ATmega 328p microprocessor, but a header-file for the 1280p is included as well. The RANDSIM simulator is included as well, because the drone is not capable of flying yet. The firmware is written entirely in C and the simulator is written in C/C++. The following describes how to run the simulator alon
g with general information about the project.

Dependencies:
------------------------------------------------
- CMake version 2.8 or newer
- SDL2 version 2.0.4 or newer
- CppUnit version 1.13.2 or newer
- screen version 4.3.1 or newer
- Graphviz version 2.38.0 or newer
- Doxygen version 1.8.11-1 or newer
- C version c11
- C++ version 14 
- avr-gcc version 4.8.1
- avr-g++ version 4.8.1
- avrdude version 6.1
- libelf-dev version 0.159-42
- arduino-sdk version 2:1.0.5+dfsg2-4 or newer

Compile Instructions:
---------------------

RANDIE uses CMake as the build system. The build system uses the following flags:

CMake Options | Default Value | Meaning
------------- | ------------- | -------------
TESTS         |       0       | Build the unit and component tests and the RANDSIM simulator
DOC           |       0       | Generate Doxygen documentation (HTML)
SERIAL_TARGETS|       0       | Enables serial communication to the host PC (for debugging)
SAMPLES       |       0       | Build Samples
SIZE_TARGETS  |       0       | Shows the size of the compiled firmware

In order to use an option you must write "Option=1" when running CMake. See the example below:
```bash
cmake -DTESTS=1 ..
```
### Compile Example:
In order to install and run the project (simulation) on a Ubuntu-based machine, please extract the files from the zip-folder and run the following bash-commands:

```bash
sudo apt install cmake libsdl2-dev libsdl2-gfx-dev libsdl2-ttf-dev libsdl2-image-dev libcppunit-dev screen graphviz-dev doxygen g++ arduino libelf-dev gcc-4.9
cd RAND/
mkdir build && cd build/
cmake -DTEST=1 ..
make randsim
cd test/randsim/
./randsim
```

