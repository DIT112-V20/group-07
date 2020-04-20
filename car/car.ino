#include <Smartcar.h>
#include <BluetoothSerial.h>

int trigPin = 19; //D19
int echoPin = 5; //D5
int MAX_DISTANCE = 300;
const auto pulsesPerMeter = 600;
const int TURN_ANGLE = 80;
const int REVERS_SPEED = 40;

BrushedMotor leftMotor(smartcarlib::pins::v2::leftMotorPins);
BrushedMotor rightMotor(smartcarlib::pins::v2::rightMotorPins);
DifferentialControl control (leftMotor, rightMotor);

GY50 gyroscope(37);
SR04 front(trigPin, echoPin, MAX_DISTANCE);

BluetoothSerial SerialBT;//for the BT

DirectionlessOdometer leftOdometer(
  smartcarlib::pins::v2::leftOdometerPin,
[]() {
  leftOdometer.update();
},
pulsesPerMeter);
DirectionlessOdometer rightOdometer(
  smartcarlib::pins::v2::rightOdometerPin,
[]() {
  rightOdometer.update();
},
pulsesPerMeter);

SmartCar car(control, gyroscope, leftOdometer, rightOdometer);

//Method that detects if the smartcar is connected to bluetooth
void callback(esp_spp_cb_event_t event, esp_spp_cb_param_t *param) {
  if (event == ESP_SPP_SRV_OPEN_EVT) { //If the smartcar has a bluetooth connection
    digitalWrite(LED_BUILTIN, HIGH); // turn the LED on (HIGH is the voltage level)
  }

  if (event == ESP_SPP_CLOSE_EVT ) { //If the smartcar does not have a bluetooth connection
    stop();
    ledBlink();
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  SerialBT.begin("Smartcar"); //Name of the BT in the car
  pinMode(LED_BUILTIN, OUTPUT);
  SerialBT.register_callback(callback);

}

void loop() {
  // put your main code here, to run repeatedly:
  handleInput();
}

void handleInput() { //handle serial input if there is any

       if (SerialBT.available()) {
    char input;
    while (SerialBT.available()) {
      input = SerialBT.read();
    }; //read till last character
    switch (input) {
      case 'l': //rotate counter-clockwise going forward
        turnLeft(TURN_ANGLE);
        break;
      case 'r': //turn clock-wise
        turnRight(TURN_ANGLE);
        break;
      case 'f': //go ahead
        driveForward();
        break;
      case 'b': //go back
        reverse(REVERS_SPEED);
        break;
      case 'd': //go a sartian distance     
         goDistance (30, 30);     
      break;
      case 'v': //drive at certain speed  
         limitSpeed (20);     
      break;
      case 's':
        stop();
        break;
      default: //if you receive something that you don't know, just stop
        stop();
    }
  }
       
}
