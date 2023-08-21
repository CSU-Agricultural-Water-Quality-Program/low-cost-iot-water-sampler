// This example retrieves last value of a variable from the Ubidots API
// using HTTP protocol.

/****************************************
 * Include Libraries
 ****************************************/

#include "Ubidots.h"

/****************************************
 * Define Constants
 ****************************************/

#ifndef UBIDOTS_TOKEN
#define UBIDOTS_TOKEN "BBFF-IONay56PteRbxIMQbk4ppZ81VFX7yHGbZe5CTfmgEwZyqhbWnVbcVC9"  // Put here your Ubidots TOKEN
#endif

// Uncomment this line to print debug messages
#define UBIDOTS_LOGGING TRUE

Ubidots ubidots(UBIDOTS_TOKEN, UBI_TCP);

/****************************************
 * Auxiliar Functions
 ****************************************/

// Put here your auxiliar functions

/****************************************
 * Main Functions
 ****************************************/

void setup() {
  Serial.begin(115200);
  ubidots.setDebug(true);
}

void loop() {
  /* Obtain last value from a variable as float using HTTP */
  // float value = ubidots.get("demo", "demo");
  tcpMap myMap = ubidots.getMultipleValues("demo", "demo1,demo2");
  float value = myMap[0];
  // Evaluates the results obtained
  if (value != ERROR_VALUE) {
    Serial.print("Value:");
    Serial.println(value);
  }
  Serial.print("other value:");
  Serial.println(myMap[1]);
  delay(5000);
}
