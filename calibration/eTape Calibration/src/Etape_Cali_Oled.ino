/*
 * Project Etape_calibration
 * Description:
 * Author:
 * Date:
 */
 // The following program is an example of data smoothing using the QuickStats.h library in Arduino.

#include "QuickStats.h" 
#include "OLED_Display_128X64.h" // Include the OLED Display library

// the value of the 'other' resistor
#define SERIESRESISTOR 2000  // 12 in = 2000, 15 in = 2500, 18 in = 3000, 24 in = 4000

#include "SeeedOLED.h"
// declaring etape pin 
byte sensorPin = A0;              
int v = 0;                        // variable to store analog reading
int NUMSAMPLES=100;               // number of samples to take for data smoothing 
float measurements[100];          // variable for holding raw measurements
float smoothed;                   // variable for holding filtered measurement
float smoothedCV;  
float depth;

void updateDisplay(int depth, int smoothedCV, int smoothed); 
// variable for holding CV of measurements

char msg[200];

QuickStats stats; //initialize an instance of this class

void setup()
{
  Serial.begin(9600); 
  Serial.println("Reading, %CV");

  Wire.begin();
  SeeedOled.init(); 

    // Clear the screen
    SeeedOled.clearDisplay();
    SeeedOled.setNormalDisplay();
    SeeedOled.setPageMode();

    // Set up Display
    SeeedOled.setTextXY(2, 0);
    SeeedOled.putString("Etape Calibration");
    SeeedOled.setTextXY(3, 0);
    SeeedOled.putString("Record Resistance");
    SeeedOled.setTextXY(4, 0);
    SeeedOled.putString("AWQP");
  
}

void loop()
{
  //Collect the data points:
  for(int i=0;i<NUMSAMPLES;i++){
    v=analogRead(sensorPin);
    measurements[i]=(v); // convert to volts
    delay(10);  // Change (or remove) this delay value to alter the sampling time span.
  }  
  smoothed=stats.median(measurements,NUMSAMPLES); // Median filter (choose which filter to use)
  //smoothed=stats.average(measurements,NUMSAMPLES); // Mean filter 
  //smoothed=stats.g_average(measurements,NUMSAMPLES); // Geometric mean filter 
  //smoothed=stats.mode(measurements,NUMSAMPLES,0.00001); // Mode filter, epsilon=0.00001 (tolerance for two measurements being equivalent)
  smoothed = (4095 / smoothed) - 1; // convert to resistance
  smoothed = SERIESRESISTOR / smoothed; // convert to voltage
  smoothedCV = stats.CV(measurements,NUMSAMPLES); // CV of readings    
  
  depth = (-0.0175*smoothed) + 69.14; //Steamboat (15in)

  Serial.print(smoothed,3);  // Print smoothed value to serial monitor
  Serial.print(", ");
  Serial.println(smoothedCV);  // Print CV to serial monitor
  Serial.print("Depth cm =  ");
  Serial.println(depth);  // Print CV to serial monitor

updateDisplay(depth, smoothedCV, smoothed);
  
//convert to string
 snprintf(msg, sizeof(msg) - 1, "Res:%f,cv:%f,depth:%f", smoothed, smoothedCV, depth);
    Particle.publish("EtapeData", msg, PRIVATE); //publish to particle cloud

  delay(5000); // Change (or remove) this delay to alter the time between readings.
}

void updateDisplay(int depth, int smoothedCV, int smoothed) {
    SeeedOled.clearDisplay();

    SeeedOled.setTextXY(2, 0);
    SeeedOled.putString("Res:");
    SeeedOled.putNumber(smoothed);

    SeeedOled.setTextXY(4, 0);
    SeeedOled.putString("Depth:");
    SeeedOled.putNumber(depth);

  }