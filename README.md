# SoccerRL

## Purpose

To create a reinforcement learning agent capable of learning an element of RoboCup Soccer.

## License

The source code of this project is licensed under the Apache License v2.0.
See LICENSE.md for more details.

## Requirements

This application was so far tested using the following libraries:
* OpenCV v3.2.0
* Boost v1.63.0

This application was tested on the following Operating System(s):
* MacOS Sierra (v10.12)

## Proposed implementation

* Computer Vision components implemented using OpenCV
* Implement reinforcement learning using Sarsa(&#955;), a TD(&#955;) method
* State space discretisation using tile coding function approximation

## Classes

* RobotTracker: implements robot tracking mechanism using ArUco AR markers
* MarkerFinder: actually finds the AR markers within the image
* BallTracker: tracks the position of the ball in the image by thresholding the image based on lower and upper HSV colour space limits.

## Code Contributors

* Marcel Ruhf (m.ruhf@protonmail.ch)

## Hardware Contributors

* Sam Wilson (S.S.Wilson@leeds.ac.uk)
* Andy Bulpitt (A.J.Bulpitt@leeds.ac.uk)

## Installing Prerequisites

Before compiling this project, you will need to have installed the prerequisites listed above. These instructions work for macOS X only. I am also assuming that you have Homebrew installed already.

```shell
brew install opencv3 --with-tbb --with-contrib  # YOU MUST INCLUDE THE tbb ANDcontrib libraries!
brew install boost
```

## Compile

To run this project, you will need to compile it first.

```shell
cd /path/to/SoccerRL
cmake .
make
```

This creates an executable called ```SoccerRL``` in ```/path/to/SoccerRL/Tracker/bin```.
