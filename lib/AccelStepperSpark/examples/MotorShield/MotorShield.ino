// MotorShield.ino
// -*- mode: C++ -*-
//
// Shows how to use AccelStepper to control a 3-phase motor, such as a HDD spindle motor
// using the Adafruit Motor Shield
// http://www.ladyada.net/make/mshield/index.html.
// Create a subclass of AccelStepper which controls the motor  pins via the
// Motor Shield serial-to-parallel interface

#include <AccelStepper.h>

// Pin names for interface to 74HCT595 latch
// on Adafruit Motor Shield
#define MOTORLATCH   A0
#define MOTORCLK     A1
#define MOTORENABLE  A2
#define MOTORDATA    A3

// PWM pins, also used to enable motor outputs
#define PWM0A        D0
#define PWM0B        D1
#define PWM1A        D2
#define PWM1B        D3
#define PWM2A        TX
#define PWM2B        RX


// The main purpose of this class is to override setOutputPins to work with Adafruit Motor Shield
class AFMotorShield : public AccelStepper
{
  public:
  AFMotorShield(uint8_t interface = AccelStepper::FULL4WIRE, uint8_t pin1 = A4, uint8_t pin2 = A5, uint8_t pin3 = A6, uint8_t pin4 = A7);

  virtual void   setOutputPins(uint8_t mask);
};


AFMotorShield::AFMotorShield(uint8_t interface, uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4)
    : AccelStepper(interface, pin1, pin2, pin3, pin4)
{
    // Enable motor control serial to parallel latch
    pinMode(MOTORLATCH, OUTPUT);
    pinMode(MOTORENABLE, OUTPUT);
    pinMode(MOTORDATA, OUTPUT);
    pinMode(MOTORCLK, OUTPUT);
    digitalWrite(MOTORENABLE, LOW);

    // enable both H bridges on motor 1
    pinMode(PWM2A, OUTPUT);
    pinMode(PWM2B, OUTPUT);
    pinMode(PWM0A, OUTPUT);
    pinMode(PWM0B, OUTPUT);
    digitalWrite(PWM2A, HIGH);
    digitalWrite(PWM2B, HIGH);
    digitalWrite(PWM0A, HIGH);
    digitalWrite(PWM0B, HIGH);

    setOutputPins(0); // Reset
};

// Use the AF Motor Shield serial-to-parallel to set the state of the motor pins
// Caution: the mapping of AccelStepper pins to AF motor outputs is not
// obvious:
// AccelStepper     Motor Shield output
// pin1                M4A
// pin2                M1A
// pin3                M2A
// pin4                M3A
// Caution this is pretty slow and limits the max speed of the motor to about 500/3 rpm
void AFMotorShield::setOutputPins(uint8_t mask)
{
  uint8_t i;

  digitalWrite(MOTORLATCH, LOW);
  digitalWrite(MOTORDATA, LOW);

  for (i=0; i<8; i++)
  {
    digitalWrite(MOTORCLK, LOW);

    if (mask & _BV(7-i))
      digitalWrite(MOTORDATA, HIGH);
    else
      digitalWrite(MOTORDATA, LOW);

    digitalWrite(MOTORCLK, HIGH);
  }
  digitalWrite(MOTORLATCH, HIGH);
}

AFMotorShield stepper(AccelStepper::HALF3WIRE, 0, 0, 0, 0); // 3 phase HDD spindle drive

void setup()
{
   stepper.setMaxSpeed(500);	// divide by 3 to get rpm
   stepper.setAcceleration(80);
   stepper.moveTo(10000000);
}

void loop()
{
   stepper.run();
}
