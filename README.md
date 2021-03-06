2015 BattleStation for X7
=========================

[![Build status](https://ci.appveyor.com/api/projects/status/xu3vg99k99cliubr?svg=true)](https://ci.appveyor.com/project/vincentzhang96/battlestation)

Features:
---------------------
- [x] SDL joystick compatbility
- [x] QTSerial library for connection to top board (writing)
- [x] Basic interpolator to handle ramping up thrusters
- [x] Looks cool  
- [x] Compute thruster values based off of joystick input
- [x] Use interpolator to filter thruster values
- [x] Compute a checksum
- [x] System View Section in GUI (update thurster look and functionality)
- [x] Thruster view in GUI (make bigger size, better color)
- [ ] Handle reading from serial
- [ ] Mission tasks in tasks section in GUI (highlight next desired task)
- [ ] System Status in GUI
- [ ] Orientation in GUI
- [ ] Configuration in GUI


How to install and run:
-----------------------
Download and install [Qt](http://qt-project.org/). Open project file in Qt Creator and run qmake to set up build system. Try running it and hopefully everything works. Only dependencies should be Qt and SDL. SDL libraries for Windows and OS X are included in the repository and should be configured to compile with them.

Dependencies
----------------------------
**Fedora
- qt5-qtserialport
- qt5-qtdeclarative
- qt-qtbase
- qt-creator
- libXi-devel
- libXmu-devel

Basic Structure Information:
----------------------------
**QT/**: Contains all main files for the program  
- **ROVTest.pro**: Main project file with build flags/information  
- **C++ Files**:  
 - **main**: includes main function, starts up an instance of battlestation  
 - **battlestation**: main class for the battlestation, handles settings things up and exiting  
 - **threadcontroller**: handles the different threads for the program  
 - **mainticker**: main thread that runs fast, will be used to manage things we need to do every tick (computing thruster vectors, serial, etc.)  
 - **joystick**: joystick class to handle abstraction of SDL and joystick  
 - **inputhandler**: handles input from joystick and main window  
 - **interpolator**: handles ramping up/down of thrusters  
 - **serial**: handles initialization of serial and sending information  
- **QML Files**:  
 - **main**: Main qml file that handles layout of GUI  
 - **ROVBox**: Box to hold things in, with battlestation style  
 - **ROVButton**: Button with battlestation style  
 - **ROVComboBox**: ComboBox with battlestation style  
 - **ROVSlider**: Sliders with battlestation style  
 - **ROVTab**: Tab interface with battlestation style
 - **ROVThruster**: Top thruster view
 - **ROVTitle**: Title text with battlestation style
- **Others**:  
 - There are some other small ones, but they have to do with some Qt build things (nothing that we will be editing).

**SDL/**: Contains SDL libraries for Windows and OS X  


# REMINDER: PLEASE EDIT AS NEED. KEEP EVERYTHING AS UP TO DATE AS WE CAN -MM #
