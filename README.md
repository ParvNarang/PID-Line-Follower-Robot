# PID-Line-Follower-Robot
A line follower robot that can follow a curvilinear path directed by a line, where both are of different colours.
It uses the Proportional, Integral & Derivative functions to calculate the error and tries to minimize that error so as to improve the movement of the robot.

Resources 
  - https://www.pololu.com/docs/0J19/all
  - https://www.instructables.com/
  
Components Used
  - Arduino Nano
  - QTR-8A Reflectance Sensor Array
  - L293D Motor Driver/ TB6612FNG Driver
  - 2 x N20-6V-300 Rpm Micro Metal Gear Motor
  - 2 x Pololu Wheel 42x19mm
  - 7.4V Lipo Battery
  
![WhatsApp Image 2021-01-10 at 18 55 35 (2)](https://user-images.githubusercontent.com/56078295/104503254-d2b80580-5606-11eb-96f2-afe145f46ba5.jpeg)

#The Equation
P, I, and D are represented by the three terms that add together here. Kp, Ki, and Kd are constants that tune how the system reacts to each factor - 
![Screenshot 2021-07-15 at 2 23 04 AM](https://user-images.githubusercontent.com/56078295/125691411-64de914d-1d6a-4362-bcc7-d844ce483c3b.png)


# ERROR CALCULATION AND SPEED CONTROL
    int error = position - 3500;
    int motorSpeed = Kp * error + Kd * (error - lastError);
    lastError = error;
    int rightMotorSpeed = BaseSpeed + motorSpeed;
    int leftMotorSpeed = BaseSpeed - motorSpeed;
    

![WhatsApp Image 2021-01-10 at 18 55 35 (1)](https://user-images.githubusercontent.com/56078295/104503321-e8c5c600-5606-11eb-8430-e149959d9270.jpeg)

The maximum speed has been set to 225, the base speed is 155 and the turning speed is set to 100. All of which can be changed to 255(max. speed) if needed. 
