//This is from the WPILib instructions on how to construct a potentiometer
//It uses the AnalogInput class, I'm not sure how to format it as a c++ class. 

//here's a link to the instructions: https://wpilib.screenstepslive.com/s/4485/m/13810/l/241877-potentiometers-measuring-joint-angle-or-linear-motion


Potentiometer *pot;
pot = new AnalogPotentiometer(0, 360, 30);
AnalogInput *ai = new AnalogInput(1);
pot = new AnalogPotentiometer(ai, 360, 30);
