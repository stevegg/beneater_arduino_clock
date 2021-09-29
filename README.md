# beneater_arduino_clock
A simple Arduino schematic and sketch to replace Ben Eater's 555 based astable and monostable clock

I was running into some issues that I thought might be related to the clock module (still haven't completely diagnosed it).  To debug I decided to build a quick clock module off of a spare Arduino Nano I had laying around.  It supports astable and monostable modes through SW1 and stepping is done with SW2.  The frequency can be set with RV1 (I'm using a 10k but really anything will do.).

The sketch takes the value of RV1 and inverts it so that the lowest value has the longest frequency and the highest value has the shortest.  Because I didn't think an interval of 0 made sense I added 10ms as a minumum delay for the duty cycle.

![Schematic](https://github.com/stevegg/beneater_arduino_clock/blob/main/schematic.png?raw=true)

