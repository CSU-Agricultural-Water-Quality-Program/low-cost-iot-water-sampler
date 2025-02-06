/*Example sketch to control a stepper motor with DRV8825 stepper motor driver, AccelStepper library and Arduino: number of steps or revolutions. More info: https://www.makerguides.com */
// Include the AccelStepper library:
#include <AccelStepper.h>
// Define stepper motor connections and motor interface type. Motor interface type must be set to 1 when using a driver:
#define dirPin 3
#define stepPin 5
#define enPin 2
#define motorInterfaceType 1
// Create a new instance of the AccelStepper class:
AccelStepper stepper = AccelStepper(motorInterfaceType, stepPin, dirPin);

///////////////////////////////// User Input ////////////////////////////////////////////
int desiredSteps = 30000; // number of steps
int maxSpeed = 1200;  // max steps per second for pump
int desiredSpeed = 1000; // steps per second
int timePause = 40000;  // time to pause between samples
//////////////////////////////////////////////////////////////////////////////////////////

void setup() {
  Serial.begin(9600);
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enPin, OUTPUT);
  // Set the maximum speed in steps per second:
  stepper.setMaxSpeed(maxSpeed);
  delay(5000);
}

void loop() { 
  while(stepper.currentPosition() != desiredSteps)
  {
    digitalWrite(enPin,LOW);  //  turn pump on
    stepper.setSpeed(desiredSpeed);
    stepper.runSpeed();
  }

  stepper.setCurrentPosition(0);
  digitalWrite(enPin,HIGH); //  turn pump off
  delay(timePause);
  
}
