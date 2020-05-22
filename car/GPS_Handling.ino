void parseGPS(){
    while (Serial2.available()) {
        //Serial.println("Encoding GPS");
        gps.encode(Serial2.read());
    }
}

void printGpsToSerial(){
    //Serial.println("SERIAL PRINT: ");
    if (gps.location.isValid()){
        Serial.println("Satellite Count:");
        Serial.println(gps.satellites.value());
        Serial.println("Latitude:");
        Serial.println(gps.location.lat(), 6);
        Serial.println("Longitude:");
        Serial.println(gps.location.lng(), 6);
    }
}
void printGpsToBluetooth(){
    if (gps.location.isValid()){
        //Serial.println("Print to Bluetooth");
        SerialBT.print(gps.location.lat(), 6);
        SerialBT.print("#");                          //if needed the # is there to split lat and long
        SerialBT.print(gps.location.lng(), 6); // '\n' is there to know that both lat long has been received
        SerialBT.print("\n");
    }
}
