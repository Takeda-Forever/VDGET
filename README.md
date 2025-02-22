# Video Device Name Getter
This program retrieves the names of video devices on your system. It utilizes the Interface Media Foundation (IMF) library by Microsoft to interact with video, audio, and other types of devices.

### Requirements
Windows OS: The program is designed for Windows.
Microsoft Media Foundation: The program depends on the IMF (Interface Media Foundation) for device interaction.
Installation
To build and use the program, follow these steps:

### Clone the repository:

```bash
git clone https://github.com/Takeda-Forever/VDGET.git
```
Build the project: Use your preferred build system (e.g., Visual Studio) to compile the program. Make sure you have the necessary dependencies for Media Foundation.

### Building
You can build this project using MinGW or Visual Studio. Below is an example of how to build it using g++:
```bash
g++ -o video_device_name_getter main.cpp -lmfplat -lcomsupp
```
Explanation:
- main.cpp: source file with code.
- -o video_device_name_getter: executable program's name.
- -lmfplat: library for working with Media Foundation.
- -lcomsupp: Library to support COM.

### Usage
Here is a small example of how to use the IMF to get video device names:
```bash
./video_device_name_getter
```
This will print out the names of available video devices.

### License
MIT License
