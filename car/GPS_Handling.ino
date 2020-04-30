#include <TinyGPS++.h>

TinyGPSPlus gps;

 void parsedGPS(){
  while (SerialGPS.available()>0){
    gps.encode(SerialGPS.read());
    delay(2000);
    Serial.println("-----------");
    if (gps.location.isUpdated()){ //do we want to update with a delay or with a delay and when the car changes position??
      Serial.print("Latitude = "); Serial.println(gps.location.lat(), 6);  //prints long and lat strings to
      Serial.print("Longitude = "); Serial.println(gps.location.lng(), 6); //bluetooth serial
    }
  }
 }
