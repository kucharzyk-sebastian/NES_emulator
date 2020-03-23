# NES 6502 Emulator

Fully functional and well-tested emulator of an 8-bit 6502 processor from Nintendo Entertainment System (NES) home video game console created as a bachelor's thesis in C++

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

### Prerequisites

* Visual Studio 2019 or newer
* VSCppUnit C++ Unit Testing Framework
* Windows 7 or newer

### Installing

1. Install Visual Studio
2. Clone this repository to your local drive
3. Open *NES_Emulator.sln* file from the root directory and you are ready to go!


## Running the tests

1. Open *NES_Emulator.sln* file from the root directory
2. Build the whole solution
3. Open Test Explorer by pressing *CTRL + E, T* or going to *View => Test Explorer*
4. Run all tests by pressing *CTRL + R, A* or using a *Run All Tests* button.


## Deployment

1. Open *NES_Emulator.sln* file from the root directory
2. Build *NES_Core* project in Release mode
3. Get the produced binary from *<ROOT>\build\bin\Win32\NES_Core\NES_Core.lib*

## Authors

* [Sebastian Kucharzyk](https://github.com/kucharzyk-sebastian)


## Acknowledgments

* Great source of information about NES - [nesdev](http://wiki.nesdev.com/w/index.php/Nesdev_Wiki)
* The very best place to see a live example of 6502 - [easy6502](https://skilldrick.github.io/easy6502/)
