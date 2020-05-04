#include "TinyGPS++.h"

TinyGPSPlus gps;

void parsedGPS() {
  
  while (Serial_connect.available()){
    gps.encode(Serial_connect.read());  
  }
  
  if (gps.location.isUpdated()){    
    //print to bluetooth
    SerialBT.println(gps.location.lat(), 6); 
    SerialBT.println("#");                          //if needed the # is there to split lat and long
    SerialBT.println(gps.location.lng(), 6 + '\n'); // '\n' is there to know that both lat long has been received


    //test for making sure the gps works using the serial monitor
   /* Serial.println("Latitude: ");
    Serial.println(gps.location.lat(), 6);
    Serial.println("Longitude: ");
    Serial.println(gps.location.lng(), 6);
   */
  }
}
