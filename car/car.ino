#include <Smartcar.h>
#include <BluetoothSerial.h>

int trigPin = 19; //D19
int echoPin = 5; //D5
int MAX_DISTANCE = 300;
const auto pulsesPerMeter = 600;
const int TURN_ANGLE = 80;
const int REVERS_SPEED = 40;
const int GYRO_OFFSET = 22;
const int STOP_DIST = 15;

BrushedMotor leftMotor(smartcarlib::pins::v2::leftMotorPins);
BrushedMotor rightMotor(smartcarlib::pins::v2::rightMotorPins);
DifferentialControl control (leftMotor, rightMotor);

GY50 gyroscope(GYRO_OFFSET);
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


//-------------------------------Set Up and Loop----------------------------------------------------//

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  SerialBT.begin("Smartcar"); //Name of the BT in the car
  SerialBT.println("U,9600,N"); //Not sure if needed
  pinMode(LED_BUILTIN, OUTPUT);
  SerialBT.register_callback(callback);

}

void loop() {
  // put your main code here, to run repeatedly:
  obstacleAvoidance();
}

//-------------------------------Set Up and Loop----------------------------------------------------//

//Method that detects if the smartcar is connected to bluetooth
void callback(esp_spp_cb_event_t event, esp_spp_cb_param_t *param) {
  if (event == ESP_SPP_SRV_OPEN_EVT) { //If the smartcar has a bluetooth connection
    digitalWrite(LED_BUILTIN, HIGH); // turn the LED on (HIGH is the voltage level)
  }

  if (event == ESP_SPP_CLOSE_EVT ) { //If the smartcar does not have a bluetooth connection
    stop();    
    
    while (true){
      digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(1000);                       // wait for a second
      digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
      delay(1000);                       // wait for a second
    }
  }
}

void obstacleAvoidance() {
  int distance = front.getDistance();

  if (distance <= STOP_DIST && distance > 0){ //stop when distance is less than 15 cm.
    stop();
  }
  else{
    handleInput();
  }
}

void handleInput() { //handle serial input (String!!)
  if (SerialBT.available()) { 
    String input;
    while (SerialBT.available()) { 
      input = SerialBT.readStringUntil('\n');   
    }; //read till last character
    
    if (input.startsWith("v")) {
      int throttle = input.substring(1).toInt();
      forward(throttle);
    }

    if (input.startsWith("b")) {
      int throttle = input.substring(1).toInt();
      reverse(throttle);
    }

    if (input.startsWith("t")) {
      int throttle = input.substring(1).toInt();
      turn(throttle);
    }  
  }
}
