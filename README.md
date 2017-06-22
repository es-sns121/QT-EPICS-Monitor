# Qt and Epics

This directory serves as an example on how to build applications using 
Qt and EPICS. Three directories are present, with each representing a
more complicated and complete implementation of the build.

The end goal is to produce an application that monitors pvRecords hosted
on a V4 database. It's GUI will be implemented using Qt. The GUI will
facilitate the monitoring of multiple records in its final state.

## Alpha

Getting up and running. This is a simple application that requests data 
from a record and then displays it in a text box.
The GUI implements a tab mechanism, allowing multiple records' data to be 
viewed at once.

The moc\_put.cpp file is the output of the Qt 'moc' program. 'moc' means
Meta Object Comiler. This file is generated, and does not have to be written.

## Beta

Beta builds on alpha by splitting the code up into a model/view relationship.
The model uses EPICS, and the view uses Qt. In this way the model can be 
dislocated from the GUI and used for other purposes.

## Gamma

Gamma represents the final product and the largest leap from version to version. 
It implements multithreading in the model to allow monitoring of multiple records.
This is necessary becuase the monitor will block the current thread as it waits
for changes in the record's data.
The GUI also changes some, as it needs to make use of the model's monitoring 
functionality. This is done by adding a timer that updates the local data
to match that retrieved by the monitor. The polling rate set by the timer is 
currently 250 milliseconds. The performace of the application at this rate
is acceptable. Higher polling rates have not been experimented with. Though 
it is doubtful it would cause any real performace issue, the effects of higher 
polling rates are unknown.
