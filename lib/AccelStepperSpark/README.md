# AccelStepper for Particle

This is the Arduino port of [AccelStepper library](http://www.airspayce.com/mikem/arduino/AccelStepper/) for Particle devices. It provides an object-oriented interface for 2, 3 or 4 pin stepper motors.

The standard Arduino IDE includes the Stepper library (http://arduino.cc/en/Reference/Stepper) for stepper motors. It is perfectly adequate for simple, single motor applications.

AccelStepper significantly improves on the standard Arduino Stepper library in several ways:

* Supports acceleration and deceleration
* Supports multiple simultaneous steppers, with independent concurrent stepping on each stepper
* API functions never delay() or block
* Supports 2, 3 and 4 wire steppers, plus 3 and 4 wire half steppers.
* Supports alternate stepping functions to enable support of AFMotor (https://github.com/adafruit/Adafruit-Motor-Shield-library)
* Supports stepper drivers such as the Sparkfun EasyDriver (based on 3967 driver chip)
* Very slow speeds are supported
* Extensive API
* Subclass support

## Example usage

```
#include "AccelStepperSpark.h"

// Define a stepper and the pins it will use
AccelStepper stepper; // Defaults to AccelStepper::FULL4WIRE (4 pins) on D2, D3, D4, D5

void setup()
{  
  // Change these to suit your stepper if you want
  stepper.setMaxSpeed(100);
  stepper.setAcceleration(20);
  stepper.moveTo(500);
}

void loop()
{
    // If at the end of travel go to the other end
    if (stepper.distanceToGo() == 0)
      stepper.moveTo(-stepper.currentPosition());

    stepper.run();
}
```

## References

Please visit http://www.airspayce.com/mikem/arduino/AccelStepper/ for a complete list of APIs.

# Thanks

Thanks to Mike McCauley for his awesome [AccelStepper](http://www.airspayce.com/mikem/arduino/AccelStepper/) library.

The Particle port is currently being maintained by [Abdulrahman Saleh Khamis](http://www.mawqey.com/)
