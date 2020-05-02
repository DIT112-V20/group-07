#include "TinyGPS++.h"
#include "SoftwareSerial.h"

int TXpin = 17;
int RXpin = 16;

SoftwareSerial Serial_connect(TXpin, RXpin); 
TinyGPSPlus gps;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial_connect.begin(9600);
  Serial.println("GPS Start");

}

void loop() {
  // put your main code here, to run repeatedly:

  while (Serial_connect.available()){
    gps.encode(Serial_connect.read());  
  }

  if (gps.location.isUpdated()){
    Serial.println("Satellite Count:");  
    Serial.println(gps.satellites.value());  
    Serial.println("Latitude:");  
    Serial.println(gps.location.lat(), 6);  
    Serial.println("Longitude:");  
    Serial.println(gps.location.lng(), 6);  
    Serial.println("Speed MPS:");
    Serial.println(gps.speed.mps());
  }

}
