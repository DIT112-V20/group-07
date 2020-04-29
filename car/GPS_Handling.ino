#include <TinyGPS++.h>

TinyGPSPlus gps;
/*
 *    THIS SHALL BE IN THE CAR FILE
 *
 * SerialGPS.begin(GPSBaud);
 */

 void parsedGPS(){
  while (SerialGPS.available()>0){
    gps.encode(SerialGPS.read());
    delay(2000);
    if (gps.location.isUpdated()){ //do we want to update with a delay or with a delay and when the car changes position??
      SerialBT.print("Latitude = "); SerialBT.println(gps.location.lat(), 6);  //prints long and lat strings to                                                                          
      SerialBT.print("Longitude = "); SerialBT.println(gps.location.lng(), 6); //bluetooth serial
    }
  }
 }
