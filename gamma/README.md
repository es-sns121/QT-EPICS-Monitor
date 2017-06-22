# recordMonitor

This code is written in c++ and is built using EPICS version 3.16, 
EPICS version 4.5.0, and Qt 4.8.1

This example demonstrates how to build a client application that monitors
the data of pvRecords hosted on an EPICS V4 database.

The application's GUI is implemented using Qt. This code is in the 
view.\* files. 
The application's model is implemented using EPICS.  This code is in
model.\* and monitorWorker.\* files.

## Expected Path

The makefile expects 'g++' and Qt's 'moc' to be available based on
the PATH variable or its equivalent.

## Shell Variables

The Makefile expects certain shell variables to be set. 

'EPICS\_V3\_DIR' : The topmost directory of the EPICS v3 install

'EPICS\_V4\_DIR' : The topmost directory of the EPICS v4 install

'EPICS\_HOST\_ARCH' : The host architecture of the system.
An example would be "linux-x86\_64".

## Building

If the shell variables are present on your system as they are defined
in the makefile just type:

    > make

## Source Files

This directory has the following files:

### Model
* model.cpp 

* model.h

* monitorWorker.h

* monitorWorker.cpp

### View
* view.h

* view.cpp

### Main
* main.cpp


