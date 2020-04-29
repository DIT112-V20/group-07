// code for GPS communication
const String fakeLatitude = "-4.898";
const String fakeLongitude = "34.2000";

void sendToBluetooth(){
    while (true){
        SerialBT.print(fakeLatitude + "#" + fakeLongitude + "##");
        delay(1000);
    }
}
