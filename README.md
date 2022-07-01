## UT.6.10x Embedded Systems: Shape the World Labs

### Description
- These labs are implemented using C programming language.

### Tools and Technologies
- C programming language.
- PlatformIO.
- NeoVIM as an editor.
- VS Code to debug the code.

### How to Run the Code
- Connect your LaunchPad to your computer.
- If you are using Linux, follow the steps in 
[here](https://docs.platformio.org/en/latest/core/installation/udev-rules.html) 
to be able to access the LaunchPad.

- Install PlatformIO.

- Clone the repository and run the following commands:
    ````
    git clone https://github.com/Alighorab/UT.6.10x.Labs.git
    cd UT.6.10x.Labs
    cd <lab_name>
    make
    make upload
    ````
- To debug the code, run the following command:
    ````
    cd <lab_name>
    code .
    ````
    - Hit <F5> to start the debugger.
