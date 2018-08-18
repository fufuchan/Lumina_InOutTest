#include "Adafruit_VL53L0X.h"

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

const int outPin = 7;
const int inPin = 2;
int pinVal = 0;
int lastPinVal = 1;

void setup() {
  Serial.begin(115200);

  pinMode (LED_BUILTIN, OUTPUT);
  pinMode (outPin, OUTPUT);
  pinMode(inPin, INPUT);
   
  // wait until serial port opens for native USB devices
  while (! Serial) {
    delay(1);
  }
  
  Serial.println("Adafruit VL53L0X test");
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while(1);
  }
  // power 
  Serial.println(F("VL53L0X API Simple Ranging example\n\n")); 
}


void loop() {
  VL53L0X_RangingMeasurementData_t measure;
    
  Serial.print("Reading a measurement... ");
  lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!

  if (measure.RangeStatus != 4) {  // phase failures have incorrect data
    Serial.print("Distance (mm): "); Serial.println(measure.RangeMilliMeter);
    outputOn();
  } else {
    Serial.println(" out of range ");
    outputOff();
  }
    input();
  delay(100);
}

void outputOn () {
  digitalWrite(outPin, HIGH);
}

 void outputOff() {                   
  digitalWrite(outPin, LOW);
 }


void input () {
  pinVal = digitalRead(inPin);
  if(lastPinVal != pinVal){
    digitalWrite(LED_BUILTIN, pinVal);
//    digitalWrite(LED_BUILTIN, HIGH);   
    Serial.println(pinVal);
   lastPinVal = pinVal;
  }
}


