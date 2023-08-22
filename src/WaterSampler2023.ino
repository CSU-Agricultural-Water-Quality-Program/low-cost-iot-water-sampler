
/*
* Project: Low-cost, IoT water sampler
* Description: A low-cost, automated water sampler (LCS) with Internet of Things
 (IoT) technology for scalable, near-real-time water quality research developed
 by the Colorado State University Agricultural Water Quality Program
* Table of Contents 
 This version uses Blynk for control and user inputs.
 adapted from code written by chip mcclelland ,seeinsight.com
 Original Author: Jay Ham
 Modified by: Emmanuel Deleon and A.J. Brown
 Sponsor: Colorado State University Agricultural Water Quality Program
 License: GPL v4
 Date: 27 Nov 2019
 Last Update: 22 Aug 2023
 Particle Boron Firmware Target: 5.2.0
*/

// v1.00 - Initial Release - Rough program outline with serial monitor// interface
// v1.01 - First Working Version, debugged with keyboard input of sample volume
// v1.02 - Uses Blynk  and WiFi for input and reporting instead of keyboard IDE
// v1.03 - Add stats and other Blynk features, provisions for prepurge of hose
// v1.04 - add a secound pump to the code
// v1.05 - coverted to particle using workbench
// v1.06 - added etape
// V1.07 - moved to new blynk IoT
// V1.08 - cleaned, added variable, add temp resistance to etapeand add project to private github repo
// V1.09 - added remote reset function

#define BLYNK_PRINT Serial  // setup blynk
// #define BLYNK_TEMPLATE_ID "TMPLirZT8ePI" // commented out when using config.h
#define BLYNK_DEVICE_NAME "Low Cost Water Sampler"

//#define SERIESRESISTOR 2000    //12-in. etape resistance
#define SERIESRESISTOR 2500    //15-in. etape resistance
//#define SERIESRESISTOR 3000    //18-in. etape resistance
//#define SERIESRESISTOR 4000    //24-in. etape resistance

#include <MeanFilterLib.h>  // setup library
#include <AccelStepper.h>
#include <QuickStats.h>
#include <Ubidots.h> 
#include <blynk.h>
#include "config.h" // include config file with tokens and other private info

// below code not needed when using config.h file
// #ifndef TOKEN
// #define TOKEN  "{Ubidots API token here}" // Put here your Ubidots API TOKEN in quotes
// #endif

Ubidots ubidots(TOKEN, UBI_TCP); // Comment this line to use another protocol.

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "{token}"; // Put your auth token here in quotes
//char auth[] = "{token}"; // additional tokens can be commented for convenience
//char auth[] = "{token}"; // additional tokens can be commented for convenience


// Your WiFi credentials if using Particle Photon instead of Paricle Boron.
// Set password to "" for open networks.
//char ssid[] = "csu-guest";
//char pass[] = "";


char depthString[16];               //  depth 
char thresholdString[16];           //   threshold
char sample_numberString[16];      //   sample number
char sigString[16];                 //   signal strength


// state machine variables
enum State { INITIALIZATION_STATE, ERROR_STATE, IDLE_STATE, PRIME_STATE, SAMPLE_STATE, PURGE_STATE, REPORTING_STATE};
char stateNames[7][14] = {"Initialize", "Error", "Idle", "Priming", "Sampling", "Purging", "Reporting"};
State state = INITIALIZATION_STATE;
State oldState = INITIALIZATION_STATE;

// GPIO assignments
const int WATER_PIN = D4;    // pin for non contact water sensor, NPN
const int DIR_PIN1 = D3;  // Pump1 direction HIGH or LOW
const int STEP_PIN1 = D5;  // Pump1 start per step
const int STEPEN_PIN1 = D2; // Enables pump1 when LOW
const int VOLT_PIN = A2;     // read voltage source, 10:1 divider

byte sensorPin = A0;              // declaring etpae to particle 
int v = 0;                        // variable to store analog reading
int NUMSAMPLES=100;               // number of samples to take for data smoothing 
float measurements[100];          // variable for holding raw measurements
float smoothed;                   // variable for holding filtered measurement
float smoothedCV;  
float depth;
int Time_old;
float rssi = 0.00;

// Remote system reset variables
#define DELAY_BEFORE_REBOOT 2000
unsigned int rebootDelayMillis = DELAY_BEFORE_REBOOT;
unsigned long rebootSync = millis();
bool resetFlag = false;

// pump pulses required to purge lines
unsigned long currentMillis, startMillis, sampleMillis,purgeMillis;
unsigned long pulsetime, pulselast, pulseinterval; // timing variables
unsigned long primeMillis=0;
unsigned long maxprimeMillis=30*1000;   // max allowable pumping time to prime, e.g.30s
unsigned long maxsampleMillis=120*1000;   // max allowable sampling time to prime, e.g.120s
unsigned long maxpurgeMillis=60*1000;   // max allowable purging time , e.g.60s
unsigned long waterMean;    // avg of non contact water sensor

#define motorInterfaceType 1  // setup motor interface type
float volCal1 = 0.008259777;   // calculated millimeter per step
int ml_to_collect=0;  // example sample volume to collect
unsigned long sampleSteps = 5000; //set to number that if need to purge on system startup will purge that many steps in 3000 steps our pump will go 15 rotations
unsigned long sampleStepsPerge; 
unsigned long stepperSpeed = 1000; // Pump speed in steps per second
float battVolt;         // battery voltage

int sample_interval_min = 60;
unsigned long sample_interval_ms = 0;
unsigned long old_sample_millis = 0;
unsigned int sample_number = 1;
int threshold = 7;
int sample_bottle_mL = 4500;

boolean sample_now =false;

AccelStepper stepper1 = AccelStepper(motorInterfaceType, STEP_PIN1, DIR_PIN1);

MeanFilter<long> meanFilter(25);  // average non contact water sensor
MeanFilter<float>voltFilter(50);  // average non contact water sensor

QuickStats stats; //initialize an instance of this class


void setup() {
  
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
    // connect to blynk
  //Particle.keepAlive(PARTICLE_KEEPALIVE);
  delay(2000);
  Blynk.begin(auth);
  Blynk.virtualWrite(V2, "clr");  // clear Terminal Widget
  Blynk.virtualWrite(V2, "4G connected! Sampler Active!\n");
  Blynk.syncVirtual(V1);  // sync slider value

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB
  }
  Serial.setTimeout(10);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(STEP_PIN1, OUTPUT);
  pinMode(DIR_PIN1, OUTPUT);
  pinMode(STEPEN_PIN1, OUTPUT);
  
  pinMode(WATER_PIN, INPUT_PULLUP);  // water detector

  stepper1.setMaxSpeed(1200); // Set the maximum speed in steps per second:
  
  for (int x = 0; x < 40; x++) {  // read non contact water sensor on hose
    waterMean = meanFilter.AddValue(digitalRead(WATER_PIN)); 
  }
    state = PURGE_STATE;

  digitalWrite(STEPEN_PIN1, LOW); // Pump1 on
  
  sample_interval_ms = sample_interval_min * 60 * 1000;

// Particle variables for Particle app
Particle.variable("depth", depthString); 
Particle.variable("threshold", thresholdString);
Particle.variable("next_sample_number", sample_numberString);
Particle.variable("signal", sigString);

//  Remote Reset Function Setup
Particle.function("reset", cloudResetFunction);
    
}  // end setup

void loop() {
  Blynk.run();
  switch(state) { // state machine  starts here
  
  case IDLE_STATE:
   if (state != oldState) printStateTransition();
   if (ml_to_collect>0 && check_sample_interval()==1 && depth >= threshold && check_sample_number()==1) state = PRIME_STATE;
   else if (ml_to_collect>0 && sample_now) state = PRIME_STATE;
   break;

  case PRIME_STATE:
    if (state != oldState) printStateTransition();
    if (!primeSystem())
    {
      state = ERROR_STATE;
     }
    else state = SAMPLE_STATE;
  break;

  case SAMPLE_STATE:
    if (state != oldState) printStateTransition();
    if (!collectSample())
    {
      state = ERROR_STATE;
    }
    else state = PURGE_STATE;
    
    Blynk.virtualWrite(V2, sample_number);
  
  break;

 case PURGE_STATE:
   if (state != oldState) printStateTransition();
   if (!purgeSystem())
    {
      state = ERROR_STATE;
    }
    else 
    state = REPORTING_STATE;
   break;
  
 case REPORTING_STATE:
   if (state != oldState) printStateTransition();
   if (!reportingData())
   {
     state = ERROR_STATE;
   }
   else 
   {
    //ml_to_collect=0;
    sample_now=false;
    state = IDLE_STATE;
   }
 break; 
 
 case ERROR_STATE:                                                   // To be enhanced - where we deal with errors
    if (state != oldState) printStateTransition();
    //Serial.println("Halted in error state");
    Blynk.virtualWrite(V2, "Halted in error state\n");
    while(1);  // halt
 break;
  
 } // end switch

// take reading every 5 min
if(Time.minute() % 5 == 0 && Time_old != Time.minute()){ //read every 20 min. change the "10" to change sample interval in min (1 - 59)

//Collect etape measurments:
  for(int i=0;i<NUMSAMPLES;i++){
    v=analogRead(sensorPin);
    measurements[i]=(v); // convert to volts
    delay(10);  // Change (or remove) this delay value to alter the sampling time span.
  }  
  smoothed = stats.median(measurements,NUMSAMPLES); // Median filter (choose which filter to use)
  //smoothed=stats.average(measurements,NUMSAMPLES); // Mean filter 
  //smoothedCV=stats.CV(measurements,NUMSAMPLES); // CV of readings  
  smoothed = (4095 / smoothed) - 1; // convert to resistance
  smoothed = SERIESRESISTOR / smoothed; // convert to voltage
  
/* Convert voltage to depth based on custom etape linear calibration curve
   etape product link: https://milonetech.com/products/standard-etape
   etape data sheet: https://img1.wsimg.com/blobby/go/6e1bce17-f4fa-40c3-9d89-9bb7445697bb/downloads/Standard%20eTape%20Data%20Sheet.pdf 
  
   Use the following equation as per the mileone etape manual guidelines
     depth = (A*smoothed) + B
     where A = (depth_2-depth_1)/(resistance_2-resistance_1) and B = depth_1 - A*resistance_1
   or where multiple resistances are plotted against depth and fitted with an OLS regression line
     depth = (slope*smoothed) + intercept
*/
 depth = (-0.01695*smoothed) + 46.2695; // current selected calibration
 //depth = (-0.01686*smoothed) + 46.99; // comment other curves for convenience to use on other sampler units


  snprintf(depthString,sizeof(depthString) -1, "%4.1f cm", depth);  // convert to string

  CellularSignal sig = Cellular.RSSI(); // get signal strength
  rssi = sig.getQuality();
  float strength = sig.getStrength();
  snprintf(sigString,sizeof(sigString), "%.02f %", strength);
 
 //FuelGauge fuel;
  // float voltage = fuel.getVCell();
  // float SoC = fuel.getSoC();
 
  ubidots.add("Level_cm", depth);  // send data to ubidots
  //ubidots.add("Volts", voltage);
  //ubidots.add("SoC", SoC);
  //ubidots.add("Rssi", rssi);
  ubidots.add("SigS", strength);
 
    bool bufferSent = false;
    bufferSent =ubidots.send();  //Send data to ubidot
    Time_old = Time.minute(); // resetting time 
  }

// Remote Reset Function
if ((resetFlag) && (millis() - rebootSync >=  rebootDelayMillis)) {
    // do things here before reset if necessary and then push the button
    Particle.publish("Debug", "Remote Reset Initiated", 300, PRIVATE);
    System.reset();
  }

} // end main loop

bool primeSystem() {    // prime system with water 
   //digitalWrite(DIR_PIN, HIGH);  // Pump forward
   digitalWrite(STEPEN_PIN1, LOW); // Pump on

   startMillis=millis();
   currentMillis=startMillis;
   waterMean = meanFilter.AddValue(digitalRead(WATER_PIN)); //  noncontact water sensor on hose
   while (waterMean != 0 && (currentMillis-startMillis)<maxprimeMillis){
     stepper1.setSpeed(stepperSpeed);
     stepper1.runSpeed();
     currentMillis=millis();   // wait for prime of tubing or runs of time
     waterMean = meanFilter.AddValue(digitalRead(WATER_PIN)); //  noncontact water sensor on hose
     Blynk.run();
   }
   stepper1.stop();       // turn Pump1 Off
   delay(50);
   if((currentMillis-startMillis)<=maxprimeMillis){
    primeMillis=currentMillis-startMillis;
   //Serial.print("Prime time: ");  Serial.println(primeMillis/1000);
    return 1;   // successful prime
   }
   else return 0;   // prime failed
   
}

bool collectSample() {  // pump desired volume into sample bottle
   
   digitalWrite(STEPEN_PIN1,LOW);    // pump1 on

   startMillis=millis();
   currentMillis=startMillis;
   //sampleRotations = ml_to_collect/volCal;
   sampleSteps = ml_to_collect/volCal1;
   stepper1.setCurrentPosition(0);

   while (stepper1.currentPosition() != sampleSteps && (currentMillis-startMillis)<maxsampleMillis){   
     currentMillis=millis(); // wait for sampling to complete or run out of time
     stepper1.setSpeed(stepperSpeed);
     stepper1.runSpeed();
     battVolt = voltFilter.AddValue(ReadVoltage(VOLT_PIN))*10.0*1.0125; //  volt source
     Blynk.run();
   }
   stepper1.stop();       // turn Pump Off

   delay(50);
   if((currentMillis-startMillis)<maxsampleMillis){
    sampleMillis=currentMillis-startMillis;
    //Serial.print("Sample time: ");Serial.println(sampleMillis/1000);
    //Serial.print("Sample ticks: ");Serial.println(pulseTicks);
    
    old_sample_millis = startMillis;
	  sample_number++;
    snprintf(sample_numberString,sizeof(sample_numberString), "%d", sample_number);
    
    return 1;   // successful sample
   }
   else return 0;   // sample failed
}

bool check_sample_interval(){
	currentMillis = millis();
	if(currentMillis - old_sample_millis >= sample_interval_ms){
		return 1;
	}	
	else return 0;
}

bool check_sample_number(){
	float current_bottle_mL = sample_number * ml_to_collect;
	if(current_bottle_mL <= sample_bottle_mL){
		return 1;
	}
	else return 0;
}

bool purgeSystem() {  // reverse pump and purge water lines of all water
   
   if (primeMillis>1000){           // if > 1s
     maxpurgeMillis= primeMillis*2;}
   else{
   maxpurgeMillis= 45*1000;}     // if <1s then default to 45s. 
   startMillis=millis();
   currentMillis=startMillis;
   sampleStepsPerge = sampleSteps*-1;
   //while (pulseTicks<purgeTicks && (currentMillis-startMillis)<maxpurgeMillis){
   stepper1.setCurrentPosition(0);
   while (stepper1.currentPosition() != sampleStepsPerge && (currentMillis-startMillis)<maxpurgeMillis){
     currentMillis=millis(); // wait for purge to complete or run out of time
     waterMean = meanFilter.AddValue(digitalRead(WATER_PIN));
     stepper1.setSpeed(-1000);
     stepper1.runSpeed();
     Blynk.run();
   }
   stepper1.stop();       // turn Pump1 Off

   digitalWrite(STEPEN_PIN1,HIGH);    // pump1 off, forward

  // Serial.print("CurrentMillis-StartMilis: ");  Serial.println((currentMillis-startMillis));
   //Serial.print("maxPurgeMillis: ");  Serial.println((maxpurgeMillis));
   if((currentMillis-startMillis)<=maxpurgeMillis){
    purgeMillis=currentMillis-startMillis;
    //Serial.print("Purge time: ");  Serial.println(purgeMillis/1000);
    return 1;   // successful sample
   }
   else return 0;   // purge failed
}

bool reportingData() {  // send data to Blynk

  Blynk.virtualWrite(10, float(volCal1*sampleSteps)); // virtual pin 
  //Blynk.virtualWrite(11, sampleTicks); // virtual pin
  Blynk.virtualWrite(12, ml_to_collect); // virtual pin
  Blynk.virtualWrite(13, float(primeMillis)/1000); // virtual pin 
  Blynk.virtualWrite(18, float(sampleMillis)/1000); // virtual pin
  //Blynk.virtualWrite(15, purgeTicks); // virtual pin 
  Blynk.virtualWrite(16, float(purgeMillis)/1000); // virtual pin
  Blynk.virtualWrite(17, depth); // virtual pin
  //Blynk.virtualWrite(18, battVolt); // virtual pin

  return 1;
}

void printStateTransition(void)   // print transition from one state to another
{
  char stateTransitionString[40];
  snprintf(stateTransitionString, sizeof(stateTransitionString), "From %s to %s", stateNames[oldState],stateNames[state]);
  oldState = state;
  Serial.println(stateTransitionString);
  Blynk.virtualWrite(V2, stateTransitionString);
  Blynk.virtualWrite(V2, "\n");
}

double ReadVoltage(byte pin){  // read voltage on esp32 w correction
  double reading = analogRead(pin); // Reference voltage is 3v3 so maximum reading is 3v3 = 4095 in range 0 to 4095
  if(reading < 1 || reading > 4095) return 0;
  // return -0.000000000009824 * pow(reading,3) + 0.000000016557283 * pow(reading,2) + 0.000854596860691 * reading + 0.065440348345433;
  return -0.000000000000016 * pow(reading,4) + 0.000000000118171 * pow(reading,3)- 0.000000301211691 * pow(reading,2)+ 0.001109019271794 * reading + 0.034143524634089;
} 

int cloudResetFunction(String command) { // Remote Reset Function
    resetFlag = true;
    rebootSync = millis();
    return 1;
    // You would call the function by typing “true” in the particle console
}

BLYNK_WRITE(V1)  //gets slider value from blynk
{
  float pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  ml_to_collect  = pinValue;
  //Serial.print("ml_to_collect: ");Serial.println(ml_to_collect);
  Blynk.virtualWrite(12, ml_to_collect); // virtual pin
  Blynk.virtualWrite(V2, "ml_to_collect set to: ");
  Blynk.virtualWrite(V2, ml_to_collect); 
  Blynk.virtualWrite(V2, " mL\n");  
}

BLYNK_WRITE(V3)  //gets slider value from blynk
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  sample_interval_min  = pinValue;	// desired sample interval in minutes
  sample_interval_ms = sample_interval_min * 60 * 1000;
  Blynk.virtualWrite(13, sample_interval_min); // virtual pin 
  Blynk.virtualWrite(V2, "sample interval set to: ");
  Blynk.virtualWrite(V2, sample_interval_min); 
  Blynk.virtualWrite(V2, " min\n");
}

BLYNK_WRITE(V4)  //gets slider value from blynk
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  threshold  = pinValue; // depth threshold (cm) for autosampler to begin sample collection
  Blynk.virtualWrite(14, threshold); // virtual pin
  Blynk.virtualWrite(V2, "threshold set to: ");
  Blynk.virtualWrite(V2, threshold); 
  Blynk.virtualWrite(V2, " cm\n"); 
}

BLYNK_WRITE(V5)  //gets slider value from blynk
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  sample_bottle_mL  = pinValue; // sample bottle volume in mL
  Blynk.virtualWrite(15, sample_bottle_mL); // virtual pin 
  Blynk.virtualWrite(V2, "sample_bottle_mL set to: ");
  Blynk.virtualWrite(V2, sample_bottle_mL); 
  Blynk.virtualWrite(V2, " mL\n");
}

BLYNK_WRITE(V9) // get button value from blynk
{
  int pinValue = param.asInt();
  sample_now=pinValue;
 // Serial.print("sample_now: ");Serial.println(sample_now);
}
