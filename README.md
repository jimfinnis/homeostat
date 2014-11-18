homeostat
=========

This program is a Qt4 simulation of W Ross Ashby's homeostat - read more in his book "Design for a Brain".

The four boxes are the four units of the homeostat. Within each unit:
* the slider is the output of the unit, corresponding to the magnet position in the original machine. As well as being an output, it can be dragged to perturb the unit.
* the four dials are the parameters, corresponding to the potentiometers and commutators in the original. Each dial is the amount the unit is affected by another unit - the first dial is unit A, the second is unit B and so on. The centre position means no effect, left of centre means a negative effect, right of centre means a positive effect. One of the dials will be a feedback parameter -  how the unit affects itself.
* the auto checkbox is used to turn on the "outer feedback loop" for that unit. When it's on, if the output goes close to the maximum or minimum, the unit's parameters will be randomized (with the exception of the feedback dial, as per Ashby's original device). The check is made every 2 seconds.

The simulation will run while the *running* checkbox is checked.

The *reset graphs* button will clear the graphs (see below), and the *randomize* button will randomize all the parameters (except the feedbacks).


The three graphs at the bottom are phase space plots of the homeostat's state. From left to right, they are:
* the output of B against the output of A
* the output of C against the output of A
* the output of D against the output of A

## Assumptions
* The output ranges are from 0-1
* The target (i.e. the desired position) for all outputs is 0.5
* The valid range (which doesn't trigger randomization) for the essential variables (the outputs) is -0.7 to 0.7
* There is currently no way to build alternate configurations - all units affect all others

## Building
* Install Qt4
* Clone the homeostat repo into a directory
* Start Qt Creator
* Open the project file
* Configure as desired
* Run

Alternatively from the command line:
* Install Qt4
* Clone the homeostat repo into a directory
* **cd** to the cloned directory
* **qmake**
* **make**
* **./homeostat**
