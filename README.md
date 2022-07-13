## UTAustinX UT.6.10x: Embedded Systems - Shape The World: Microcontroller Input/Output Labs

### Description
- This is my solution to the 
[UT.6.10x: Embedded Systems - Shape The World: Microcontroller Input/Output](https://learning.edx.org/course/course-v1:UTAustinX+UT.6.10x+3T2019/home) course.

### Tools and Technologies
- [PlatformIO](https://platformio.org/).
- [NeoVIM](https://neovim.io/) as an editor.
- [VS Code](https://code.visualstudio.com/) to debug the code.
- [Keil μVision V4.0](https://www.keil.com/demo/eval/armv4.htm) for edX grader.

### How to Run the Code
- Connect your LaunchPad to your computer.
- If you are using Linux, follow the steps in 
[here](https://docs.platformio.org/en/latest/core/installation/udev-rules.html) 
to be able to access the LaunchPad.

- Install PlatformIO CLI and VSCode extension.

- Clone the repository and run the following commands:
    ````
    git clone https://github.com/Alighorab/UT.6.10x.Labs.git
    cd UT.6.10x.Labs
    cd <lab_name>
    make
    make upload
    ````
- To debug the code, run the following commands:
    ````
    cd <lab_name>
    code .
    ````
    - Hit `F5` to start the debugger.

- To get a grade for the lab, copy the code to Keil 
and follow the instructions in the course.

### Certificate
- You can view my certificate from this [link](https://courses.edx.org/certificates/19d4d07d36c043bab8d145dee51e8a41).
