void parsedGPS() {

  Serial.println("1");
  while (Serial_connect.available()){
     Serial.println("2");
    gps.encode(Serial_connect.read());
  }
  
  if (gps.location.isUpdated()){    
    //print to bluetooth
     Serial.println("3");
    SerialBT.print(gps.location.lat(), 6);
    SerialBT.print("#");                          //if needed the # is there to split lat and long
    SerialBT.print(gps.location.lng(), 6); // '\n' is there to know that both lat long has been received
    SerialBT.print("\n");


    //test for making sure the gps works using the serial monitor
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