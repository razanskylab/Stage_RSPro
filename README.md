# Stage_RSPro

## Overview of project

Build your own simple linear stage including Serial interface and a customized microcontroller code. The whole project consists of three parts

*  Lead screw driven stage with a home switch and a stepper motor
*  Electronics to wire the stepper motor
*  Firmware with a serial protocol for communication
*  MATLAB interfacing code to allow object oriented stage control

Initially I started this because all the commercially available solutions were just way to expensive while providing high accuracies. I simply needed to move a camera forth and back between two positions and did not want to spend 3k CHF on a super expensive motorized stage.

## Hardware

*  Any Arduino should do the job of the controlling
*  For the stepper motor driver I would recommend [this module by Pololu](https://www.pololu.com/product/2998)
*  I had the linear stage and the stepper motor laying around

## Missing features which will be implemented ASAP

*  home switch
*  homing velocity
*  acceleration / piecewise increase of speed

## Serial communication protocol

The serial protocol is used to communicate between the host PC and the microcontroller responsible for the motor control. Typically each command thereby consists of a first character which can be followed by some data if required. At the very end of the communication, the Arduino/Teensy returns a handshake through `r`. While I provide only a MATLAB library for the communication, everything should be easy to adapt to other programming languages since Serial communication is quite standard.

Baud rate: `9600`

### Functions

Overview over implemented functions

*  Identify
*  Read and set absolute position
*  Read and set lead screw pitch
*  Read and set steps per revolution of stepper
*  Read and set velocity of stage movement

#### Identify controller

Command: `i`
Handshake: `r` should be returned
Function: All LEDs on controller board qucikly light up to show which board we are using

#### Request value of current position

Command: `p`
Return: `float` value identifying the position of the stage relative to the home position in `mm`

#### Move stage to a new positon

Command: `a` (absolute move) followed by `float` (4 bytes)
Return: `r` when completed movement
Function: moves the stage to a new position specified in the world coordinate system

#### Request currently defined lead screw pitch

Command: `t`
Return: `float` value identifying the pitch of the leadscrew per revolution followed by an `r`
This value is provided in mm pitch per full revolution of the stepper.

#### Define pitch of lead screw

Command: `y` followed by `float` (4 bytes)
Return: `r` when completed
This value is provided in mm pitch per full revolution of the stepper

#### Request steps per revolution of stepper motor

Command: `s`
Return: `float` followed by `r` for handshaking
How many steps does our stepper motor need to do for a single full revolution? This value would typically be between 200 and 400

#### Define steps per revolution of stepper motor

Command: `d`
Return: `float` followed by `r` for handshaking
How many steps does our stepper motor need to do for a single full revolution? This value would typically be between 200 and 400

#### Request velocity of stage movement

Command: `w`
Return: `float` followed by `r` for handshaking
Function: What is the target velocity of the stage movement?

#### Define velocity of stage movement

Command: `v` followed by a `float` specifying the target velocity in `mm/s`
Return: `r` when completed
Function: This function will not induce any stage movement but simply define the target velocity value which we want to reach.


